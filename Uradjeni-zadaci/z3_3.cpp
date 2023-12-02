/* 
Student : Milin Ivan E1-79/2023

Zadatak 3.3 : Skalarni proizvod dva vektora

mpic++ -o z3_3 z3_3.cpp
mpiexec -n 4 ./z3_3
*/

#include <stdio.h>
#include <mpi.h>
#include <cmath>
#include <time.h>

int getInput(){
    int res;
    printf("Vector length : ");
    fflush(stdout);
    scanf("%d",&res);
    return (int)(res);
}

int main(int argc, char *argv[])
{
    int n;
    int sum = 0;
    int tsum;

    int csize, prank;
    int block_size, start, finish, iterration;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &csize);
    MPI_Comm_rank(MPI_COMM_WORLD, &prank);

    if(prank == 0){
        n = getInput();
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int vector1[n], vector2[n];
    time_t random_time;
    srand((unsigned) time(&random_time) + prank);

    for(int i = 0; i<n; i++){
        vector1[i] = rand()%20;
        vector2[i] = rand()%20;
    }

    MPI_Bcast(vector1, n, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(vector2, n, MPI_INT, 0, MPI_COMM_WORLD);

    double s = MPI_Wtime();

    block_size = ceil(float(n)/csize);
    start  = prank * block_size;
    iterration = start;

    if(prank != csize - 1){
        finish = start + block_size;
    }
    else {
        finish = n;
    }
    
    if(start < n){
        while(iterration<finish){
            sum = sum + vector1[iterration]*vector2[iterration];
            iterration ++;
        }
    }    

    MPI_Reduce(&sum, &tsum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    double e = MPI_Wtime();
    double d = e-s;
    double mind; 
    
    MPI_Reduce(&d, &mind, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if(prank == 0){
        printf("\nScalar product of { ");
        for(int i = 0; i<n; i++){
            printf("%d ",vector1[i]);
        }
        printf("} * { ");
        for(int i = 0; i<n; i++){
            printf("%d ",vector2[i]);
        }
        printf("} is %d\n",tsum);
        printf("Elapsed time: %f\n\n",d);
    }

    MPI_Finalize();

    return 0;
}