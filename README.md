# TCP/IP

## Description
This repository illustrates a simple usage of tcp/ip. \
In this repository, there is a `tcpIp.cc` file. This is a server that make use of tcp/ip.

## Build
Install `g++` if not already exist in your host. \
Run on your terminal `g++ -std=c++17 tcpIp.cc -o tcpIp`.

## Run
### Server
Run on your terminal `./tcpIp`. This command runs the server.

### Client
Install `telnet` if not alreay exist in your host. \
Open a new a terminal and run `telnet localhost 54000`. \
Now type in any message, the same message will be printed in the server, and echoed back to the client.
