#include "tcp_server.hpp"
#include "acceptor.hpp"
#include <boost/log/trivial.hpp>

namespace async
{

tcp_server::tcp_server(uint16_t port_num, uint32_t thread_pool_size) :
    server_base(thread_pool_size),
    port_num_(port_num),
    acc_(std::make_unique<acceptor>(io_service_, port_num_))
{
}

tcp_server::~tcp_server()
{
}

bool tcp_server::do_init()
{
    acc_->start();
    BOOST_LOG_TRIVIAL(info) << "Server Started. Listening to port " << port_num_;
    return true;  // TODO: check should be done.
}

bool tcp_server::do_close()
{
    acc_->stop();
    return true; // TODO: check should be done.
}

}
