/***********************************************/
/* Nome: Jonathas Conceição                    */
/* Github: Jonathas-Conceicao                  */
/* Make a token bounce between two MPI process */
/***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>
#include <assert.h>

int main (void) {
  int comm_sz;
  int my_rank;
  int *ball;
  ball = calloc(0, sizeof(int));

  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  assert(comm_sz == 2);
  for (int i = 0; i < 10; i++) {
    if (my_rank == *ball) {
      *ball = (my_rank +1) % 2;
      printf("It is I, thread %i, who hold the ball at turn %i!\n", my_rank, i);
      MPI_Send(ball, 1, MPI_INT, *ball, 0, MPI_COMM_WORLD);
    } else {
      MPI_Recv(ball, 1, MPI_INT, (my_rank +1) % 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
  }
  MPI_Finalize();

  free(ball);
  return 0;
}