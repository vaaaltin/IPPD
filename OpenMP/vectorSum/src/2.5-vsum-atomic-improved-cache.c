#include <omp.h>

long long int sum(int *v, long long int N){
	long long int i, init, end, slice, sum_local, sum = 0;
	int myid, nthreads;

	#pragma omp parallel private(i, myid, sum_local, init, end) shared(sum, nthreads, slice)
	{
		myid = omp_get_thread_num();
		#pragma omp single
		{
			nthreads = omp_get_num_threads();
			slice = N / nthreads;
		}

		init = myid * slice;
		if(myid == nthreads - 1)
			end = N;
		else
			end = init + slice;

		sum_local = 0;
		for(i = init; i < end; i++)
			sum_local += v[i];

		#pragma omp atomic
		sum += sum_local;
	}
	
	return sum;
}