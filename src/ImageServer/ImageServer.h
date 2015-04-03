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

	//! stores focus-stacks
	class ImageServer {

	public:
		/*!
                 * Initialize image-server and parse parameters.
                 */
		ImageServer(int argc, char ** argv);

		int start_server ();

	private:
		std::string settings_path_; // settings path
		const char * def_settings_ = "FStk.ini";

		//! could have been protected if we were writing an API
		void load_settings();
		void load_settings_line(const char * buffer, const int LEN);
	};

} // end namespace LMFocusStack

#endif
