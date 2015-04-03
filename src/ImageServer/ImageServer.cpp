
#include "ImageServer.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>

#define STR_EXPAND(tok) #tok
#define STR(tok) STR_EXPAND(tok)
 
// example of a namespace alias
namespace FS = LMFocusStack;

FS::ImageServer::ImageServer(int argc, char ** argv) {

	const std::string help = "--help";
	if (argc < 2) 
	{ // settings file not specified, use default
		this->settings_path_ = def_settings_;
	} 
	else { // load settings or display help
		if (argv[1] == help) {
			#include STR(L10N_LANG)
			std::wcout << rstr_help << std::endl;
		} else {
			settings_path_ = argv[1];
		}
	} 
	load_settings(); // could throw invalid settings exception
}

int FS::ImageServer::start_server() {
	return 0;
}

void FS::ImageServer::load_settings() {
	std::ifstream fin;
	fin.close();
	try {
		const int BUF_LEN = 4096;
		char buffer[BUF_LEN];
		// try to open the settings file
		fin.open(this->settings_path_);
		if (!fin.good()) 
			throw std::invalid_argument
				("Cannot access settings file: "
					+ settings_path_);
		
		// read one line at a time
		while (fin.good()) {
			fin.getline(buffer, BUF_LEN);
		}
		
	} catch (...) {
		fin.close();
	}
}
