#include <stdio.h>
#include <mpi.h>

double getInput(){
    double res;
    printf("Number: ");
    fflush(stdout);
    scanf("%lf", &res);
    return (double)(res);
}

int main(int argc, char *argv[]){
    double n;
    double sum = 0;
    int csize, prank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &csize);
    MPI_Comm_rank(MPI_COMM_WORLD, &prank);

    if(prank == 0){
        n = getInput();
    }

    MPI_Bcast(&n,1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double s  = MPI_Wtime();
    double i  = (double) prank;
    double ds = (double) csize;

    while(i<=n){
        sum += i;   //sum = sum + prank;
        i += ds;    //i = i + csize;
    }

    double tsum;
    MPI_Reduce(&sum, &tsum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    double e = MPI_Wtime();
    double d = e - s; 
    double mind;
    MPI_Reduce(&d, &mind, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if(prank == 0){
        printf("Sum of first %d is %d \n",(int)n,(int)tsum);
        printf("Elapsed time : %f s\n",d);
    }

    MPI_Finalize();

    return 0;
}
