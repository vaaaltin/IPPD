//send: data, count, datatype, destination, tag, communicator
//receive: data, count, datatype, source, tag, communicator, status

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  const int PING_PONG_LIMIT = 50;
  int world_rank, world_size, ping_pong_count=0;

  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  double t_inicio[world_size], t_fim[world_size], t_decorrido[world_size];

  t_inicio[world_rank] = MPI_Wtime();

  if (world_size != 2) {
    fprintf(stderr, "World size must be two for %s\n", argv[0]);
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  int partner_rank = (world_rank + 1) % 2;
  while (ping_pong_count < PING_PONG_LIMIT) {
    if (world_rank == ping_pong_count % 2) {
      // Increment the ping pong count before you send it
      ping_pong_count++;
      MPI_Send(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);

      t_fim[world_rank] = MPI_Wtime();
      t_decorrido[world_rank] = t_fim[world_rank] - t_inicio[world_rank];

      printf("%d sent and incremented ping_pong_count %d to %d time of %f\n",
             world_rank, ping_pong_count, partner_rank, t_decorrido[world_rank]);
    } else {
      MPI_Recv(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD,
               MPI_STATUS_IGNORE);
      
      t_fim[world_rank] = MPI_Wtime();
      t_decorrido[world_rank] = t_fim[world_rank] - t_inicio[world_rank];
      
      printf("%d received ping_pong_count %d from %d time of %f\n",
             world_rank, ping_pong_count, partner_rank, t_decorrido[world_rank]);
    }
  }
  MPI_Finalize();
}
