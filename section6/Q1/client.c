//Amirreza Hosseini 9820363
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define SERVER_PORT 6000

int main()
{
    int client_socket;
    char buffer[256];
    //making the server address record with a recognized server IP and port
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
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
        printf("file path is:\n");
        fgets(buffer, 256, stdin);//send the file path
        write(client_socket, buffer, 256);
        printf("msg is sent to the server!\n");

        char buffer2[256];
        bzero(buffer, 256);
        read(client_socket, buffer, 255);
        printf("read file from server: %s\n", buffer);
        buffer[strcspn(buffer, "\r\n")] = 0;

        strcat(buffer2,buffer);
        
        FILE *fp = fopen("./client_cpy.txt", "wb");
        fprintf(fp,"%s\n",buffer2);
        //fputs(buffer2,fp);
        //fwrite(buffer2,sizeof(buffer2),1,fp);
        fclose(fp);
        printf("stored into file....\n\n");
    }
    return 0;
}