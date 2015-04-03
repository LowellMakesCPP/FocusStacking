#ifndef LMFS_IMAGESERVER_H
#define LMFS_IMAGESERVER_H

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
		const char * def_settings_ = "FStk.ini";
	};

} // end namespace LMFocusStack

#endif
