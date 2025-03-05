/*
Author: Saptarshi Mandal

Naive Parallalization. 
No point to point communication involved. 

To compile: mpicc HelloWorldMPInaive.c
To run    : mpirun -np 4 a.out , Note: 4 is the number of processes     
*/
#include <stdio.h>
#include <mpi.h>
int main(int argc, char *argv[])
{

    int my_rank,p;     
    MPI_Init(&argc, &argv);                                // MPI Start

    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);                // Get the rank of the process
    MPI_Comm_size(MPI_COMM_WORLD,&p);                      // Get number of processes
    
    printf("Hello world from the process %d \n",my_rank);

    MPI_Finalize();                                         // MPI Stop
}
