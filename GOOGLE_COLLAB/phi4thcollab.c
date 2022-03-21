
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

#define iterations 1e9
#define threads 4

double pi=0;
int section = iterations/threads;

void *pileibnitz(void *arg){
    int hilo = (int *) arg;
    int init = section * hilo;
    int fn = init + section -1;
    for(int init=0; init < fn; init++){
        pi += (double) 1/(init*2+1) * 4;
        init++;
        pi -= (double) 1/(init*2+1) * 4 ;
    }
}

int main(){
    FILE *fo;
    fo = fopen("pithreaddataCOLLAB.txt", "a");
    struct timeval t_before, t_after, t_execution; 
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    pthread_t thread4;
    gettimeofday(&t_before, NULL);
    pthread_create(&thread1, NULL, (void *)pileibnitz, (void *) 0);
    pthread_create(&thread2, NULL, (void *)pileibnitz, (void *) 1);
    pthread_create(&thread3, NULL, (void *)pileibnitz, (void *) 2);
    pthread_create(&thread4, NULL, (void *)pileibnitz, (void *) 3);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    gettimeofday(&t_after, NULL);
    timersub(&t_after, &t_before, &t_execution);
    long int seconds = (long int) t_execution.tv_sec;
    long int useconds = (long int) t_execution.tv_usec;
    fprintf(fo, "\n4Thread %ld.%06ld", seconds, useconds);
    fclose(fo);
    printf("Pi calculated with %f iteractions \n With a value of %f \n Executed in %ld.%06ld seconds", iterations, pi, seconds, useconds);
    return 0;
}