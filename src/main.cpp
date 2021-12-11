#include <thread>
#include <exception>
#include <iostream>

#include <asio.hpp>

using asio::ip::tcp;

void session(tcp::socket socket) {
    try {
        for (;;) {
            char buffer[512];
            asio::error_code error;
            auto length = socket.read_some(asio::buffer(buffer), error);
            if (error == asio::error::eof)
                break;
            else if (error)
                throw asio::system_error(error);
            asio::write(socket, asio::buffer(buffer, length));
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

int main() {
    asio::io_context io_context;
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 7));
    for (;;) {
        auto socket = acceptor.accept();
        std::thread(session, std::move(socket)).detach();
    }
    return 0;   
}
