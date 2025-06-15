/*
Author: Saptarshi Mandal

Hello World with point to point communication. 

Process 1 to (n-1) create and send the message to process 0
Process 0 receives the message and prints it.

To compile: mpicc MPI_HelloWorld2.c
To run:     mpirun -np 4 a.out , Note: 4 is the number of processes     

*/
#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{

    int my_rank,p;
    char messages[100]; // Buffer to hold messages
    MPI_Status status;
    MPI_Init(&argc, &argv);                                // MPI Start
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);                // Get the rank of the process
    MPI_Comm_size(MPI_COMM_WORLD, &p);                      // Get number of processes
    if (my_rank != 0)
    {
        sprintf(messages, "Hello worlld form the process %d \n", my_rank);
        MPI_Send(messages, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD); // Send message to process 0
    }else // rank 0 receives messages from all other processes
    {
        for (int i = 1; i < p; i++)
        {
            MPI_Recv(messages, 100, MPI_CHAR, i, 0, MPI_COMM_WORLD, &status); // Receive message from process i
            printf("%s", messages); // Print the received message
        }
    }


    MPI_Finalize();                                         // MPI Stop
}
