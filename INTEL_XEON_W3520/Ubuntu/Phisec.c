#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h> //For linux
//#include <windows.h> //for windows OS

#define iterations 1e9


void pileibnitz(double *picalc){
    for(int i=0; i< iterations; i++){
        *picalc += (double) 1/(i*2+1) * 4;
        i++;
        *picalc -= (double) 1/(i*2+1) * 4 ;
    }
}

void main(){
    FILE *fo;
    fo = fopen ("pithreaddataINTELU.txt", "a");
    double pi=0;
    struct timeval tval_before, tval_after, tval_result; //time execution calc command for linux
    gettimeofday(&tval_before, NULL); //time execution calc command for linux

    //LARGE_INTEGER frequency; //time execution calc command for windows
    //LARGE_INTEGER start; //time execution calc command for windows
    //LARGE_INTEGER end; //time execution calc command for windows
    //double exec_time; //time execution calc command for windows
    //QueryPerformanceFrequency(&frequency); //time execution calc command for windows
    //QueryPerformanceCounter(&start); //time execution calc command for windows

    pileibnitz(&pi);

    //QueryPerformanceCounter(&end); //time execution calc command for windows
    //exec_time = (double) (end.QuadPart - start.QuadPart)/frequency.QuadPart; //time execution calc command for windows

    gettimeofday(&tval_after, NULL); //time execution calc command for linux
    timersub(&tval_after, &tval_before, &tval_result); //time execution calc command for linux
    long int seconds = (long int)tval_result.tv_sec; //time execution calc command for linux
    long int useconds = (long int)tval_result.tv_usec; //time execution calc command for linux

    //fprintf(fo, "1 %f\n", exec_time);  //time execution calc command for windows
    fprintf(fo, "1 %ld.%06ld", seconds, useconds); //time execution calc command for linux
    fclose(fo);

    printf("Pi calculated with %f iteractions \n With a value of %f \n Executed in %ld.%06ld seconds", iterations, pi, seconds, useconds); //time execution calc command for linux
    //printf("Pi calculated with %f iteractions \n With a value of %f \n Executed in %f seconds", iterations, pi, exec_time); //time execution calc command for windows
}
