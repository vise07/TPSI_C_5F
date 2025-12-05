/*
Scrivere il codice in C di un’applicazione socket CLIENT–SERVER in cui il server
riceve in input una stringa e, dopo i controlli necessari, restituisce al client
la stringa da cui sono stati rimossi tutti i caratteri duplicati consecutivi.

CLIENT
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <ctype.h>
#include <unistd.h>

#define DIM 50
#define SERVERPORT 1450

int main(int argc, char *argv[]) {
    
    struct sockaddr_in servizio;
    
    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);    
    
    char string[DIM];
    int socketfd;
    
    if(socketfd = socket(AF_INET, SOCK_STREAM, 0) == -1) {
        printf("Errore chiamata alla system call socket.\n");
        exit(1);
    }
    
    if(connect(socketfd, (struct sockaddr*)&servizio, sizeof(servizio)) == -1) {
        printf("Errore chiamata alla system call connect.\n");
        exit(1);
    }
    
    printf("Inserisci una stringa.\n");
    scanf("%s", string);
    
    write(socketfd, string, sizeof(string));
    
    read(socketfd, string, sizeof(string));
    
    printf("Stringa ricevuta: %s\n", string);
    
    close(socketfd);
    
    return 0;
}
