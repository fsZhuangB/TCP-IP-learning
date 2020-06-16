#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char* argv[])
{
    int serv_sock;  // server socket
    int clnt_sock;  // client socket

    struct sockaddr_in serv_addr; // server address
    struct sockaddr_in clnt_addr; // client address
    socklen_t clnt_addr_size;

    char message1[] = "Hello World";

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);

    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    // bind function to allocate address and port
    if (bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
        return -1;
// use the listen turning the socket to accept
    if (listen(serv_sock, 5) == -1)
        return -1; 

    clnt_addr_size = sizeof(clnt_addr);
// use the accept function to handle the connection request 
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    if(clnt_sock == -1)
        return -1;

    write(clnt_sock, message1, 4);
    write(clnt_sock, message1 + 4, 4);
    write(clnt_sock, message1 + 8, 4);
    write(clnt_sock, message1 + 12, sizeof(message1) - 12);
    
    close(clnt_sock);
    close(serv_sock);

    return 0;

}