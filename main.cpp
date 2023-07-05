#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

#define SERVER_PORT 8888
#define BUFFER_SIZE 1024

using namespace std;

int main() {

  // create soket
  int soketfd = socket(AF_INET, SOCK_DGRAM, 0);

  if (soketfd < 0)
    cout << "error creating soket error code: " << soketfd;

  // bind soket

  // lisne in soket

  // acsept client

  // disconect soket

  return 0;
}
