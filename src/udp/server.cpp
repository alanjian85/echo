#include "udp/server.hpp"
using namespace echo::udp;

void server::do_receive() {
    socket_.async_receive_from(asio::buffer(buffer_), endpoint_,
        [this](asio::error_code error, std::size_t length) {
            if (!error && length > 0) {
                do_send(length);
            } else {
                do_receive();
            }
        });
}

void server::do_send(std::size_t length) {
    socket_.async_send_to(asio::buffer(buffer_, length), endpoint_,
        [this](asio::error_code, std::size_t) {
            do_receive();
        });
}
