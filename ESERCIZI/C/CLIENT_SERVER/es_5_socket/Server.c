// Server

#include <stdio.h>      //std in-out
#include <stdlib.h>     //per utilizzo di certe funzioni:htonl,rand,....
#include <sys/socket.h> //funz. accept+bind+listen
#include <sys/types.h>  //funz. accept
#include <netinet/in.h> //definiscono la struttura degli indirizzi
#include <netdb.h>      //strutture hostent e servent che identificano l'host tramite iol nome
#include <string.h>     //funz. stringhe
#include <fcntl.h>      //descrittore di file
#include <signal.h>     //consente l'utilizzo delle funzioni per la gestione dei segnali fra processi
#include <errno.h>      //gestioni errori connessione
#include <ctype.h>      //bind
#include <unistd.h>     // file header che consente l'accesso alle API dello standard POSIX

#define SERVERPORT 1450
#define DIM 20

int controlloStringhe(char s[], char s2[]) {
    if (strlen(s) > strlen(s2))
        return 1;
    else if (strlen(s) < strlen(s2))
        return 0;
    else
        return -1;
}

int main() {
    struct sockaddr_in servizio;
    int socketfd, soa;
    char s[DIM], s2[DIM], risposta[DIM];
    int fromlen = sizeof(servizio);

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("chiamata alla system call socket fallita");
        exit(1);
    }

    if (bind(socketfd, (struct sockaddr*)&servizio, sizeof(servizio)) == -1) {
        printf("chiamata alla system call bind fallita");
        exit(1);
    }

    if (listen(socketfd, 10) == -1) {
        printf("chiamata alla system call listen fallita");
        exit(1);
    }

    printf("Server in ascolto...\n");

    for (;;) {
        soa = accept(socketfd, (struct sockaddr*)&servizio, &fromlen);
        if (soa == -1) {
            printf("chiamata alla system call accept fallita");
            exit(1);
        }

        read(soa, s, DIM);
        read(soa, s2, DIM);

        int controllo = controlloStringhe(s, s2);

        if (controllo == 1)
            snprintf(risposta, DIM, "La stringa 1 è più lunga.");
        else if (controllo == 0)
            snprintf(risposta, DIM, "La stringa 2 è più lunga.");
        else
            snprintf(risposta, DIM, "Le stringhe sono uguali.");

        write(soa, risposta, DIM);

        close(soa);
    }
    return 0;
}
