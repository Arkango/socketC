// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <ctype.h>
#include <netdb.h>


#define PORT 1234
int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "connessione avvenuta";
    struct hostent *host;

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }



    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    // Forcefully attaching socket to the port 1234
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    int i,times = 0;

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t*)&addrlen))<0)
    {

        perror("accept");
        exit(EXIT_FAILURE);
    } else{
        host = gethostbyaddr((char *) &address, 4, AF_INET);
        char* canonical_name = host->h_name;
        printf("Risultato di gethostbyaddr(%s): %s\n",
               inet_aton(address.sin_addr.s_addr), canonical_name);

    }

    while(1){
            switch (times){
                case 0:
                    send(new_socket , hello , strlen(hello) , 0 );
                    break;
                case 1:
                    valread = read( new_socket , buffer, 1024);
                    printf("Client: %s\n",buffer );

                    char *tmp;


                    for(i=0; i < sizeof(buffer); i++){
                        memset(tmp + i, toupper(buffer[i]), sizeof(char));
                    }

                    printf("%s\n",tmp);

                    send(new_socket , tmp , strlen(tmp) , 0 );

                    memset(buffer,0, sizeof(buffer));
                    memset(tmp,0, sizeof(tmp));



                    break;
                case 2:
                    valread = read( new_socket , buffer, 1024);
                    printf("Client:  %s\n",buffer );


                    for(i=0; i < sizeof(buffer); i++){
                        memset(tmp + i, tolower(buffer[i]), sizeof(char));

                    }

                    printf("%s\n",tmp);
                    send(new_socket , tmp , strlen(tmp) , 0 );

                    memset(buffer,0, sizeof(buffer));
                    memset(tmp,0, sizeof(tmp));

                    break;
                default:
                    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                                             (socklen_t*)&addrlen))<0)
                    {
                        perror("accept");
                        exit(EXIT_FAILURE);
                    }
                    times = -1;
                    break;
            }
            times += 1;


    }

    return 0;
} 
