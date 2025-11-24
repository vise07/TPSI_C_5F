// Client

#include <stdio.h>      //std in-out
#include <stdlib.h>     //per utilizzo di certe funzioni:htonl,rand,....
#include <sys/socket.h> //funz. accept+bind+listen
#include <sys/types.h>  //funz. accept
#include <netinet/in.h> //definiscono la struttura degli indirizzi
#include <string.h>     //funz. stringhe
#include <errno.h>      //gestioni errori connessione
#include <ctype.h>      //bind
#include <unistd.h>     // file header che consente l'accesso alle API dello standard POSIX

#define SERVERPORT 1450
#define DIM 100

int main() {
    struct sockaddr_in servizio;
    int socketfd;
    int vet[10] = {1, 3, 6, 7, 8, 9, 11, 13, 16, 17};
    char risposta[DIM];

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("chiamata alla system call socket fallita");
        exit(1);
    }

    if (connect(socketfd, (struct sockaddr*)&servizio, sizeof(servizio)) == -1) {
        printf("chiamata alla system call connect fallita");
        exit(1);
    }

    write(socketfd, vet, sizeof(vet));

    read(socketfd, risposta, sizeof(risposta));

    printf("Risposta del server: %s\n", risposta);

    close(socketfd);
    return 0;
}
