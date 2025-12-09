#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <netinet/in.h>
#include <unistd.h>

#define DIM 50
#define SERVERPORT 1450

void stringaMaiuscolo(char string[]) {
    for(int i = 0; string[i] != '\0'; i++) {
        string[i] = toupper(string[i]);
    }
}

int lunghezzaStringa(char string[]) {
    return strlen(string);
}

int numeroCifre(char string[]) {
    int cont = 0;
    for(int i = 0; i < strlen(string); i++) {
        if(string[i] >= '0' && string[i] <= '9') {
            cont++;
        }
    }
    return cont;
}

void sostituisciSpazi(char string[]) {
    for(int i = 0; string[i] != '\0'; i++) {
        if(string[i] == ' ') {
            string[i] = '_';
        }
    }
}


int main() {

    struct sockaddr_in servizio;

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    char string[DIM];
    int socketfd, scelta, soa, fromlen = sizeof(servizio);

    if((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("Errore nella chiama alla system call socket.\n");
        exit(1);
    }

    if((bind(socketfd, (struct sockaddr*)&servizio, sizeof(servizio))) == -1) {
        printf("Errore nella chiama alla system call bind.\n");
        exit(1);
    }

    if((listen(socketfd, 10)) == -1) {
        printf("Errore nella chiama alla system call listen.\n");
        exit(1);
    }

    for(;;) {
        printf("Server in ascolto...\n");
        fflush(stdout);

        if((soa = accept(socketfd, (struct sockaddr*)&servizio, &fromlen)) == -1) {
            printf("Errore nella chiama alla system call accept.\n");
            exit(1);
        }

        read(soa, string, sizeof(string));
        read(soa, &scelta, sizeof(scelta));

        switch(scelta) {
            case 1:
            stringaMaiuscolo(string);
            break;
            
            case 2:
            sprintf(string, "Lunghezza stringa: %d", lunghezzaStringa(string));
            break;

            case 3:
            sprintf(string, "Numero cifre: %d", numeroCifre(string));
            break;

            case 4:
            sostituisciSpazi(string);
            break;

            default:
            printf("Scelta non valida.\n");
            break;
        }

        write(soa, string, sizeof(string));

        close(soa);
    }

    return 0;
}
