#include <stdlib.h>
#include <stdio.h>
//#include <sys/time.h> //For linux
#include <windows.h> //for windows OS
#include <pthread.h>

#define iterations 1e09
#define threads 4
double pithval[threads];
int pith[threads];
double pi = 0.0;

void *pileibnitz(void *arg){
    int init, ending, div = *(int *)arg;
    init = (iterations/threads) * div;
    ending = init + ((iterations/threads) -1);
    pithval[div] = 0.0;
    //printf("Init %i, Ending %i, div %i \n",init,ending,div);
    for(int i=init; i< ending; i++){
        pithval[div] += (double) (1.0/(i*2+1) * 4.0);
        i++;
        pithval[div] -= (double) (1.0/(i*2+1) * 4.0);
    }
}

void main(){
    FILE *fo;
    fo = fopen ("pithreaddataAMD.txt", "a");
    pthread_t thread[threads];
    int *retval;

    LARGE_INTEGER frequency; //time execution calc command for windows
    LARGE_INTEGER start; //time execution calc command for windows
    LARGE_INTEGER end; //time execution calc command for windows
    double exec_time; //time execution calc command for windows
    QueryPerformanceFrequency(&frequency); //time execution calc command for windows
    QueryPerformanceCounter(&start); //time execution calc command for windows

    //struct timeval tval_before, tval_after, tval_result; //time execution calc command for linux
    //gettimeofday(&tval_before, NULL); //time execution calc command for linux

    for (int i=0; i< threads; i++){
        pith[i]=i;
        pthread_create(&thread[i], NULL, pileibnitz, &pith[i]);
    }
    for (int j=0; j< threads; j++){
        pthread_join(thread[j], (void **) &retval);
        //printf("\nFinished %i join thread\n", j);
    }
    for (int k=0; k< threads; k++){
        //printf("Pi value in thread %i %2.12f \n", k,pithval[k]);
        pi += pithval[k];
    }


    QueryPerformanceCounter(&end); //time execution calc command for windows
    exec_time = (double) (end.QuadPart - start.QuadPart)/frequency.QuadPart; //time execution calc command for windows

    //gettimeofday(&tval_after, NULL); //time execution calc command for linux
    //timersub(&tval_after, &tval_before, &tval_result); //time execution calc command for linux
    //seconds = (long int)tval_result.tv_sec; //time execution calc command for linux
    //useconds = (long int)tval_result.tv_usec; //time execution calc command for linux

    fprintf(fo, "%i %f\n", threads,exec_time);  //time execution calc command for windows
    //fprintf(fo, "%iThread %ld.%06ld", seconds, useconds); //time execution calc command for linux
    fclose(fo);

    //printf("Pi calculated with %f iteractions \n With a value of %f \n Executed in %ld.%06ld seconds", iterations, pi, seconds, useconds); //time execution calc command for linux
    printf("Pi calculated with %f iteractions \n With a value of %f \n Executed in %f seconds", iterations, pi, exec_time); //time execution calc command for windows
    return 0;
}
