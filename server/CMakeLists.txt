cmake_minimum_required(VERSION 3.13)
project(async_server)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DBOOST_LOG_DYN_LINK)
find_package(Boost COMPONENTS REQUIRED
    log
    program_options
    system)
find_package(Threads)

add_executable(${PROJECT_NAME}
    main.cpp
    tcp_server.cpp
    acceptor.cpp
    service.cpp
    server_base.cpp)

target_link_libraries(${PROJECT_NAME}
    ${Boost_LIBRARIES})

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_SOURCE_DIR}/bin)
