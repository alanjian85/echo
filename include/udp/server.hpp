#ifndef ECHO_SERVER_HPP
#define ECHO_SERVER_HPP

#include <asio.hpp>

namespace echo {
    namespace udp {
        class server {
        public:
            server(asio::io_context& io_context)
                : io_context_(io_context),
                  socket_(io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 7))
            {
                do_receive();
            }
        private:
            void do_receive() {
                socket_.async_receive_from(asio::buffer(buffer_), endpoint_,
                    [this](asio::error_code error, std::size_t length) {
                        if (!error && length > 0) {
                            do_send(length);
                        } else {
                            do_receive();
                        }
                    });
            }

            void do_send(std::size_t length) {
                socket_.async_send_to(asio::buffer(buffer_, length), endpoint_,
                    [this](asio::error_code, std::size_t) {
                        do_receive();
                    });
            }
        private:
            asio::io_context& io_context_;
            asio::ip::udp::socket socket_;
            asio::ip::udp::endpoint endpoint_;
            char buffer_[512];
        };
    }
}

#endif
