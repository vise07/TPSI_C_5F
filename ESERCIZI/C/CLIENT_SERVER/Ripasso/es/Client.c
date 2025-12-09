#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

#define DIM 50
#define SERVERPORT 1450

int main() {

    struct sockaddr_in servizio;

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    char string[DIM];
    int socketfd, scelta;

    if((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("Errore nella chiama alla system call socket.\n");
        exit(1);
    }

    if(connect(socketfd, (struct sockaddr*)&servizio, sizeof(servizio)) == -1) {
        printf("Errore nella chiama alla system call connect.\n");
        exit(1);
    }

    printf("Inserisci una stringa.\n");
    fgets(string, DIM, stdin);

    printf("Inserisci la scelta:\n1. Stringa in MAIUSCOLO\n2. Lunghezza stringa\n3. Numero di cifre\n4. Sostituire spazi con '_'");
    scanf("%d", &scelta);

    write(socketfd, string, sizeof(string));
    write(socketfd, &scelta, sizeof(scelta));

    read(socketfd, string, sizeof(string));

    printf("Stringa dopo la modifica: %s", string);

    close(socketfd);

    return 0;
}
