#include "Server.h"
#include "Logger.h"

#include <iostream> 
#include <boost/asio.hpp>
#include <sstream> // for ostringstream used in logger
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/asio/ssl.hpp>

namespace ssl = boost::asio::ssl;
using ssl_socket = ssl::stream<tcp::socket>;

int main(int argc, char* argv[]){

	if(argc < 2){
		return -1;
	}

	// Create a root
	boost::property_tree::ptree root;
	// Load the json file in this ptree
	boost::property_tree::read_json(argv[1], root);
	std::string type = root.get<std::string> ("LogLevel");
	
	Logger logger1(type);

    logger1.log("    \"Proxy Server\"", "info");

	// create a buffer to make log with it using ostringstream
	std::ostringstream tmp;  

	int port = 1080;
	size_t buffer_size = 8192;

	try {

		boost::asio::io_service io_service;
		ssl::context ssl_context(ssl::context::tls);
		// boost::asio::io_context io_context;
		ssl_socket socket(io_service, ssl_context);
		Server server(io_service, port, buffer_size, logger1.getConfigType());
		server.start(argv[1]);
		io_service.run();
	
	} catch (std::exception& e) {

		tmp << "exception: " << e.what();
		logger1.log(tmp.str(), "error");

	}

	return 0;
}
