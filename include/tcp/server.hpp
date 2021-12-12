#ifndef ECHO_TCP_SERVER_HPP
#define ECHO_TCP_SERVER_HPP

#include <asio.hpp>

#include "connection.hpp"

namespace echo {
    namespace tcp {
        class server {
        public:
            server(asio::io_context& io_context)
                : io_context_(io_context),
                  acceptor_(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 7))
            {
                do_accept();
            }

            void do_accept() {
                auto new_connection = std::make_shared<connection>(io_context_);
                acceptor_.async_accept(new_connection->socket(),
                    [this, new_connection](asio::error_code error) {
                        if (!error) {
                            new_connection->start();
                        }

                        do_accept();
                    });
            }
        private:
            asio::io_context& io_context_;
            asio::ip::tcp::acceptor acceptor_;
        };
    }
}

#endif
