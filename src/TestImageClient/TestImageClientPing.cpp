
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

enum { max_length = (10240 + 100) };

std::string 
parse_ping_reply (char * reply) {

	std::string s;
	bool message_start = false; 
	for(int i = 0; i < max_length; i++)
	{
		if (!message_start) {
			if (reply[i] == '\000')
				message_start = true;
			continue;
		}
		if (reply[i] == '\004') break; // message end
		s += reply[i];
	}
	return reply;
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

    std::cout << "Sending PING to " 
 	 << argv[1] << ": " << argv[2] << std::endl;
    const char * request = "\000PING\004";
    size_t request_length = std::strlen(request);
    boost::asio::write(s, boost::asio::buffer(request, request_length));

    char reply[max_length];
    size_t reply_length = boost::asio::read(s,
        boost::asio::buffer(reply, request_length));
    std::string rs = parse_reply(reply);
    std::cout << rs << "\n";
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
