//
// Created by arcangelo on 10/7/19.
//

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 5000
#define BUFFERSIZE 1024

char* insertString(int i);

int main(int argc,char const *argv[]){
    int sock;
    char buff[BUFFERSIZE];
    struct sockaddr_in serv_addr;

    //creazione del socket
    if((sock = socket(AF_INET, SOCK_STREAM,0) < 0)){
        printf("\n Socket creation error\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(PORT);
    /*
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }*/

    connect(sock,(struct sockaddr*)&serv_addr, sizeof(serv_addr));
    /*if(connect(sock,(struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
        printf("\nConnection Failed \n");
        return -1;
    }*/

    /*Ricevo dati dal server*/
    int flag =0;
    int times = 0;
    ssize_t numBytesRcvd;

    while(1){
        numBytesRcvd = recv(sock,buff,BUFFERSIZE-1,0);
        buff[numBytesRcvd] = '\0';
        if(numBytesRcvd <= 0){
            printf("Connection failed or closed prematurely,Exit...\n");
            flag = 1;
            break;
        }
        printf("From Server : %s", buff);
        times += 1;
        if (times == 3) {
            printf("Client Exit...\n");
            break;
        }else if((strncmp(buff, "connessione avvenuta", 20)) == 0){

            char *stringa_1 = insertString(times);

            if (send(sock, stringa_1, strlen(stringa_1), 0) !=  strlen(stringa_1)) {
                printf("send() sent a different number of bytes than expected\n");
                flag = 1;
                break;
            }
        }

    }


    close(sock);
    if(flag == 1){
        return -1;
    }

    return 0;
}

char* insertString(int i){
    char *stringa_1;
    char *name[2];
    name[1] = "prima";
    name[2] ="seconda";
    printf("Inserire la %s stringa in input\n",name[i]);
    scanf("%s",stringa_1);

    return stringa_1;

}
