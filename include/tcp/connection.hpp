#ifndef ECHO_CONNECTION_HPP
#define ECHO_CONNECTION_HPP

#include <memory>

#include <asio.hpp>

namespace echo {
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
            void do_read() {
                auto self = shared_from_this();
                socket_.async_read_some(asio::buffer(message_),
                    [this, self](asio::error_code error, std::size_t length) {
                        if (!error) {
                            length_ = length;
                            do_write();
                        }
                    });
            }

            void do_write() {
                auto self = shared_from_this();
                asio::async_write(socket_, asio::buffer(message_, length_),
                    [this, self](asio::error_code error, std::size_t) {
                        if (!error) {
                            do_read();
                        }
                    });
            }
        private:
            asio::ip::tcp::socket socket_;
            char message_[512];
            std::size_t length_;
        };
    }
}

#endif
