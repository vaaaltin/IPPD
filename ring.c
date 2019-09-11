//send: data, count, datatype, destination, tag, communicator
//receive: data, count, datatype, source, tag, communicator, status
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  int world_rank, world_size, token;

  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  double t_inicio[world_size], t_fim[world_size], t_decorrido[world_size];
  t_inicio[world_rank] = MPI_Wtime();

  MPI_Send(&token, 1, MPI_INT, (world_rank + 1) % world_size, 0,
           MPI_COMM_WORLD);
  t_fim[world_rank] = MPI_Wtime();
  t_decorrido[world_rank] = t_fim[world_rank] - t_inicio[world_rank];
  printf("Process %d sended token %d from process %d time of %f\n", world_rank, token,
           world_rank + 1, t_decorrido[world_rank]);
  
   // Receive from the lower process and send to the higher process. Take care
  // of the special case when you are the first process to prevent deadlock.
  if (world_rank != 0) {
    t_fim[world_rank] = MPI_Wtime();
    t_decorrido[world_rank] = t_fim[world_rank] - t_inicio[world_rank];
    
    MPI_Recv(&token, 1, MPI_INT, world_rank - 1, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
    printf("Process %d received token %d from process %d time of %f\n", world_rank, token,
           world_rank - 1, t_decorrido[world_rank]);
  } else {
    // Set the token's value if you are process 0
    token = -1;
  }
  // Now process 0 can receive from the last process. This makes sure that at
  // least one MPI_Send is initialized before all MPI_Recvs (again, to prevent
  // deadlock)
  if (world_rank == 0) {
    MPI_Recv(&token, 1, MPI_INT, world_size - 1, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
    t_fim[world_rank] = MPI_Wtime();
    t_decorrido[world_rank] = t_fim[world_rank] - t_inicio[world_rank];
    printf("Process %d received token %d from process %d time of %f\n", world_rank, token,
           world_size - 1, t_decorrido[world_rank]);
  }
  MPI_Finalize();
}
