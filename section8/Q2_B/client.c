// Amirreza Hosseini 9820363

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
//#define SERVER_PORT argv[2]
int main(int argc, char *argv[])
{
    
    int SERVER_PORT=atoi (argv[2]);
    int client_socket;
    char buffer[256];
    //making the server address record with a recognized server IP and port
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr(argv[1]);
    //making socket family = AF_INET, type = SOCK_STREAM , protocol = TCP
    client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //connecting to the server
    if (connect(client_socket, (struct sockaddr *)&server, sizeof(server)) == 0)
        printf("Client is connected to the server!\n");
    else
        printf("Error in connecting to the server\n");
    while (1)
    {
        bzero(buffer, 256);
        fgets(buffer, 256, stdin);
        write(client_socket, buffer, 256);
        printf("msg is sent to the server!\n");
    }
    return 0;
}