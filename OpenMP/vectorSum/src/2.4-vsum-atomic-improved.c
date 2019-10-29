#include <omp.h>

long long int sum(int *v, long long int N){
	long long int i, sum_local, sum = 0;
	int myid, nthreads;

	#pragma omp parallel private(i, myid, sum_local) shared(sum, nthreads)
	{
		myid = omp_get_thread_num();
		#pragma omp single
		nthreads = omp_get_num_threads();

		sum_local = 0;
		for(i = myid; i < N; i += nthreads)
			sum_local += v[i];

		#pragma omp atomic
		sum += sum_local;
	}
	
	return sum;
}