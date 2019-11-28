// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <ctype.h>
#include <arpa/inet.h>
#define PORT 1234



int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "connessione avvenuta";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons( PORT );

    // Forcefully attaching socket to the port 8080
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
    int i,times = -1;



    while(1){



            switch (times){
                case 0:
                    send(new_socket , hello , strlen(hello) , 0 );
                    times = 1;
                    break;
                case 1:

                    //funzione programma
                    valread = read( new_socket , buffer, 1024);
                    char tmp[100];


                    char demil[] = "|";
                    char* token = strtok(buffer, demil);
                    char *array[3];
                    int i = 0;


                    while(token != NULL)
                    {
                        array[i++] = token;
                        token = strtok(NULL, demil);

                    }

                    if(i != 3){
                        times = -1;
                        break;
                    }

                   int flag = 0;
                    float op = 0.0;
                   float first;
                   sscanf(array[1], "%f", &first);
                    float second;
                   sscanf(array[2], "%f", &second);


                   if(strcmp(array[0],"a") == 0 || strcmp(array[0],"A") == 0 ){
                        op = first+second;
                        sprintf(tmp,"risultato addizione %f",op );
                        send(new_socket , tmp , strlen(tmp) , 0 );
                        flag = 1;
                   }


                   if(strcmp(array[0],"s") == 0 || strcmp(array[0],"S") == 0 ){
                        op = first-second;
                       sprintf(tmp,"risultato sottrazione %f",op );
                        send(new_socket , tmp , strlen(tmp) , 0 );
                        flag = 1;
                   }



                    if(strcmp(array[0],"m") == 0 || strcmp(array[0],"M") == 0 ){
                         op = first*second;
                        sprintf(tmp,"risultato moltiplicazion %f",op );
                         send(new_socket , tmp , strlen(tmp) , 0 );
                         flag = 1;

                    }



                    if(strcmp(array[0],"d") == 0 || strcmp(array[0],"D") == 0 ){
                        if(second == 0){
                          op = -1;
                        }else{
                         op = first/second;

                        }
                        sprintf(tmp,"risultato divisione %f",op );
                         send(new_socket , tmp , strlen(tmp) , 0 );
                         flag = 1;

                    }


                     if(flag == 0){
                         strcpy(tmp, "TERMINE PROCESSO CLIENT");

                         send(new_socket , tmp , strlen(tmp) , 0 );
                         close(new_socket);
                         times = -1;
                     }

                    memset(buffer,0, sizeof(buffer));
                    memset(tmp,0, sizeof(tmp));
                    memset(array,0, sizeof(array));

                    times = -1;


                    break;

                default:
                    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                                             (socklen_t*)&addrlen))<0)
                    {
                        perror("accept");
                        exit(EXIT_FAILURE);
                    }
                    times = 0;
                    break;
            }


    }
}




