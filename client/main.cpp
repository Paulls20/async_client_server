#include <boost/program_options.hpp>
#include <iostream>
#include "tcp_client.hpp"

int main(int argc, const char *argv[])
{
    uint16_t port_num = 3333;
    std::string ip_addr = "127.0.0.1";
    namespace po = boost::program_options;
    try
    {
        po::options_description desc{"Options"};
        desc.add_options()
            ("help,h", "Help screen")
            ("port", po::value<float>()->default_value(3333), "Port")
            ("ip", po::value<std::string>()->default_value("127.0.0.1"), "IP Address");

        po::variables_map vm;
        store(parse_command_line(argc, argv, desc), vm);
        notify(vm);

        if (vm.count("help"))
        {
            std::cout << desc << '\n';
            return 0;
        }
        if (vm.count("ip"))
        {
            ip_addr = vm["ip"].as<std::string>();
            std::cout << "IP: " << vm["ip"].as<std::string>() << '\n';
        }
        if (vm.count("port"))
        {
            port_num = vm["port"].as<float>();
            std::cout << "Port: " << port_num << '\n';
        }
    }
    catch (const po::error &ex)
    {
        std::cerr << ex.what() << '\n';
    }

    std::string request;
    do
    {
        std::cout << "Enter request: ";
        std::cin >> request;
        fizyr::tcp_client tc(ip_addr, port_num);
        tc.send_request(request + "\n");
    } while(request != "q");
}