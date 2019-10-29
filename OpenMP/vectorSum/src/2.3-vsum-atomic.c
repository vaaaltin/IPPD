#include <omp.h>

long long int sum(int *v, long long int N){
	long long int i, sum = 0;
	int myid, nthreads;

	#pragma omp parallel private(i, myid) shared(sum, nthreads)
	{
		myid = omp_get_thread_num();
		#pragma omp single
		nthreads = omp_get_num_threads();

		for(i = myid; i < N; i += nthreads)
			#pragma omp atomic
			sum += v[i];
	}
	
	return sum;
}