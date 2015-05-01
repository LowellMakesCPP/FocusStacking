#include <iostream>
#include "ImageServer.h"

#define STR_EXPAND(tok) #tok
#define STR(tok) STR_EXPAND(tok)

// PManandhar note: not preferred, used for demo
// or short files
using namespace LMFocusStack;
using namespace std;

int options(char ** argv) {
  // Task 1.1: exit after help. Insert a flag after help, if that
  // flag exists then exit the program in main; return 0.
  // (Try to do this in the main function)
  
  const std::string help = "--help";
  if (argv[1] == help) {
    #include STR(L10N_LANG)
    std::wcout << rstr_help << std::endl;
    return -1;
  }
  else {
    return 0;
  }
}

int main(int argc, char ** argv) {
  
  if (argc >= 2 && options(argv) == -1){
    std::cout << "Program closing" << std::endl;

    return -1;
    
  }
  else {

    try
      {
	ImageServer server(argc, argv);

	server.start_server();
    
      }
    catch (std::exception& e)
      {
	std::cerr << "Exception: " << e.what() << "\n";
      }

    return 0;
  }
    
}
