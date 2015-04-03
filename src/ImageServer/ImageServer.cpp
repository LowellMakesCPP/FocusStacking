
#include "ImageServer.h"
#include <iostream>
#include <stdexcept>
#include <string>

#define STR_EXPAND(tok) #tok
#define STR(tok) STR_EXPAND(tok)
 
// example of a namespace alias
namespace FS = LMFocusStack;

FS::ImageServer::ImageServer(int argc, char ** argv) {

	const std::string help = "--help";
	if (argc < 2) { // settings file not specified, use default
		
	} else { // load settings or display help
		#include STR(L10N_LANG)
		if (argv[1] == help) {
			std::cout << rstr_help << std::endl;
		}
	} 
}

int FS::ImageServer::start_server() {
	return 0;
}

