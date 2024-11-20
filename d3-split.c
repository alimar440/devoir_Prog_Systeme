#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h> 

void join(int argc ,  char *argv[] ){
	
	    int fdDest = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC,
				      S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
		if (fdDest == -1) {
			perror("Erreur lors de la création du fichier destination");
			exit(1);
		}

		
		char buffer[200];
		ssize_t nbRead, nbWrite;

		for (int i = 2; i < argc; i++) {
		
		
		int fdPart = open(argv[i], O_RDONLY);
		if (fdPart == -1) {
			perror("Erreur lors de l'ouverture d'une partie");
			close(fdDest);
			exit(1);
		}
		
		while ((nbRead = read(fdPart, buffer, sizeof(buffer))) > 0) {
			nbWrite = write(fdDest, buffer, nbRead);
			if (nbWrite < 0 || nbRead <0) {
				perror("Erreur lors de l'ecriture ou lors de la lecture dans le fichier destination");
				close(fdPart);
				close(fdDest);
				exit(1);
			}
		}

		

		close(fdPart) ;
			}
		
		close(fdDest) ;
		
	

		    
		    
}

void split(int argc, char *argv[]){
	int size = atoi(argv[2]) ;
		
		int fd = open(argv[1] , O_RDONLY  );
		
		if (fd == -1) {
			perror("Erreur d'ouverture en écriture seule");
			exit(1);
		}
		
		char buff ;
		int  nbRead = 0 ;
		int nbWrite ;
		int taille = 0 ;
		
		
		do{
			nbRead = read(fd , &buff , sizeof(char) ) ;
			if(nbRead>0 ) 
				taille++ ; 
			
		}while(nbRead >0  ) ;
		
		close(fd) ;
		
		char gcc_args[2][10] ;
		
		
		int fdSrc = open(argv[1] , O_RDONLY  );
		
		if (fdSrc == -1) {
			perror("Erreur lors de la réouverture du fichier source");
			exit(1);
		}
		
		int nbElement = taille/size ;
		
		for(int i = 0 ; i<size ; i++){
		
			char part[10] = "part_0";
			part[5] = '0' + i;
			
			int fdPart = open(part, O_WRONLY | O_CREAT | O_EXCL ,
				S_IWUSR | S_IRUSR |S_IRGRP |
				S_IROTH 
		
				) ;
				
			if (fdPart == -1) {
				perror("Erreur lors de la création d'une partie");
				close(fdSrc);
				exit(1);
			}
			
			nbRead= 0 ;
			
			do{
		
			
				read(fdSrc , &buff , sizeof(char) ) ;
				if(nbRead > 0 ) 
				{
					nbWrite = write(fdPart , &buff , sizeof(char) ) ;
				
					if (nbWrite < 0 ) {
						perror("Erreur lors de l'écriture dans le fichier destination");
						close(fdPart);
						close(fdSrc);
						exit(1);
					}
				}
				nbRead++;
			}while(nbRead <  nbElement  || nbWrite <0 ) ;
			
			
		}
		
		close(fdSrc) ;
}

int main(int argc, char *argv[]) {

	if (argc < 3) {
			printf("Usage: ./split <fichier_destination> <part_1> <part_2> ...\n  "
					"ou bien \n"
					"Usage: ./split <nombre de fichier (entier)\n");
			exit(1) ;
		
	}

	if(argc == 3 ){
		
		split(argc , argv) ;   
		
	}else{
    
		join(argc , argv ) ;
				
	}

	return 0;
}

