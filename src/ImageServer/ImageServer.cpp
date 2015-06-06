
#include "ImageServer.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include <assert.h>
#include <thread>
#include <boost/filesystem.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/regex.hpp>
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp> 

#define STR_EXPAND(tok) #tok
#define STR(tok) STR_EXPAND(tok)
 
// example of a namespace alias
namespace FS = LMFocusStack;
namespace bfs = boost::filesystem;

using FS::ImageServer;

FS::ImageServer::ImageServer(int argc, char ** argv) {
  
	if (argc < 2) 
	{ // settings file not specified, use default
		this->settings_path_ = def_settings_;
	} 
	else { // load settings or display help
		settings_path_ = argv[1];
	} 
	load_settings(); // could throw invalid settings exception
}

void FS::ImageServer::start_server() {
	std::cout << "Starting server at " << port_ 
			<< " ..." << std::endl;
	using boost::asio::ip::tcp;

	boost::asio::io_service io_service;

	server_(io_service, port_);

	// io_service.run might not be needed for blocking sever
	//io_service.run();
	
}

void FS::ImageServer::load_settings() {
	std::ifstream fin;
	#include STR(L10N_LANG)
	try {
		const int BUF_LEN = 4096*2;
		char buffer[BUF_LEN];
		// check if file exists and is a regular file
		// if file doesn't exist create a default file
		bfs::path p (this->settings_path_);
		if ( !bfs::exists(p) )
			create_default_settings ();
		if ( bfs::is_directory(p) ) 
			throw std::invalid_argument (
				rstr_dirNotFile + settings_path_ );
 	
		fin.open(this->settings_path_);
		if (!fin.good()) 
			throw std::invalid_argument
				("Cannot access settings file: "
					+ settings_path_);
		
		// read one line at a time
		while (fin.good()) {
			fin.getline(buffer, BUF_LEN);
			load_settings_line(buffer, BUF_LEN);
		}
		
	} catch (...) {
		fin.close(); 
		// destruction of fin should also ensure clousure
		// but just making sure
		throw; // clean-up and re-throw
	}
}

void FS::ImageServer::load_settings_line(const char * buf, const int N) {
	assert( N > 0 );
	//std::cout << "Reading line: " << buf << std::endl;
	const boost::regex re_comment("^[[:space:]]*;");
	const boost::regex re_dbpath ( 
		"^([[:space:]]*database[[:space:]]=[[:space:]]*)");
	const boost::regex re_port (
		"^([[:space:]]*port[[:space:]]=[[:space:]]*)");
	boost::smatch str_matches; 
	if ( boost::regex_search(std::string(buf), 
				str_matches, re_comment) ) {
		//std::cout << "Comment found\n";
		return;
	}
	if ( boost::regex_search(std::string(buf), 
				str_matches, re_dbpath) ) {
		//std::cout << "Comment found\n";
		db_path_ = buf + str_matches[0].length(); 
		std::cout << "Setting database path to: " 
			  << db_path_ << std::endl;
		return;
	}
	if (boost::regex_search(std::string(buf),
				str_matches, re_port) ) {
	  port_ = std::atoi(buf + str_matches[0].length());
	  return;
	}
}

void FS::ImageServer::create_default_settings() {
	using namespace boost::posix_time;
	using namespace boost::gregorian;

	ptime now = second_clock::local_time();

	std::ofstream fout(settings_path_, std::ofstream::out);
	
	fout << "; Focus Stacking Image Server settings file V 1.0\n"
		"; Automatically created by " << program_version << "\n"
		"; " << to_simple_string(now) << std::endl <<
		"database = FSImSrvDb\n"
	  "port = 8080\n";

	std::cout << "create_default_settings() called" << std::endl <<
	  "settings file created: " << settings_path_ << std::endl;
	

	fout.close();
}

std::map<std::thread::id, FS::ImageServer::state_t> * 
	FS::ImageServer::state_map_
	= new std::map<std::thread::id, FS::ImageServer::state_t>();

using boost::asio::ip::tcp;
// Using for echo example
/*void FS::ImageServer::session_(tcp::socket sock)
{
  const std::thread::id tid = std::this_thread::get_id();
  state_t state = waiting_for_start;
  state_map_->insert(std::pair<std::thread::id, state_t>(tid,state));
  for(;;)
    {
      char data[max_msg_len];

      boost::system::error_code error;
      size_t length = sock.read_some(boost::asio::buffer(data), error);
      std::cout << "Read " << length << " bytes from client" << std::endl;
      if (error == boost::asio::error::eof)
	break; // Connection closed cleanly by peer.
      else if (error)
    
	throw boost::system::system_error(error); // Some other error.

	boost::asio::write(sock, boost::asio::buffer(data, length));
    }
  
}
*/

FS::ImageServer::state_t FS::ImageServer::get_state_()
{
  const std::thread::id tid = std::this_thread::get_id();
  return (*state_map_)[tid];
}

void FS::ImageServer::set_state_(state_t st)
{
  const std::thread::id tid = std::this_thread::get_id();
  (*state_map_)[tid] = st;
}

void FS::ImageServer::parse_frame_id_(char * data, FrameReadState * rs)
{
  std::cout << "parsing header ..." << std::endl;
  uint i;
  for (i = 0; i < rs->length; i++) {
    rs->header[rs->header_pos] = data[i];
    rs->header_pos++;
    if (rs->header_pos == HEADER_LEN) {
      set_state_(reading_data);
      i++;
      break;
    }
  }
  rs->data_index += i;
}


using namespace boost::property_tree;
ptree FS::ImageServer::read_settings_(ptree pt)
/* According to DatabaseFormat.md, we need to: 
 * 1) read the settings file (.ini),
 */
{
  std::cout << "Start of read_settings_" << std::endl;
  
  try {
    
    ini_parser::read_ini(settings_path_, pt);
    
    std::cout << pt.get<std::string>
      ("Network.working_directory") <<std::endl;
    std::cout << pt.get<std::string>
      ("Network.database") << std::endl;
    //std::cout << pt.get<std::string>
    //  ("Network.port") << std::endl;

    return pt;
      
  }
  catch(...){
    std::cout << "Could not read: " << settings_path_ << std::endl;

    // set default ini values here.

    return pt;
  }
  
}

using namespace boost::property_tree;
using namespace boost::filesystem;
void FS::ImageServer::create_update_db_()
/* According to DatabaseFormat.md, we need to:
 * 1b) create or update a database directory
 */
{
  ptree pt;
  pt = read_settings_( pt ); // not sure if this is done correctly
  
  std::cout << pt.get<std::string>
    ("Network.port") <<std::endl;
  
  std::cout << "Settings file exists: " << settings_path_ << std::endl;

  // If a settings_path isn't given then use the /tmp/ directory
  // Assuming linux environment.
  std::cout << "Working directory: " << current_path() << std::endl;
  
  std::string directory = "FSImSrvDb";
  std::string dirpath =
	pt.get<std::string>("Network.working_directory");
  
  // set current path before directory is created
  current_path(dirpath);
  
    
  if (exists(current_path()))
    {
      if (is_directory(directory))
	{
	  //std::cout << "Yes FSImSrvDb is a directory in /tmp/" <<
	  //  std:: endl <<
	  //  "File size in folder: " << file_size("FSImSrvDb/uuid")
	  //  << std::endl;
	  //create_directory("FSImSrvDb/testing");
	  //std::cout << "New directory created: " <<
	  //  is_directory("FSImSrvDb/testing") << std::endl;
	    
	}
      else if (!is_directory(directory))
	{
	  // Attempt to get filepath from settings file.  
	  create_directory(dirpath + directory);
	}
      else
	{
	  //std::cout << "No FSImSrvDb is not a directory" << std::endl;
	  if (!is_directory(directory)){
	    std::cout << "No FSImSrvDb is not a directory" << std::endl;
	    //throw
	    //  boost::system::system_error("No FSImSrvDb is not a directory");
	  }
	}
    }
}

using namespace boost::uuids;
uuid FS::ImageServer::create_uuid_()
  /* According to DatabaseFormat.md, we need to:
   * 3) create or update a UUID file containing the db unique ID
   */
{
  
  uuid new_one = random_generator()();
  //std::cout << "New uuid: " << new_one << std::endl;
  
  return new_one;
}

using namespace boost::uuids;
using namespace boost::property_tree;
using namespace boost::filesystem;
void FS::ImageServer::meta_info_()
/* According to DatabaseFormat.md, we need to:
 * 2) create or update a meta-information file describing the data
 */
{
  ptree pt;

  // would have preferred to put this in the header file
  std::string meta_file_ = "FSImSrvDb/meta_file.json";

  // come back to this once the uuid is created. You can use
  // that as the child then put a bunch of info below it.
  if (exists(meta_file_))
    {
      // update meta_file_
      std::cout << "meta info exists" << std::endl;
    }
  else
    {
      uuid new_uuid = create_uuid_();
      
      pt.put("meta.info","Meta Information for Database");
      pt.put("meta.uuid", new_uuid);
      boost::property_tree::write_json(meta_file_, pt);
      std::cout << "meta info not exists" << std::endl;
    }
}

void FS::ImageServer::process_db_()
/* According to DatabaseFormat.md, we need to: 
 * 1) read the settings file (.ini),
 * 1b) create or update a database directory
 * 2) create or update a meta-information file describing the data
 * 3) create or update a UUID file containing the db unique ID
 * 4) create or update a folder for each stack in the db
 * 5) Ensure that the stack's folder equals the stack's UUID
 */
{
  // step 1b
  create_update_db_();

  // step 2
  meta_info_();

  // step 3
  create_uuid_();

    
}

std::string FS::ImageServer::settings_path_;
// Referencing: https://code.google.com/p/minini/wiki/INI_File_Syntax

void FS::ImageServer::process_ping_(tcp::socket& sock)
{
  std::cout << "processing PING..." << std::endl;
  const char * data = "\002PONG PING\003";
//        "\002PING FocusStacking ImageServer version 0.1 \n"
//    "Database: 123e4567e89b12d3a452426655440000\003";
  size_t length = std::strlen(data);
  boost::asio::write(sock, boost::asio::buffer(data, length));
  // reset the state to process the next input
  set_state_(waiting_for_start);
}

void FS::ImageServer::create_new_stack_(tcp::socket& sock)
{
  
  //const 
  const char * data = //"\002PONG PING\003";
        "\002PING FocusStacking ImageServer version 0.1 \n"
    "Database: 123e4567e89b12d3a452426655440000\003";
  size_t length = std::strlen(data);
  boost::asio::write(sock, boost::asio::buffer(data, length));
  // reset the state to process the next input
  set_state_(waiting_for_start);
}



void FS::ImageServer::db_logic_(boost::asio::ip::tcp::socket& sock,
				FrameReadState * rs)
{
  // read all data until complete frame has been read
  //while (
  std::cout << "processing data ..." << std::endl;
  std::string sHead;
  for(size_t i = 0; i < HEADER_LEN; i++) sHead += rs->header[i];
  std::cout << "Header is " << sHead << std::endl;
  if (sHead == "PING")
    process_ping_(sock);
  else if (sHead == "GTID")
    create_new_stack_(sock);
}


// Using for not echo example
void FS::ImageServer::session_(tcp::socket sock)
{
  try {
  // get id for the current thread
  const std::thread::id tid = std::this_thread::get_id();
  // when a new connection starts, it's waiting for the start of packet
  state_t state = waiting_for_start;
  state_map_->insert(std::pair<std::thread::id, state_t>(tid,state));
  // read bytes until EOF
  for(;;)
    {
      char data[max_msg_len];
      FrameReadState read_state;

      boost::system::error_code error;
      read_state.length = sock.read_some(
			     boost::asio::buffer(data, max_msg_len),
			     error);
      std::cout << "Read " << read_state.length <<
	" bytes from client" << std::endl;
      
      
      // testing process_db_() and read_settings_(),
      // not being called anywhere else. 
      //std::cout << "Processing ping, testing database" << std::endl;
      //process_db_();
      
      if (error == boost::asio::error::eof)
	break; // Connection closed cleanly by peer.
      else if (error)    
	throw boost::system::system_error(error); // Some other error.

      while (read_state.data_index != read_state.length) {
      	
	switch(get_state_())
	  {
	  case waiting_for_start:
	    detect_start_msg_(data, &read_state);
	    break;
	  case reading_header:
	    parse_frame_id_(data, &read_state);
	    break;
	  case reading_data:
	    db_logic_(sock, &read_state);
	    break;
	  }
      
      }
      //boost::asio::write(sock, boost::asio::buffer(data, length));
	
    }
  }
  catch(std::exception& e)
    {
      std::cerr << "Exception: " << e.what() << std::endl;
    }
  
}

void FS::ImageServer::server_(boost::asio::io_service& io_service,
			      unsigned short port)
{
  tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
  for (;;)
  {
    //try {
      tcp::socket sock(io_service);
      a.accept(sock);
      // starting a new thread here
      std::thread(session_, std::move(sock)).detach();
      //} catch()
  }
}

void FS::ImageServer::detect_start_msg_(char * data, FrameReadState *rs)
{
  uint i;
  for (i = 0; i < rs->length; i++) {
    if (data[i] == '\002') {
      set_state_(reading_header);
      rs->header_pos = 0;
      i++;
      break;
    }
  }
  rs->data_index += i;
}

