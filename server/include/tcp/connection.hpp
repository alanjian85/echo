#ifndef ECHO_CONNECTION_HPP
#define ECHO_CONNECTION_HPP

#include <memory>

#include <asio.hpp>

namespace echo {
    namespace server {
        namespace tcp {
            class connection : public std::enable_shared_from_this<connection> {
            public:
                connection(asio::io_context& io_context)
                    : socket_(io_context)
                {
                
                }

                asio::ip::tcp::socket& socket() {
                    return socket_;
                }

                const asio::ip::tcp::socket& socket() const {
                    return socket_;
                }
        
                void start() {
                    do_read();
                }
            private:
                void do_read();
                void do_write(std::size_t length);
            private:
                asio::ip::tcp::socket socket_;
                char message_[512];
            };
        }
    }
}

#endif
