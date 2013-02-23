#ifndef CUKE_WIRESERVER_HPP_
#define CUKE_WIRESERVER_HPP_

#include "ProtocolHandler.hpp"

#include <string>

#include <boost/asio.hpp>

namespace cucumber {
namespace internal {

using namespace boost::asio;
using namespace boost::asio::ip;

/**
 * Socket server that calls a protocol handler line by line
 */
template <class Protocol=boost::asio::ip::tcp>
class SocketServer {
public:
    /**
      * Constructor for DI
      */
	SocketServer(const ProtocolHandler *protocolHandler) :
		ios(),
		acceptor(ios),
		protocolHandler(protocolHandler) {
		}

    /**
     * Bind and listen to a port (or unix domain socket)
     */
	template <class Identifier>
    void listen(Identifier const& port);

    /**
     * Accept one connection
     */
    void acceptOnce()
	{
		typename Protocol::iostream stream;
		acceptor.accept(*stream.rdbuf());
		processStream(stream);
	}

    ~SocketServer() {}; // Forbid inheritance

private:
    const ProtocolHandler *protocolHandler;
    io_service ios;
    typename Protocol::acceptor acceptor;

	void processStream(typename Protocol::iostream &stream) {
		std::string request;
		while (getline(stream, request)) {
			stream << protocolHandler->handle(request) << std::endl << std::flush;
		}
	}
};

template <>
template <>
void SocketServer<boost::asio::ip::tcp>::listen(unsigned short const& port);

template <>
template <>
void SocketServer<boost::asio::local::stream_protocol>::listen(std::string const& path);

}
}

#endif /* CUKE_WIRESERVER_HPP_ */
