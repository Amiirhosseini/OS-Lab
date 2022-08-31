//Amirreza Hosseini 9820363
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define SERVER_PORT 6000
#define MAX_CLIENT 5

int main()
{

    char buffer[256];
    int server_socket, client_socket;
    // server_address = explicit address of server
    //client_address = client information
    struct sockaddr_in server_address, client_address;
    //filling the server address record
    server_address.sin_family = AF_INET; //IPv4
    server_address.sin_port = htons(SERVER_PORT);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    //server_address.sin_addr.s_addr=INADDR_ANY;
    //making socket family = AF_INET, type = SOCK_STREAM , protocol = TCP
    server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //binding socket to the server address
    bind(server_socket, (struct sockaddr *)&server_address,
         sizeof(server_address));
    //listening to incoming requests from clients with backlog of 5 clients
    listen(server_socket, MAX_CLIENT);
    while (1)
    {
        int clientsize = sizeof(client_address);
        if ((client_socket = accept(server_socket, (struct sockaddr *)&client_address, &(clientsize))) >= 0)
            printf("A connection from a client is recieved\n");
        else
            printf("Error in accepting the connection from the client\n ");

        bzero(buffer, 256);
        read(client_socket, buffer, 256);
        buffer[strcspn(buffer, "\r\n")] = 0;
        printf("sended path: %s\n", buffer);

        char source[256];
        char symbol;

        ///home/amir/Desktop/oslab6/Q1/hi.txt
        FILE *fp = fopen(buffer, "r");
        if (fp == NULL)
            printf("file not exist\n");

        int fpos = 0;
        do
        {
            char c = fgetc(fp);

            if (feof(fp))
                break;

            source[fpos] = c;
            fpos++;
        } while (1);
        source[fpos] = '\0';
        fclose(fp);

        printf("inside file : %s\n", source);

        printf("send file again to the client");

        write(client_socket, source, 256);
    }

    return 0;
}