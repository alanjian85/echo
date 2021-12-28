#ifndef ECHO_SERVER_HPP
#define ECHO_SERVER_HPP

#include <asio.hpp>

namespace echo {
    namespace server {
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
                void do_receive();
                void do_send(std::size_t length); 
            private:
                asio::io_context& io_context_;
                asio::ip::udp::socket socket_;
                asio::ip::udp::endpoint endpoint_;
                char buffer_[512];
            };
        }
    }
}

#endif
