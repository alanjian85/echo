#include <iostream>
#include <stdexcept>

#include "tcp/server.hpp"
#include "udp/server.hpp"
using namespace echo::server;

int main() {
    try {
        asio::io_context io_context;
    
        tcp::server tcp_server(io_context);
        udp::server udp_server(io_context);
    
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;   
}
