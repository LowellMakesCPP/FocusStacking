#ifndef LMFS_IMAGESERVER_H
#define LMFS_IMAGESERVER_H

#include <string>

/*! \file ImageServer.h
 *
 * \brief Declarations for the focus-stack server.
 * 
 * \copyright Copyright 2015 Prakash Manandhar, Suraj Adhikari, 
        Tyler Brown and Chris Fields. 
 * \license This project is released under the GNU Public License.
 */

//! Namespace for Lowell-Makes C++ Course FocusStack project
namespace LMFocusStack {

	//! processes help message


	//! stores focus-stacks
	class ImageServer {

	public:

		const char * program_version = "FSImServ 0.1";
		enum { max_msg_len = (10240 + 100) }; 

		/*!
                 * Initialize image-server and parse parameters.
                 */
		ImageServer(int argc, char ** argv);

		int start_server ();

	private:
		std::string settings_path_; // settings path
		const char * def_settings_ = "FStk.ini";

		// database path, note that it is initialized to empty
		std::string db_path_; 

		//! could have been protected if we were writing an API
		void load_settings();
		void load_settings_line(const char * buffer, const int LEN);

		// create default settings file if given file does not exist
		void create_default_settings();
	};

} // end namespace LMFocusStack

#endif
