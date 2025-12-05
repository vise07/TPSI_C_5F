/*
Scrivere il codice in C di un'applicazione socket CLIENT-SERVER in cui il server
riceve in input una stringa e, dopo i controlli necessari, restituisce al client
la stringa da cui sono stati rimossi tutti i caratteri duplicati consecutivi.

SERVER
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>

#define DIM 50
#define SERVERPORT 1450

void eliminaDoppie(char s[]) {
    int j = 0;   // indice di scrittura

    for (int i = 0; s[i] != '\0'; i++) {
        // copia il carattere solo se non è uguale al precedente
        if (i == 0 || s[i] != s[i - 1]) {
            s[j++] = s[i];
        }
    }

    s[j] = '\0'; // termina la stringa
}

int main(int argc, char *argv[]) {

	struct sockaddr_in servizio;

	servizio.sin_family = AF_INET;
	servizio.sin_addr.s_addr = htonl(INADDR_ANY);
	servizio.sin_port = htons(SERVERPORT);

	char string[DIM];
	int socketfd, soa, fromlen = sizeof(servizio);

	if(socketfd = socket(AF_INET, SOCK_STREAM,0) == -1) {
		printf("Errore chiamata alla system call socket.\n");
		exit(1);
	}

	if(bind(socketfd, (struct sockaddr*)&servizio, sizeof(servizio)) == -1) {
		printf("Errore chiamata alla system call bind.\n");
		exit(1);
	}

	if(listen(socketfd, 10) == -1) {
		printf("Errore chiamata alla system call listen.\n");
		exit(1);
	}

	for(;;) {
		printf("\nServer in ascolto...\n");
		fflush(stdout);

		if(soa = accept(socketfd, (struct sockaddr*)&servizio, &fromlen) == -1) {
			printf("Errore chiamata alla system call accept.\n");
			exit(1);
		}
		
		read(soa, string, sizeof(string));
		
		printf("Stringa ricevuta: %s.\n", string);
		
		eliminaDoppie(string);
		
		printf("Stringa senza doppie: %s.\n", string);
		
		write(soa, string, sizeof(string));
		
		close(soa);
	}

	return 0;
}
