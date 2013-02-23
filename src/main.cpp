#include <cucumber-cpp/internal/CukeEngineImpl.hpp>
#include <cucumber-cpp/internal/connectors/wire/WireServer.hpp>
#include <cucumber-cpp/internal/connectors/wire/WireProtocol.hpp>
#include <iostream>

namespace {

template <class Protocol, class Identifier>
void acceptWireProtocol(Identifier const& port) {
    using namespace ::cucumber::internal;
    CukeEngineImpl cukeEngine;
    JsonSpiritWireMessageCodec wireCodec;
    WireProtocolHandler protocolHandler(&wireCodec, &cukeEngine);
    SocketServer<Protocol> server(&protocolHandler);
    server.listen(port);
    server.acceptOnce();
}

}

int main(int argc, char **argv) {
    try {
        unsigned short port = 3902;
		std::string unix_socket;

        if (argc > 1) {

            std::string firstArg(argv[1]);

			try {
				port = ::cucumber::internal::fromString<int>(firstArg);
			} catch (...) {
				unix_socket = firstArg;
			}
        }

		if (unix_socket.empty()) {
			std::clog << "Listening on port " << port << std::endl;
			acceptWireProtocol<boost::asio::ip::tcp>(port);
		} else {
			std::clog << "Listening on " << unix_socket << std::endl;
			acceptWireProtocol<boost::asio::local::stream_protocol>(unix_socket);
		}

    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    return 0;
}
