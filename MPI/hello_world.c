#include<mpi.h>
#include<stdio.h>
#include<time.h>

int main(int argc, char **argv){
    int world_size, rank_procs, name_len;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    double t_inicio[10], t_fim[10], t_decorrido[10];

    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank_procs);
    
    if (world_size > 10) {
        fprintf(stderr, "Max world size must be ten for %s\n", argv[0]);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    t_inicio[rank_procs] = MPI_Wtime();
    
    MPI_Get_processor_name(processor_name, &name_len);
    for(long int c=0; c<500000000; c++){

    }
    t_fim[rank_procs] = MPI_Wtime();
    t_decorrido[rank_procs] = t_fim[rank_procs] - t_inicio[rank_procs];

    printf("Processor %s, rank %d of %d is saying hello, time of %f segs.\n", processor_name, rank_procs, world_size, t_decorrido[rank_procs]);

    MPI_Finalize();


    return 0;
}