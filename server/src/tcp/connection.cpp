#include "tcp/connection.hpp"
using namespace echo::server::tcp;

void connection::do_read() {
    auto self = shared_from_this();
    socket_.async_read_some(asio::buffer(message_),
        [this, self](asio::error_code error, std::size_t length) {
            if (!error) {
                do_write(length);
            }
        });
}

void connection::do_write(std::size_t length) {
    auto self = shared_from_this();
    asio::async_write(socket_, asio::buffer(message_, length),
        [this, self](asio::error_code error, std::size_t) {
            if (!error) {
                do_read();
            }
        });
}
