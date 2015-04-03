
#include "ImageServer.h"
#include <iostream>
#include <stdexcept>
#include <string>

#define L10N_INC "ResourceStrFRA.inc"

// example of a namespace alias
namespace FS = LMFocusStack;

FS::ImageServer::ImageServer(int argc, char ** argv) {

	const std::string help = "--help";
	if (argc < 2) { // settings file not specified, use default
		
	} else { // load settings or display help
		#include L10N_INC
		if (argv[1] == help) {
			std::cout << rstr_help << std::endl;
		}
	} 
}

int FS::ImageServer::start_server() {
	return 0;
}

