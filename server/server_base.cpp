#include "server_base.hpp"
#include <boost/log/trivial.hpp>

namespace fizyr
{

server_base::server_base(uint32_t thread_pool_size) :
    thread_pool_size_(thread_pool_size)
{
}

void server_base::start()
{
    if (do_init())
    {
        // Create the thread pool
        for (auto i = 0u; i < thread_pool_size_; ++i)
        {
            auto th = std::make_unique<std::thread>(
                [this]()
                {
                    ios_.run();
                });

            thread_pool_.push_back(std::move(th));
        }
    }
}

void server_base::stop()
{
    if(do_close())
    {
        ios_.stop();

        for (auto &th : thread_pool_)
        {
            th->join();
        }
    }
}

}