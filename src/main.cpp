#include "tcp/server.hpp"
#include "udp/server.hpp"

int main() {
    asio::io_context io_context;
    echo::tcp::server tcp_server(io_context);
    echo::udp::server udp_server(io_context);
    io_context.run();
    return 0;   
}
