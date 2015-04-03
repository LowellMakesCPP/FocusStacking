
#include "ImageServer.h"
#include <stdexcept>

// example of a namespace alias
namespace FS = LMFocusStack;

FS::ImageServer::ImageServer(int argc, char ** argv) {
	
	if (argc < 2) { // settings file not specified, use default
		
	} else { // load settings or display help
		
	} 
}

int FS::ImageServer::start_server() {
	return 0;
}

