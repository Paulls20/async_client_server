cmake_minimum_required(VERSION 3.13)
project(async_client)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DBOOST_LOG_DYN_LINK)
find_package(Boost COMPONENTS log program_options system REQUIRED)
find_package(Threads)

add_executable(${PROJECT_NAME}
    main.cpp
    tcp_client.cpp)

target_link_libraries(${PROJECT_NAME}
    ${Boost_LIBRARIES})

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_SOURCE_DIR}/bin)