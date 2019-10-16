// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>

int main(int argc, char const *argv[])
{
    int PORT = 1234;
    struct hostent *lh;
    char ip[16];
    struct in_addr **addr_list;

    if(argc == 1 || argc > 3){
        printf("Usage ./a.out nameserver [port] \n default port 1234");
        return 1;
    }


    lh = gethostbyname(argv[1]);
    if (lh){
        printf("%S",lh->h_name);

    }else{
        herror("gethostbyname");
        return 1;
    }


    if(argc == 3){
        PORT = (int) argv[2];
    }



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


    addr_list = (struct in_addr **)lh->h_addr_list;


    serv_addr.sin_addr = *addr_list[0];




    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    //connessione ricevuta
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );

    memset(buffer,0, sizeof(buffer));

    //prima stringa
    char *tmp;
    printf("Insert string\n");
    fgets(tmp,1024,stdin);

    send(sock , tmp , strlen(tmp) , 0 );
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );

    memset(buffer,0, sizeof(buffer));
    memset(tmp,0, sizeof(tmp));

    //seconda stringa

    printf("Insert string\n");
    fgets(tmp,1024,stdin);

    send(sock , tmp , strlen(tmp) , 0 );
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );

    memset(buffer,0, sizeof(buffer));
    memset(tmp,0, sizeof(tmp));

    close(sock);



    return 0;
}