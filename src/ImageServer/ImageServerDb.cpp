/**
 * Isolates database related functions of ImageServer.
 */

#include "ImageServer.h"
#include <iostream>
#include <boost/filesystem.hpp>

#define STR_EXPAND(tok) #tok
#define STR(tok) STR_EXPAND(tok)

namespace FS = LMFocusStack;
namespace bfs = boost::filesystem;

/**
 * Creates the database folder if it doesn't exist.
 */
void FS::ImageServer::create_db_ifmissing_()
{
	#include STR(L10N_LANG)
	
	// check if folder exists and is not a file
	// if file doesn't exist create a folder
	bfs::path p (this->db_path_);
	if ( !bfs::exists(p) )
			create_db_ ();
	if ( !bfs::is_directory(p) ) 
		throw std::invalid_argument (
				rstr_dbNotDir + db_path_ );
	
}

void FS::ImageServer::create_db_() {
	
}

void FS::ImageServer::create_update_db_()
/* According to DatabaseFormat.md, we need to:
 * 1b) create or update a database directory
 */
{
/*
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
*/
}


