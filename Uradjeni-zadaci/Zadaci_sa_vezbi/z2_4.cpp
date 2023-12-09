/* 
Student : Milin Ivan E1-79/2023

Zadatak 2.4 : Svaki proces salje svakom procesu dvocifreni broj

mpic++ -o z2_4 z2_4.cpp
mpiexec -n 4 ./z2_4
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

const int MAX_STRING = 100;

int main (int argc, char **argv){
    char gret[MAX_STRING];
    int csize, prank;
    int generated_number;
    
    time_t random_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &csize);
    MPI_Comm_rank(MPI_COMM_WORLD, &prank);

    int recieved_number[csize];
    srand((unsigned) time(&random_time) + prank);

    for (int i = 0; i < csize; i++){
        if(i != prank){
            generated_number = prank*10 + rand()%10;
            MPI_Send(&generated_number, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }

    for (int i = 0; i < csize; i++){
        if(i != prank){
            MPI_Recv(&recieved_number[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }

    if(prank != 0){
        sprintf(gret,"Process %d recieved: ", prank);
        for(int i = 0; i<csize;i++){
            if(i != prank){
                char string[MAX_STRING];
                sprintf(string," %d",recieved_number[i]);
                strcat(gret, string);
            }
        }
        MPI_Send(gret,strlen(gret)+1,MPI_CHAR,0,0,MPI_COMM_WORLD);
    }

    if(prank == 0){
        printf("Process 0 recieved: ");
    
        for (int i = 1; i < csize; i++){    
            printf("%d ", recieved_number[i]);
            
            if(i == csize-1){
                printf(" \n");
            }
        }
        
        for (int i = 1; i < csize; i++){    
            MPI_Recv(gret,MAX_STRING,MPI_CHAR,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            printf("%s \n", gret);
        }
    }

    MPI_Finalize();
}