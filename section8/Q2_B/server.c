//Amirreza Hosseini 9820363

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
//#define SERVER_PORT argv[2]
//#define MAX_CLIENT argv[3]

int main(int argc, char *argv[])
{
        int SERVER_PORT = atoi(argv[2]);
        int MAX_CLIENT = atoi(argv[3]);

        // printf("in server\n");
        // printf("max %d  ",MAX_CLIENT);
        // printf("server %d\n",SERVER_PORT);

        // printf("arg1 %s \n arg2 %s \n arg3 %s \n",argv[1],argv[2],argv[3]);

        char buffer[256];
        int server_socket, client_socket;
        // server_address = explicit address of server
        //client_address = client information
        struct sockaddr_in server_address, client_address;
        //filling the server address record
        server_address.sin_family = AF_INET; //IPv4
        server_address.sin_port = htons(SERVER_PORT);
        server_address.sin_addr.s_addr = inet_addr(argv[1]);
        //server_address.sin_addr.s_addr=INADDR_ANY;
        //making socket family = AF_INET, type = SOCK_STREAM , protocol = TCP
        server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        //binding socket to the server address
        bind(server_socket, (struct sockaddr *)&server_address,
             sizeof(server_address));
        //listening to incoming requests from clients with backlog of 5 clients
        listen(server_socket, MAX_CLIENT);
        int clientsize = sizeof(client_address);
        if ((client_socket = accept(server_socket, (struct sockaddr *)&client_address, &(clientsize))) >= 0)
            printf("A connection from a client is recieved\n");
        else
            printf("Error in accepting the connection from the client\n ");
        while (1)
        {
            bzero(buffer, 256);
            read(client_socket, buffer, 256);
            if (strncmp(buffer, "bye", 3) == 0)
            {
                printf("finished....\n");
                break;
            }

            printf("%s\n", buffer);
        }
    return 0;
}