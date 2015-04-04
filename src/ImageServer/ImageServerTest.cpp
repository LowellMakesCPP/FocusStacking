#include <iostream>
#include "ImageServer.h"

// PManandhar note: not preferred, used for demo
// or short files
using namespace LMFocusStack;
using namespace std;

int main(int argc, char ** argv) {

  try {
	ImageServer server(argc, argv);

	return 0;
	
  }
  catch (exception &e) {
    // Tyler note: http://isocpp.org/wiki/faq/exceptions#ctors-can-throw
        std::cerr << "Program closing: " << e.what();
        return -1;
  }
 
}

