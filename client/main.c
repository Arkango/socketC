// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 1234

int main(int argc, char const *argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    //stringa benvenuto
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );
    memset(buffer,0, sizeof(buffer));



    char *tmp;
    printf("Insert operation: \nformat: operand-op1-op2\na-A addizione\ts-S sottrazione\nm-M moltiplicazione\td-D divisione\n\n");
    fgets(tmp,1024,stdin);

    send(sock , tmp , strlen(tmp) , 0 );
    valread = read( sock , buffer, 1024);
    if(strcmp(buffer,"TERMINE PROCESSO CLIENT")==0){
        printf("chiusura connessione\n");
        close(sock);
        return 1;
    }
    printf("%s\n",buffer );
    memset(tmp,0, sizeof(tmp));
    memset(buffer,0, sizeof(buffer));



    printf("chiusura connessione\n");
    close(sock);
    return 0;
}