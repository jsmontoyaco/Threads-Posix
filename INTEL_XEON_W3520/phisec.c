#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <windows.h>


#define iterations 1e9

double pi = 0;

double pileibnitz(){
    for(int i=0; i< iterations; i++){
        pi += (double) 1/(i*2+1) * 4;
        i++;
        pi -= (double) 1/(i*2+1) * 4 ;
    }
    return pi;
}

void main(){
    FILE *fo;
    fo = fopen ("pithreaddata.txt", "a");
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double exec_time;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
    double pi = pileibnitz();
    QueryPerformanceCounter(&end);
    exec_time = (double) (end.QuadPart - start.QuadPart)/frequency.QuadPart;
    fprintf(fo, "1Thread %f", exec_time);
    fclose(fo);
    //printf((long int)t_execution.tv_sec);
    printf("Pi calculated with %f iteractions \n With a value of %f \n Executed in %f seconds", iterations, pi, exec_time);
}
