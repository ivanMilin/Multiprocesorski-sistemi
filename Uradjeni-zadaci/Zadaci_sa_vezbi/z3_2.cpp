/* 
Student : Milin Ivan E1-79/2023

Zadatak 3.2 : Sumiranje prvih N prirodnih brojeva upotrebom blokovske strategije

mpic++ -o z3_2 z3_2.cpp
mpiexec -n 4 ./z3_2
*/

#include <stdio.h>
#include <mpi.h>
#include <cmath>

double getInput(){
    double res;
    printf("Number : ");
    fflush(stdout);
    scanf("%lf",&res);
    return (double)(res);
}

int main(int argc, char *argv[])
{
    double n;
    double sum = 0;
    double tsum;
    
    int csize, prank;
    int start, finish, iterration;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &csize);
    MPI_Comm_rank(MPI_COMM_WORLD, &prank);

    if(prank == 0){
        n = getInput();
    }

    MPI_Bcast(&n, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double s = MPI_Wtime();

    start  = n*prank/csize + 1;
    finish = n*(prank+1)/csize;
    iterration = start;
    
    while(iterration<=finish){
        sum = sum + iterration;
        iterration ++;
    }

    MPI_Reduce(&sum, &tsum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    double e = MPI_Wtime();
    double d = e-s;
    double mind; 
    
    MPI_Reduce(&d, &mind, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if(prank == 0){
        printf("\nSum of first %.0f numbers is %.0f\n", n, tsum);
        printf("Elapsed time: %f\n\n",d);
    }

    MPI_Finalize();

    return 0;
}