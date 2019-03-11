#ifndef TCP_CLIENT_HPP
#define TCP_CLIENT_HPP

#include <boost/asio.hpp>
#include <thread>

namespace fizyr
{

namespace basio = boost::asio;

/**
 * \brief Simple asynchronous tcp client that run the io_service off in its own thread.
 *        It operates completely asynchronously with respect to the rest of the program.
 */
class tcp_client
{
public:
    /**
     * \brief Constructor initializes the tcp socket and start the io_service.
     * \param ip_addr remote server IP address.
     * \param port number to which the client send the request.
     */
    tcp_client(const std::string& ip_addr, uint16_t port);

    /**
     * \brief Stop the io_service
     */
    ~tcp_client();

    /**
     * \brief Send request to the server.
     * \param request the message send to server.
     */
    void send_request(const std::string& request);

private:
    std::string ip_addr_;
    uint16_t port_num_;
    basio::io_service ios_;
    basio::io_service::work work_;
    basio::ip::tcp::socket sock_;
    std::unique_ptr<std::thread> thread_;
};

}

#endif

