#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

#define INVALID_SOCKET          (~0)
#define SOCKET_ERROR            (-1)

void showErrorMessage(std::string message)
{
  std::cerr << "[ERROR]: " << message << std::endl;
}

int main() 
{
  // server socket
  int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket == INVALID_SOCKET)
  {
    showErrorMessage("Can't create a socket.");
    return -1;
  }

  // create a bind information
  sockaddr_in serverAddress;
  socklen_t serverAddressSize = sizeof(serverAddress);
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(54000);
  inet_pton(AF_INET, "0.0.0.0", &serverAddress.sin_addr);

  // bind the socket to ip and port
  if (bind(serverSocket, (sockaddr *)&serverAddress, serverAddressSize) == SOCKET_ERROR)
  {
    showErrorMessage("Can't bind to IP/port.");
    return -2;
  }

  // Mark the server socket for listening in
  if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
  {
    showErrorMessage("Can't listen.");
    return -3;
  }

  // Accept a call
  sockaddr_in clientAddress;
  socklen_t clientAddressSize = sizeof(clientAddress);

  // Accept an incoming connection
  int clientSocket = accept(serverSocket, (sockaddr *)&serverAddress, &clientAddressSize);

  if (clientSocket == SOCKET_ERROR)
  {
    showErrorMessage("Problem with client connecting!");
    return -4;
  }

  std::cout << "Client address: " << inet_ntoa(clientAddress.sin_addr) << " and port: " << ntohs(clientAddress.sin_port) << std::endl;

  // close the server socket
  close(serverSocket);

  // while receiving, display message 
  char buf[4096];

  while (true)
  {
    // clear the buffer
    memset(buf, 0, 4096);

    // wait for a message
    int bytesRecv = recv(clientSocket, buf, 4096, 0);

    if (bytesRecv == -1)
    {
      showErrorMessage("There was a connection issue.");
      break;
    }

    if (bytesRecv == 0)
    {
      std::cout << "The client disconnected." << std::endl;
      break;
    }

    // display message
    std::cout << "Received: " << std::string(buf, 0, bytesRecv) << std::endl;

    // resend message
    send(clientSocket, buf, bytesRecv + 1, 0);
  }

  // close socket
  close(clientSocket);

  return 0;
}
