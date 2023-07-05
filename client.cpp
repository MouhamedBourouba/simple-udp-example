#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080
#define BUFFER_SIZE 1024

using namespace std;

int main() {
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) {
    cerr << "Error creating socket." << endl;
    return 1;
  }

  struct sockaddr_in serverAddr {};
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(SERVER_PORT);
  if (inet_pton(AF_INET, SERVER_IP, &(serverAddr.sin_addr)) <= 0) {
    cerr << "Invalid server address." << endl;
    close(sockfd);
    return 1;
  }

  socklen_t serverAddrLen = sizeof(serverAddr);
  for (;;) {
    char message[BUFFER_SIZE];
    cout << "Enter a message: ";
    cin.getline(message, sizeof(message));

    ssize_t bytesSent =
        sendto(sockfd, message, strlen(message), 0,
               (const struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (bytesSent <= 0) {
      cerr << "Error sending message." << endl;
      close(sockfd);
      return 1;
    }
    char buffer[BUFFER_SIZE];

    int receivedBytes =
        recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0,
                 (struct sockaddr *)&serverAddr, &serverAddrLen);
    buffer[receivedBytes] = '\0';
    cout << "replay: " << buffer << endl;
  }
  close(sockfd);
  return 0;
}
