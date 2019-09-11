#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char **argv){
    MPI_Init(NULL, NULL);
    int world_rank, world_size;
    char greeting[100];

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if(world_rank != 0){
        sprintf(greeting, "Greeting from process %d of %d", world_rank, world_size);
        MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }else{
        for(int q=1; q<world_size; q++){
            MPI_Recv(greeting, 100, MPI_CHAR, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s\n", greeting);
        }
    }

  

    MPI_Finalize();
    return 0;
}