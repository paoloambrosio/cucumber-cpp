#include <cucumber-cpp/internal/connectors/wire/WireServer.hpp>
#include <cstdio>

namespace cucumber {
namespace internal {

template <>
template <>
void SocketServer<boost::asio::ip::tcp>::listen(unsigned short const& port) {
    tcp::endpoint endpoint(tcp::v4(), port);
    acceptor.open(endpoint.protocol());
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    acceptor.bind(endpoint);
    acceptor.listen(1);
}

template <>
template <>
void SocketServer<boost::asio::local::stream_protocol>::listen(std::string const& path) {
	std::remove(path.c_str());
	local::stream_protocol::endpoint endpoint(path);
    acceptor.open(endpoint.protocol());
    acceptor.bind(endpoint);
    acceptor.listen(1);
}

}
}
