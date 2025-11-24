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
#define DIM 100

int contaPari(int vet[]) {
    int count = 0;
    for (int i = 0; i < 10; i++) {
        if (vet[i] % 2 == 0)
            count++;
    }
    return count;
}

int contaDispari(int vet[]) {
    int count = 0;
    for (int i = 0; i < 10; i++) {
        if (vet[i] % 2 != 0)
            count++;
    }
    return count;
}

int main() {
    struct sockaddr_in servizio;
    int socketfd, soa;
    int vet[10], fromlen = sizeof(servizio);
    char risposta[100];

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


    for (;;) {
        printf("Server in ascolto...\n");

        soa = accept(socketfd, (struct sockaddr*)&servizio, &fromlen);
        if (soa == -1) {
            printf("chiamata alla system call accept fallita");
            exit(1);
        }

        read(soa, vet, sizeof(vet));

        int pari = contaPari(vet);
        int dispari = contaDispari(vet);

        snprintf(risposta, sizeof(risposta),"Numeri pari: %d  Numeri dispari: %d",pari, dispari);

        write(soa, risposta, sizeof(risposta));

        close(soa);
    }

    return 0;
}
