#include "Socket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

using namespace pr;
using namespace std;

void Socket::connect(const std::string & host, int port){
    
    struct addrinfo * adr;
    struct in_addr ipv4;

    if(getaddrinfo(host.c_str(), nullptr, nullptr, &adr) != 0) {
        perror("DNS");
    }

    for(struct addrinfo * rp=adr; rp != NULL; rp=rp -> ai_next) {
        if(rp -> ai_family == AF_INET && rp -> ai_socktype == SOCK_STREAM) {
            ipv4 = ((struct sockaddr_in*) rp -> ai_addr) -> sin_addr;
        }
        break;
    }

    freeaddrinfo(adr);
    connect(ipv4, port);
}

void Socket::connect(in_addr ipv4, int port){
    this -> fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (fd < 0) {
        perror("socket");
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr = ipv4;
    
    if (::connect(fd, ((struct sockaddr *) &server), sizeof(server)) < 0) {
        ::close(fd);
        fd = -1;
        perror("connect");
    }
}

void Socket::close() {
    if (fd != -1) {
        shutdown(fd, 2);
        ::close(fd);
        fd = -1; 
    }
}