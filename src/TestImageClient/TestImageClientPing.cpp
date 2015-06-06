
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

enum { max_length = (10240 + 100) };

std::string 
parse_ping_reply (char * reply, size_t reply_length, 
	bool &start_found, bool &end_found) {

	std::string s;
	for(size_t i = 0; i < reply_length; i++)
	{
		if (!start_found) {
			if (reply[i] == '\002')
				start_found = true;
			continue;
		}
		if (reply[i] == '\003') {
			end_found = true;
			break; // message end
		}
		s += reply[i];
	}
	std::cout << "parsing reply " << s << std::endl;
	return s;
}

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: TestImageClientPing <host> <port>\n";
      return 1;
    }

    boost::asio::io_service io_service;

    tcp::socket s(io_service);
    tcp::resolver resolver(io_service);
    boost::asio::connect(s, resolver.resolve({argv[1], argv[2]}));

    const char * request = "\002PING\003";
    size_t request_length = std::strlen(request);
    std::cout << "Sending PING to " 
	<< argv[1] << ": " << argv[2]
	<< ", Length is " << request_length << std::endl;
    boost::asio::write(s, boost::asio::buffer(request, request_length));

    char reply[max_length];
    bool start_found = false;
    bool end_found = false;
    std::string rs;
    while ( ! end_found ) {
    	size_t reply_length = boost::asio::read(s,
        boost::asio::buffer(reply, request_length));
	rs += parse_ping_reply(reply, reply_length, 
		start_found, end_found);
	std::cout << "Reply length is " << reply_length << std::endl;

	}
    std::cout 
      << "Found: " << rs 
      << " Start: " << start_found 
      << " End: " << end_found << std::endl;

    // print out the ping 
    std::cout << rs << "\n";
  }
  
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
