/*
Author: Saptarshi Mandal

Computing a integral to find the value of pi using MPI.
1/(1+x^2) from 0 to 1 is pi/4 

The limit of the integral can be divide into n parts ()and each part can be calculated by a different process. 
The final result can be obtained by summing up the results from all processes
We finally compute the total sum in process 0.

To compile: mpicc MPI_HelloWorld2.c
To run:     mpirun -np 4 a.out , Note: 4 is the number of processes     

*/

#include<stdio.h>
#include<mpi.h>
int main(int argc, char * argv[])   //main function 

{
 int p;
 int my_rank;
 float a = 0.0, b = 1.0; int n = 1000;  //integration limit a,b and the total number of trapezoids is
                                       // multiple of p in this case! 

float start ,finish ;

float h;                              // the step size;
float local_a ;                       // the left end of my process (local)
float local_b ;                       // the right end of my process (local)
int local_n;                          // the number of tapezoids for my calculation (local) 
float integral ;                      //the integral over my integral (local )
float total;                          // total integration over the domain a to b;
int source ;                          // process sending the integral
int dest = 0;                         // all message goes to process zero !
int tag = 0;
MPI_Status status;

float Trap(float local_a, float local_b,int local_n, float h);      //Trapezoidal function declaration

printf("see which process is printing this\n");
MPI_Init(&argc,&argv);                   //MPI Start
MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);  //get the rank of the process
MPI_Comm_size(MPI_COMM_WORLD,&p);        //find out number of process 


//printf("see which process is printing this\n");
h = (b-a)/n;          //step size ! is choosen same for all the processes
local_n = n/p;        //number of intervals assigned to each  processes

local_a = a + ( h * my_rank * local_n );
local_b = local_a + ( local_n * h );
integral = Trap(local_a,local_b,local_n,h);  

//make the broadcast to all the processes

MPI_Barrier(MPI_COMM_WORLD);
start = MPI_Wtick();                         // timimg starts!
 if (my_rank ==0){
    printf("We broadcast all the data from the root process to all the other process THE ROOT PROCESS IS PROCESS 0 \n");
 
   
 MPI_Bcast(&integral,1,MPI_FLOAT,0,MPI_COMM_WORLD);
 }
 
 
 

// asseble the local integrals in procecss 0 and sum up the total integral with MPI_reduce(GLOBAL SUM)
MPI_Reduce(&integral,&total,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);                 
MPI_Barrier(MPI_COMM_WORLD);                      
finish = MPI_Wtick();                                //timing finishes          


   
 /*print the result */
  if (my_rank == 0){
    printf("with n = %d traperoids our estimate\n",n);
    printf("of the integral from %f to %f is = %f \n",a,b,total);
    printf("Elapsed time = %f seconds \n", finish-start);
    
  }







MPI_Finalize();                       //MPI Stop 



}                                     //main function closed !


/* Definiton of the Trapezoidal rule function */ 

float Trap(float local_a, float local_b,int local_n, float h)    // all inputs
{

float integral;
float x;
int i;
float f(float x); // declaration of the funcion we are integrating

integral = (f(local_a) + f(local_b))/2.0;
x = local_a;

 for (i = 1;i <= local_n -1;i++){

   x = x+h;
   integral = integral + f(x);
   
   
   }
   
 integral = integral *h;
 
 return integral;



}


float f(float x)  // definition of the integral function and retun the calculation of the function 
{
 float return_value;
	                	
 return_value = 1 / (1 + ( x*x ));	

 return return_value; 

} //  f closed