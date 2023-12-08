#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

ServerSocket (int port) {
    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    if(socketfd < 0) {
        perror("socketfd");
    }

    struct sockaddr_in adr;

    adr.sin_family = AF_INET;
    adr.sin_port = htons(port);
    adr.sin_addr = INADOR_ANY;

    if(bind(socketfd, (struct sockaddr *) &adr, sizeof adr)) {
        perror("bind");
    }

    int i=1;
    
}