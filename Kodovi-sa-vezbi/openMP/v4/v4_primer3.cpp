// g++ -fopenmp -Wall -o v4_primer2 v4_primer2.cpp
// ./v4_primer3 8

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[]){
    
    int tc = strtol(argv[1],NULL,10);
    double n;
    double sum = 0;

    printf("Number : ");
    scanf("%lf",&n);

    double s = omp_get_wtime();
    #pragma omp parallel for num_threads(tc) reduction(+:sum)
    for(int i = 0; i<= (int)n; i++){
        sum += (double)i;
    }
    s = omp_get_wtime() - s;

    printf("\nSum is %.0lf\n",sum);
    printf("Executed for %lf s\n",s);
    
    return 0;
}