/**
 * This exercise I didn't write error handling code
 * You can add the code yourself  
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


int main(int argc, char* argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    int str_len = 0;
    int idx = 0;

    // initialize the server address
    memset(&serv_addr, 0, sizeof(serv_addr));
    sock = socket(PF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);  // IP address
    serv_addr.sin_port = htons(atoi(argv[2]));       // port

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        return -1;

    for (int i = 0; i < 3000; i++)
        printf("Wait time %d\n", i);
    if (!read(sock, message, sizeof(message) - 1))
        return -1;
    printf("Message from server : %s \n", message);
    close(sock);
    return 0;
    
}