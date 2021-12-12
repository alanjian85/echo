#include "tcp/server.hpp"

int main() {
    asio::io_context io_context;
    echo::tcp::server tcp_server(io_context);
    io_context.run();
    return 0;   
}
