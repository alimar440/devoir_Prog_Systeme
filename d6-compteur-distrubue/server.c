#include "common.h"


int main(int argc, char *argv[]) {


	if (argc < 2) {
		printf("Erreur : aucun fichier spécifié\n");
		printf("Usage : %s  < PORT>\n", argv[0]);
		return 1; 
	}
	

    int socketTCP ;

    if( (socketTCP = socket(AF_INET, SOCK_STREAM, 0)) == -1 ) {
        	perror("ERROR! creation de socket") ;
            exit(1) ;
    }

    struct sockaddr_in sockaddr ;

    memset( &sockaddr , 0 , sizeof(sockaddr)) ;

    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(atoi(argv[1]));
    sockaddr.sin_addr.s_addr = inet_addr("0.0.0.0") ; 

   

    
    if(bind(socketTCP , (struct sockaddr * ) &sockaddr , sizeof(struct sockaddr_in) )  == -1 ) {
        	perror("ERROR! de  bind ") ;
            exit(1) ;
    }

    printf("Execution execution bind success 🥳 \n");

    if( listen(socketTCP , 5)  == -1 ) {
        	perror("ERROR! de listen ") ;
            exit(1) ;
    }

    printf("Execution execution listen success 🥳 \n");

    struct sockaddr_in clientaddr ;
    int tailleClt = sizeof(clientaddr) ;

    int socketClientDistant = accept(socketTCP , (struct sockaddr * ) &clientaddr , &tailleClt) ;

    int nbSend , nbRcv ; 

    int buffRcv;
    int buffSnd = 0 ;

    int i = 0 ;
    

    while(1){

        nbSend = send( socketClientDistant, &buffSnd , sizeof(buffSnd) , 0) ;
    	
    	
        sleep(1);
       
	//recevoir ping
	
	
	nbRcv = recv(socketClientDistant, &buffSnd ,sizeof(buffSnd), 0);
	
	
	printf("[Server# %d] Recu : %d\n" ,i, buffSnd); 	
	
	buffSnd++ ;
		
	if (nbRcv == -1) {
            perror("Erreur lors de recv");
            break;
        } else if (nbRcv == 0) {
            printf("Le client a fermé la connexion.\n");
            break;
        }



    }

	close(socketClientDistant)  ;    
     	return 0 ;
}
