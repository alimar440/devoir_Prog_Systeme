#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <string.h>

int** creeMatrice(int n) {

    int** matrice = (int**)malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++) {

        matrice[i] = (int*)malloc(n * sizeof(int));

    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            matrice[i][j] = rand() % 100;

        }

    }

    return matrice;

}



void afficherFichier(int fd , int type) {

    char buffer;
    int buff;

    if (type) {
        while (read(fd, &buffer, sizeof(char)) > 0) {
            printf("%c", buffer);
        }

    } else {
        while (read(fd, &buff, sizeof(int)) > 0) {
            printf("%d ", buff);

        }

        printf("\n");

    }

}



void Sauvegarde(int fd, int** matrice, int taille, int type) {
    
    if (type) {  

        char textBuff[256];
         for (int i = 0; i < taille; i++) {
            for (int j = 0; j < taille; j++) {
                sprintf(textBuff, "%d", matrice[i][j]);

                write(fd, textBuff, strlen(textBuff));
                if (j < taille - 1) write(fd, " ", 1);

            }

            write(fd, "\n", 1);

        }

    } else { 
        for (int i = 0; i < taille; i++) {
            for (int j = 0; j < taille; j++) {
                write(fd, &matrice[i][j], sizeof(int));
            }

        }

    }

}



int main(int argc, char *argv[]) {

    int opt;
    int** matrice = NULL;
    int type = 0;
    int taille = 0;
    char* fic = NULL;
    int cree = 0;
    int affiche= 0;



   
    while ((opt = getopt(argc, argv, "cad:f:tb")) != -1) {
        switch (opt) {
            case 'c':  
                 cree = 1;
                break;
            case 'a': 
                affiche= 1;
                break;
            case 'd': 
                taille = atoi(optarg);
                break;
                
            case 'f': 
                fic = optarg;
                 break;
            case 't': 
                type = 1;
                break;
            case 'b':
                type = 0;   
                break;
            case '?':
                printf("Option non reconnue : %c\n", optopt);
                break;
            case ':':
                printf("Erreur : L'option -%c attend un argument\n", optopt);
                break;

        }

    }
    
    if (cree) {
        if (taille > 0 && fic != NULL) {

            matrice = creeMatrice(taille);            
            int fd = open(fic, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            if (fd == -1) {
                perror("Erreur lors de l'ouverture du fichier");
                return 1;
            }

            Sauvegarde(fd, matrice, taille, type);

            close(fd);
        } else {
            printf("Erreur! Donnee le nom du fichier  et la taille de la matrice  \n");
        }

    }



    

    if (affiche) {
        if (fic != NULL) {

            int fd2 = open(fic, O_RDONLY);
            
            if (fd2 == -1) {
                perror("Erreur d'ouverture du fichier en mode lecture");
                return 1;
            }

            afficherFichier(fd2, type);

            close(fd2);

        } else {

            printf("Donnee le nom du fichier \n");

        }

    }



    

    if (matrice) {

        for (int i = 0; i < taille; i++) {

            free(matrice[i]);

        }

        free(matrice);

    }



    return 0;

}

