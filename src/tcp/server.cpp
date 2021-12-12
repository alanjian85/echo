#include "tcp/server.hpp"
using namespace echo::tcp;

void server::do_accept() {
    auto new_connection = std::make_shared<connection>(io_context_);
    acceptor_.async_accept(new_connection->socket(),
        [this, new_connection](asio::error_code error) {
            if (!error) {
                new_connection->start();
            }

            do_accept();
        });
}
