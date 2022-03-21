#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <windows.h>
#include <pthread.h>

#define iterations 1e9

double pi=0;

void *pileibnitz_positive(){
    for(int i=0; i< iterations; i+=2){
        pi += (double) 1/(i*2+1) * 4;
    }
}

void *pileibnitz_negative(){
    for(int i=1; i< iterations; i+=2){
        pi -= (double) 1/(i*2+1) * 4;
    }
}

void main(){
    FILE *fo;
    fo = fopen ("pi2h.txt", "a");
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;

    pthread_t thread1;
    pthread_t thread2;

    double exec_time;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
    pthread_create(&thread1, NULL, (void *)pileibnitz_positive, NULL);
    pthread_create(&thread2, NULL, (void *)pileibnitz_negative, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    QueryPerformanceCounter(&end);
    exec_time = (double) (end.QuadPart - start.QuadPart)/frequency.QuadPart;
    fprintf(fo, "%f", exec_time);
    fclose(fo);
    printf("Pi calculated with %f interactions \n With a value of %f \n Executed in %f seconds", iterations, pi, exec_time);
}
