#include "common.h"

int main(int argc, char *argv[]) {


	if (argc < 2) {
		printf("Erreur : aucun fichier spécifié\n");
		printf("Usage : %s <@> < PORT>\n", argv[0]);
		return 1; 
	}
	

    int socketClient  ;

    if( (socketClient = socket(AF_INET, SOCK_STREAM, 0) )== -1 ) {
        	perror("ERROR! creation de socket") ;
            exit(1) ;
    }

    struct sockaddr_in sockaddr ;

    memset( &sockaddr , 0 , sizeof(sockaddr)) ;

    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(atoi(argv[2]));
    sockaddr.sin_addr.s_addr = inet_addr(argv[1]);
    
    
    
    if(  connect(socketClient , (struct sockaddr * ) &sockaddr , sizeof(sockaddr) )  == -1 ) {
        	 perror("Erreur d'ouverture de connexion ") ;
            exit(1) ;
    }

    printf("Execution execution connexion success 🥳 \n");



    int nbSend , nbRcv ; 

    int buffRcv;
    int buffSnd;
    int i = 0 ;
    

    while(1){

	//memset(&buffRcv , 0 ,10) ;
	nbRcv = recv(socketClient, &buffRcv, sizeof(buffRcv), 0);

        printf("[Client# %d]  Recu : %d \n" ,i, buffRcv); 

        sleep(1);
	
	buffRcv++ ;
	
	if (nbRcv == -1) {
            perror("Erreur lors de recv");
            break;
        } else if (nbRcv == 0) {
            printf("Le Server a fermé la connexion.\n");
            break;
        }

		//recevoir ping
		
        nbSend = send( socketClient, &buffRcv , sizeof(buffRcv), 0) ;
        
      //  printf("[Client# %d]  Send : %s \n" ,i, buffSnd); 


        i++ ;


    }


   close(socketClient) ;
    return 0;
}



    
