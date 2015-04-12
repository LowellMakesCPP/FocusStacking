
#include "ImageServer.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include <assert.h>
#include <boost/filesystem.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/regex.hpp>

#define STR_EXPAND(tok) #tok
#define STR(tok) STR_EXPAND(tok)
 
// example of a namespace alias
namespace FS = LMFocusStack;
namespace bfs = boost::filesystem;

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

int FS::ImageServer::start_server() {
	using boost::asio::ip::tcp;
	
	return 0;
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
	
}

void FS::ImageServer::create_default_settings() {
	using namespace boost::posix_time;
	using namespace boost::gregorian;

	ptime now = second_clock::local_time();

	std::ofstream fout(settings_path_, std::ofstream::out);
	
	fout << "; Focus Stacking Image Server settings file V 1.0\n"
		"; Automatically created by " << program_version << "\n"
		"; " << to_simple_string(now) << std::endl <<
		"database = FSImSrvDb\n";

	fout.close();
}

/* TODO: review blocking_tcp_echo_server.cpp and add echo server
         methods to interface with ping client example.
*/

void FS::ImageServer::session(socket_ptr sock)
{
  break;
}
