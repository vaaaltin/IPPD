#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <omp.h>

#include "src/sum.h"

int main(int argc, char **argv){
	char *awnser[] = { "bad", "ok" };

	long long int i, vsum, n;
	int *v;
	double elapsed, start, end;

	if(argc != 2){
		fprintf(stderr, "Usage: %s <number of elements>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	n = atoll(argv[1]);
	printf("number of elements: %lld\n", n);

	v = (int *) malloc(n * sizeof(int));
	assert(v != NULL);

	for(i = 0; i < n; i++)
		v[i] = 1; /* Do not change it! */

	start = omp_get_wtime();
	vsum = sum(v, n);
	end = omp_get_wtime();

	elapsed = end - start;

	printf("sum value is %s\ntime: %.3f seconds\n", awnser[vsum == n], elapsed);

	free(v);

	return 0;
}