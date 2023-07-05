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
  if (soketfd < 0) {
    cerr << "error creating soket error code: " << soketfd << endl;
    return 1;
  }

  cout << "socket created \n";

  // bind soket
  struct sockaddr_in serverAddr {};
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  serverAddr.sin_port = htons(SERVER_PORT);
  serverAddr.sin_family = AF_INET;

  if (bind(soketfd, (const sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
    cerr << "error binding socket" << endl;
    return 1;
  };

  cout << "socket binded \n";

  // lisne in soket
  if (listen(soketfd, 1) < 0) {
    cerr << "error listening" << endl;
    return 1;
  }
  // acsept client
  for(;;) {
        
  }

  // disconect soket

  return 0;
}
