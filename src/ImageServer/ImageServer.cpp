
#include "ImageServer.h"
#include <iostream>
#include <stdexcept>
#include <string>

// example of a namespace alias
namespace FS = LMFocusStack;

FS::ImageServer::ImageServer(int argc, char ** argv) {

	const std::string help = "--help";
	if (argc < 2) { // settings file not specified, use default
		
	} else { // load settings or display help
		if (argv[1] == help) {
			//std::string test =L"Latin text на кирилица and more latin";
			std::cout << "हामिछ" << std::endl;
			//std::cout << "Help Message" << std::endl;
		}
	} 
}

int FS::ImageServer::start_server() {
	return 0;
}

