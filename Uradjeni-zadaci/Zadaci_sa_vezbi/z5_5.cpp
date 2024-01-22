/* 
Student : Milin Ivan E1-79/2023

Zadatak 5.5 : Sumiranje prvih N prirodnih brojeva tako sto svaka nit racuna svoju parcijalnu sumu.
              Potom se konacna suma racuna sumiranjem tako dobijenih parcijalnih suma.

// g++ -fopenmp -Wall -o z5_5 z5_5.cpp
// ./z5_5 4
*/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[]){
    
    int tc = strtol(argv[1],NULL,10);

    int n, sum[tc], partial_sum = 0, global_sum = 0 ;
    int start, finish, iterration;

    printf("Number : ");
    scanf("%d",&n);


    double s = omp_get_wtime();
    #pragma omp parallel private(partial_sum,start,finish, iterration) num_threads(tc)
    {
        int trank = omp_get_thread_num();
        start  = n*trank/tc+1;
        finish = n*(trank+1)/tc;
        iterration = start;

        //printf("Thread = %d, start = %d, finish = %d\n",trank, start, finish);

        while(iterration <= finish){
            partial_sum = partial_sum + iterration;
            iterration ++;
        }

        sum[trank] = partial_sum;
        //printf("Thread = %d, sum = %d\n",trank,sum[trank]);
    }

    for(int i = 0; i<tc; i++){
           global_sum = global_sum + sum[i];   
    }

    s = omp_get_wtime() - s;

    printf("\nSum is %d\n", global_sum);
    printf("Executed for %lf s\n",s);
    
    return 0;
}