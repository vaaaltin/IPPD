#include<mpi.h>
#include<stdio.h>
#include<time.h>

int main(int argc, char **argv){
    int world_processors, rank_processors, name_len;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    double t_inicio[10], t_fim[10], t_decorrido[10];
    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &world_processors);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank_processors);

    t_inicio[rank_processors] = MPI_Wtime();
    
    MPI_Get_processor_name(processor_name, &name_len);
    for(long int c=0; c<5000000000; c++){

    }
    t_fim[rank_processors] = MPI_Wtime();
    t_decorrido[rank_processors] = t_fim[rank_processors] - t_inicio[rank_processors];

    printf("Processor %s, rank %d of %d is saying hello, time of %f segs.\n", processor_name, rank_processors, world_processors, t_decorrido[rank_processors]);

    MPI_Finalize();


    return 0;
}