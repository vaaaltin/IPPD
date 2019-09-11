#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char **argv){
    int rank_procs, world_size;
    char greeting[100];
    double t_inicio[10], t_fim[10], t_decorrido[10];
    
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank_procs);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if (world_size > 10) {
        fprintf(stderr, "Max world size must be ten for %s\n", argv[0]);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    t_inicio[rank_procs] = MPI_Wtime();
    if(rank_procs != 0){
        sprintf(greeting, "Greeting from process %d of %d", rank_procs, world_size);
        //data, count, datatype, destination, tag, communicator
        MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }else{
        for(int q=1; q<world_size; q++){
            //data, count, datatype, source, tag, communicator, status
            MPI_Recv(greeting, 100, MPI_CHAR, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            t_fim[rank_procs] = MPI_Wtime();
            t_decorrido[rank_procs] = t_fim[rank_procs] - t_inicio[rank_procs];
            printf("%s time of %f \n", greeting, t_decorrido[rank_procs]);
            
        }
    }
    MPI_Finalize();
    return 0;
}