#include "acceptor.hpp"
#include "service.hpp"
#include <boost/log/trivial.hpp>

namespace fizyr
{

acceptor::acceptor(basio::io_service& ios, unsigned short port_num) :
    ios_(ios),
    acceptor_(ios_,
              basio::ip::tcp::endpoint(
                  basio::ip::address_v4::any(),
                  port_num)),
    is_stopped_(false)
{
}

void acceptor::start()
{
    acceptor_.listen();
    init_accept();
}

void acceptor::stop()
{
    is_stopped_.store(true);
}

void acceptor::init_accept()
{
    auto sock = std::make_shared<basio::ip::tcp::socket>(basio::ip::tcp::socket(ios_));

    auto accept_callback = [this, sock](
        const boost::system::error_code& error)
    {
        on_accept(error, sock);
    };

    acceptor_.async_accept(*sock.get(), accept_callback);
}

void acceptor::on_accept(
    const boost::system::error_code& ec,
    std::shared_ptr<basio::ip::tcp::socket> sock)
{
    if (not ec)
    {
        // This service object will get deleted in service::on_finished()
        (new service(std::move(sock)))->start_handling();
    }
    else
    {
        BOOST_LOG_TRIVIAL(error) << "Error code = "
                                 << ec.value()
                                 << ". Message: " << ec.message();
    }

    // Init next async accept operation if
    // acceptor has not been stopped yet.
    if (not is_stopped_.load())
    {
        init_accept();
    }
    else
    {
        // Stop accepting incoming connections
        // and free allocated resources.
        acceptor_.close();
    }
}

}