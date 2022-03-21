#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <windows.h>
#include <pthread.h>

#define iterations 1e9
#define threads 4

double pi=0;
int section = iterations/threads;

void *pileibnitz(void *arg){
    int hilo = (int *) arg;
    int init = section * hilo;
    int fn = init + section -1;
    for(init; init < fn ; init++){
        pi += (double) 1/(init*2+1) * 4;
        init++;
        pi -= (double) 1/(init*2+1) * 4 ;
    }
}


void main(){
    FILE *fo;
    fo = fopen ("pithreaddata.txt", "a");
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;

    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    pthread_t thread4;

    double exec_time;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
    pthread_create(&thread1, NULL, (void *)pileibnitz, (void *) 0);
    pthread_create(&thread2, NULL, (void *)pileibnitz, (void *) 1);
    pthread_create(&thread3, NULL, (void *)pileibnitz, (void *) 2);
    pthread_create(&thread4, NULL, (void *)pileibnitz, (void *) 3);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    QueryPerformanceCounter(&end);
    exec_time = (double) (end.QuadPart - start.QuadPart)/frequency.QuadPart;
    fprintf(fo, "\n4Thread %f", exec_time);
    fclose(fo);
    printf("Pi calculated with %f iteractions \n With a value of %f \n Executed in %f seconds", iterations, pi, exec_time);
}
