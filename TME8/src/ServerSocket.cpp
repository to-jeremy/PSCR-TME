#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstdio>
#include "ServerSocket.h"
#include <iostream>

using namespace pr;
using namespace std;

ServerSocket::ServerSocket (int port) {
    int socket = ::socket(AF_INET, SOCK_STREAM, 0);

    if(socket < 0) {
        perror("erreur socket");
    }

    struct sockaddr_in adr;

    adr.sin_family = AF_INET;
    adr.sin_port = htons(port);
    adr.sin_addr.s_addr = INADDR_ANY;

    if(bind(socket, (struct sockaddr *) &adr, sizeof(adr))) {
        perror("bind");
    }

    int i=1;

    setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i));

    if(listen(socket, 10) < 0) {
        perror("close");
    }
}

Socket ServerSocket::accept() {
    struct sockaddr_in exp;
    socklen_t size=sizeof(exp);
    int sc = ::accept(socketfd, (struct sockaddr *) &exp, &size);
    return Socket(sc);
}