//
// Created by strunz on 28/11/19.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


#define ECHOMAX 1024

int check_vowel(char c);

int main(int argc, char const *argv[]){
    int sock;
    struct sockaddr_in ServAddr;
    struct sockaddr_in fromAddr;
    socklen_t fromSize;
    char echoBuffer[ECHOMAX];
    int StringLen = sizeof(echoBuffer);
    int respStringLen;
    struct hostent* server;
    struct	in_addr* ina;
    char serverName[ECHOMAX];
    int serverPort;
    char c;




    printf("Inserisci l'hostname del server\n");
    scanf("%s", serverName);

    printf("Inserisci la porta del server\n");
    scanf("%d", &serverPort);


    // CREAZIONE DELLA SOCKET
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
        printf("Errore nella creazione della socket");
        return(-1);
    }

    memset(&server, 0, sizeof(server));
    server = (struct hostent *) gethostbyname(serverName);

    if(server	==	NULL){
        fprintf(stderr,	"gethostbyname() failed.\n");
        return(-1);
    }else{
        ina = (struct	in_addr*) server->h_addr_list[0];
        printf("Risultato di gethostbyname(%s): %s\n",	server->h_name,
               inet_ntoa(*ina));
    }


    // COSTRUZIONE DELL'INDIRIZZO DEL SERVER
    memset(&ServAddr, 0, sizeof(ServAddr));
    ServAddr.sin_family = PF_INET;
    ServAddr.sin_port = htons(serverPort);
    ServAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*ina));

    strcpy(echoBuffer, "Hello Server\n");
    if ( sendto(sock, echoBuffer, ECHOMAX, 0, (struct sockaddr*)&ServAddr, sizeof(ServAddr)) == -1){
        printf("Errore inviato numero di bytes differenti");
        return(-1);
    }

    memset(&echoBuffer, 0, sizeof(echoBuffer));

    // STRINGA OK
    fromSize = sizeof(fromAddr);
    respStringLen = recvfrom(sock, echoBuffer, ECHOMAX, 0, (struct sockaddr*)&fromAddr, &fromSize);
    printf("%s\n",echoBuffer);


    printf("Inserisci una stringa alfanumerica\n");
    scanf("%s", echoBuffer);

    fromSize = sizeof(echoBuffer);

    int i;
    int counter = 0;

    for(i=0;i <= fromSize;i++){
        if(check_vowel(echoBuffer[i])){
            // INVIO DELLA VOCALE AL SERVER
            if (sendto(sock, &echoBuffer[i], 1, 0, (struct sockaddr*)&ServAddr, sizeof(ServAddr)) != 1){
                printf("Errore inviato numero di bytes differenti");
                return(-1);
            }

            //STRINGA DI RITORNO DELLE VOCALI MAIUSCOLE
            respStringLen = recvfrom(sock,&c, 1, 0, (struct sockaddr*)&fromAddr, &fromSize);
            printf("%c",c);
            counter ++;
        }
    }

    // INVIO DELL' ULTIMO SIMBOLO AL SERVER
    if (sendto(sock, "#", 1, 0, (struct sockaddr*)&ServAddr, sizeof(ServAddr)) != 1){
        printf("Errore inviato numero di bytes differenti");
        return(-1);
    }

    printf("\n");





    return 0;
}

int check_vowel(char c)
{
    if (c >= 'A' && c <= 'Z')
        c = c + 32;

    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        return 1;

    return 0;
}