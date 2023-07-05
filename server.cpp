#include <arpa/inet.h>
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

  // create soket
  int soketfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (soketfd < 0) {
    cerr << "error creating soket error code: " << soketfd << endl;
    return 1;
  }

  cout << "socket created \n";

  // bind soket
  struct sockaddr_in serverAddr {};
  serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
  serverAddr.sin_port = htons(SERVER_PORT);
  serverAddr.sin_family = AF_INET;

  if (bind(soketfd, (const sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
    cerr << "error binding socket" << endl;
    return 1;
  };

  cout << "socket binded \n";
  cout << "server listneing \n";

  char buffer[BUFFER_SIZE];
  struct sockaddr_in clientAddr;
  auto clientSocketSize = sizeof(clientAddr);
  socklen_t clientAddrLen = sizeof(clientAddr);
  for (;;) {
    int byteread = recvfrom(soketfd, buffer, sizeof(buffer) - 1, 0,
                            (struct sockaddr *)&clientAddr, &clientAddrLen);
    if (byteread < 0) {
      std::cerr << "Failed to accept incoming connection." << std::endl;
    }
    buffer[byteread] = '\0';
    cout << "message recieved: " << buffer << endl;
    

    cout << "your replay: ";
    char replay[BUFFER_SIZE];
    cin.getline(replay, sizeof(replay));

    sendto(soketfd, replay, sizeof(replay), 0, (const struct sockaddr *)&clientAddr,
           sizeof(clientAddr));
  }

  return 0;
}
