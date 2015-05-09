#ifndef LMFS_IMAGESERVER_H
#define LMFS_IMAGESERVER_H

#include <string>
#include <thread>
#include <map>
#include <vector>
#include <boost/asio.hpp>

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

		void start_server ();

	private:
		std::string settings_path_; // settings path
		const char * def_settings_ = "FStk.ini";

		// database path, note that it is initialized to empty
		std::string db_path_;
		unsigned short port_ = 8080; // tcp/ip port number

		//! could have been protected if we were writing an API
		void load_settings();
		void load_settings_line(const char * buffer,
	                                const int LEN);

		// create default settings file if given file does not exist
		void create_default_settings();

		// parse tcp/ip from echo client
		static void session_(boost::asio::ip::tcp::socket);

		void server_(boost::asio::io_service&,
	                     unsigned short port);

		enum state_t { waiting_for_start,
	                       reading_header,
	                       reading_data};

		static std::map<std::thread::id, state_t> * state_map_;
		void detect_start_msg_(char *, size_t length);
		
	};

} // end namespace LMFocusStack

#endif
