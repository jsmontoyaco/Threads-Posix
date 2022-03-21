
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define iterations 1e9
double pi=0;

double pileibnitz(){
    for(int i=0; i< iterations; i++){
        pi += (double) 1/(i*2+1) * 4;
        i++;
        pi -= (double) 1/(i*2+1) * 4 ;
    }
    return pi;
}

int main(){
    FILE *fo;
    fo = fopen("pithreaddataCOLLAB.txt", "a");
    struct timeval t_before, t_after, t_execution; 
    gettimeofday(&t_before, NULL);
    double pi = pileibnitz();
    gettimeofday(&t_after, NULL);
    timersub(&t_after, &t_before, &t_execution);
    long int seconds = (long int) t_execution.tv_sec;
    long int useconds = (long int) t_execution.tv_usec;
    fprintf(fo, "1Thread %ld.%06ld", seconds, useconds);
    fclose(fo);
    printf("Pi calculated with %f iteractions \n With a value of %f \n Executed in %ld.%06ld seconds", iterations, pi, seconds, useconds);
    return 0;
}