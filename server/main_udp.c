//
// Created by strunz on 28/11/19.
//




#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <ctype.h>

#define ECHOMAX 512
#define PORT 2020

int main(int argc, char const *argv[]) {
    int sock;
    struct sockaddr_in echoServAddr;
    struct sockaddr_in echoClntAddr;
    unsigned int cliAddrLen;
    char echoBuffer[ECHOMAX];
    int recvMsgSize;
    char c;


// CREAZIONE DELLA SOCKET
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        printf("Errore nella creazione della socket");
        return (-1);
    }

    // COSTRUZIONE DELL'INDIRIZZO DEL SERVER
    memset( &echoServAddr, '\0', sizeof(echoServAddr));

    echoServAddr.sin_family = AF_INET;
    echoServAddr.sin_port = htons(PORT);
    echoServAddr.sin_addr.s_addr =inet_addr("127.0.0.1");

// BIND DELLA SOCKET
    if (bind(sock, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr))==-1){
        printf("Errore nella bind della socket");
        return (-1);
    }



    int i = 0;
    cliAddrLen = sizeof(echoClntAddr);


// RICEZIONE DELLA STRINGA ECHO DAL CLIENT
    while(1) {
//fflush(stdout);


        if ((recvMsgSize = recvfrom(sock, (char *) echoBuffer, ECHOMAX, MSG_WAITALL, (struct sockaddr *) &echoClntAddr, &cliAddrLen)) == -1)
        {
            printf("no msg recvfrom");
            return (-1);
        }


        //printf("Messaggio ricevuto %s client %s\n", echoBuffer, inet_ntoa(echoClntAddr.sin_addr));




        if(recvMsgSize > 0){
            switch (i) {
                case 0:
                    printf("Messaggio ricevuto %s client %s\n", echoBuffer, inet_ntoa(echoClntAddr.sin_addr));
                    if (sendto(sock, "OK", 2, 0, (struct sockaddr *)&echoClntAddr,sizeof(echoClntAddr)) != 2){
                        printf("Errore nel numero di byte inviati");
                        return(-1);
                    }
                    i++;
                    break;
                case 1:
                    c = echoBuffer[0];
                    if(c !='#'){
                        c = toupper(c);
                        // RINVIA LA STRINGA ECHO AL CLIENT
                        if (sendto(sock,&c, sizeof c, 0, (struct sockaddr *)&echoClntAddr,sizeof(echoClntAddr)) != sizeof c){
                            printf("Errore nel numero di byte inviati");
                            return(-1);
                        }

                    }else {
                        i = 0;
                    }

                    break;
            }
        }

    }


}