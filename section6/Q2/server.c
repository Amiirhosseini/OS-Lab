//Amirreza Hosseini 9820363
// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
int main()
{
    
        int server_socket;
        char buffer1[256];
        char buffer2[256];
        struct sockaddr_in server_address, client_address;
        // Creating a socket file descriptor
        if ((server_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        {
            printf("error: socket creation failed\n");
            return -1;
        }
        // Filling server information
        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
        server_address.sin_port = htons(6000);
        // Bind the socket with the server address
        if (bind(server_socket, (const struct sockaddr *)&server_address,
                 sizeof(server_address)) < 0)
        {
            printf("error: bind failed\n");
            return (-1);
        }
        while (1)
    {
        int client_address_len = sizeof(client_address);
        int n;
        n = recvfrom(server_socket, (char *)buffer1, 255, MSG_WAITALL, (struct sockaddr *)&client_address, &client_address_len);
        buffer1[n] = '\0';
        int number1 = atoi(buffer1);
        printf("A number 1 from a client: %d\n", number1);

        n = recvfrom(server_socket, (char *)buffer2, 255, MSG_WAITALL, (struct sockaddr *)&client_address, &client_address_len);
        buffer2[n] = '\0';
        int number2 = atoi(buffer2);
        printf("A number 2 from a client: %d\n", number2);

        int sum = number1 + number2;

        char sumBuffer[256];
        sprintf(sumBuffer, "%d", sum);

        sendto(server_socket, (const char *)sumBuffer, strlen(sumBuffer), MSG_CONFIRM,
               (const struct sockaddr *)&client_address, client_address_len);
        printf("sum sent to the client.\n");
    }
    return 0;
}