#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <semaphore.h>
#include <pthread.h>

sem_t semSecondaire, semTercier;

int count = 0;
int nb;
int i = 0 ;
void *ftheadsecondaire(void *arg) {
    int courant = *(int *)arg;

    while (1) {
        if (courant == 0) {
            sem_wait(&semSecondaire);
            printf("%d %d\n" , i++ , count++);
            if (count == nb) {
                sem_post(&semTercier);
            } else {
                sem_post(&semSecondaire);
            }
        } else {
            sem_wait(&semTercier);
            printf("	%d	 %d	\n" , i++ , count--);
            if (count == -nb) {
                sem_post(&semSecondaire);
            } else {
                sem_post(&semTercier);
            }
        }
    }
    return NULL;
}

int main(int argc, char const *argv[]) {
    pthread_t th1, th2;

   //printf("Donnez le nombre n : ");
    //scanf("%d", &nb);
    
    nb= atoi(argv[1] ) ;

   

    sem_init(&semSecondaire, 0, 1);
    sem_init(&semTercier, 0, 0);

    int argTh1 = 0;
    int argTh2 = 1;

    if (pthread_create(&th1, NULL, ftheadsecondaire, &argTh1) != 0) {
        perror("Erreur: creation thread secondaire");
        return 1;
    }

    if (pthread_create(&th2, NULL, ftheadsecondaire, &argTh2) != 0) {
        perror("Erreur: creation thread tercier");
        return 1;
    }

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    sem_destroy(&semSecondaire);
    sem_destroy(&semTercier);

 

    return 0;
}
