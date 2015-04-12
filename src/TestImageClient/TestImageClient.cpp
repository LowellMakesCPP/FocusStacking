
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char ** argv) {
	try {
		if (argc != 3)
		{
			std::cerr << "Usage: TestImageClient <host> <port>" 
				<< std::endl;
		}

		boost::asio::io_service io_service;
		
		tcp::resolver resolver(io_service);
		tcp::resolver::query query(argv[1], argv[2]);		

		tcp::resolver::iterator iterator = resolver.resolve(query);

		tcp::socket socket(io_service);
		

		return 0;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
