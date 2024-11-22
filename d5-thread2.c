#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define maxThread 20

int suiv = 1;
int nbThread;
sem_t semaphores[maxThread];

void* threadSecondaire(void* arg) {
    while (1) {
        sem_wait(&semaphores[suiv - 1]);

        printf("Thread numero : %d \n", suiv);

        suiv = (suiv % nbThread) + 1;
        sem_post(&semaphores[suiv - 1]);

        
    }
    return NULL;
}

int main() {
	 
    printf("Donnez le nombre de thread : ");
    scanf("%d", &nbThread);

    if(nbThread <maxThread ){
    	    sem_init(&semaphores[0], 0, 1 );
	    for (int i = 1; i < nbThread; i++) {
		sem_init(&semaphores[i], 0, 0);
	    }

	    pthread_t threads[nbThread];
	    for (int i = 0; i < nbThread; i++) {
		pthread_create(&threads[i], NULL, threadSecondaire, NULL);
	    }

	    for (int i = 0; i < nbThread; i++) {
		pthread_join(threads[i], NULL);
	    }

	    for (int i = 0; i < nbThread; i++) {
		sem_destroy(&semaphores[i]);
	    }
    }else{
    	printf("Trop de thread , Diminuez ! \n ") ;
    }

    return 0;
}
