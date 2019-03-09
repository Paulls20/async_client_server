# async_client_server

Command-line server and client in C++ using asynchronous communication using boost ASIO.

## Prerequisites:

1. Boost libraries
```bash
sudo apt -y install libboost-dev
```
2. CMake >= 3.13
3. Compiler which supports C++14 (_Note_: Currently tested only with GCC).

## Steps to build:

```bash
git clone https://github.com/Paulls20/async_client_server.git
mkdir build && cd build
cmake ..
make
make install
```
```make install``` installs the binaries to the ```bin``` directory.

## How to start the server:

```
cd ../bin
./async_server
[2019-03-09 16:02:13.769580] [0x00007f68e0dfb740] [info]    Server Started. Listening to port 3333
```
By default server starts listening to port 3333. But ofcourse you can change the port with --port arg as shown.
```bash
./async_server  -h
Options:
  -h [ --help ]         Help screen
  --port arg (=3333)    Port Number
```

## How to run the client:

Open the ```bin``` directory in another terminal:
```bash
./async_client
IP: 127.0.0.1
Port: 3333
Enter request: Hello World
Response:Hello World back
```
By default the client connects to 127.0.0.1 and port 3333. Like the server, you can also start the client to connect to a different host and port as shown.
```bash
./async_client  -h
Options:
  -h [ --help ]         Help screen
  --port arg (=3333)    Port
  --ip arg (=127.0.0.1) IP Address
```

## Limitations:
1. In the current implementation Server runs only for 60 seconds.
2. Client's response buffer size is set to 128 bytes.
