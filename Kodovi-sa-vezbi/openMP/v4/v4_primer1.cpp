//g++ -fopenmp -Wall -o v4_primer1 v4_primer1.cpp
// ./v4_primer1
#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[]){
    #pragma omp parallel num_threads(8)
    {
        int trank = omp_get_thread_num();
        int tc = omp_get_num_threads();
        printf("Hello from thread %d of %d\n",trank,tc);
    }
    return 0;
}