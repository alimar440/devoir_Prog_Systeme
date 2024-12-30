#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h> 

int main() {
    

    struct sockaddr_in addrServer;
    addrServer.sin_family = AF_INET;
    addrServer.sin_addr.s_addr = inet_addr("0.0.0.0");

    printf("les ports libres entre 0 et 3000 \n" );
    for (int i = 0; i <= 3000; i++) {
    	int socketTCP = socket(AF_INET, SOCK_STREAM, 0);
        if (socketTCP < 0) {
            perror("Erreur creation Socket  ");
            exit(EXIT_FAILURE);
        }

        addrServer.sin_port = htons(i);

        if (connect(socketTCP, (struct sockaddr *) &addrServer, sizeof(addrServer)) == 0) {
            printf("%d\n", i);
        }

        close(socketTCP);
    }
    return 0;
}
