#include <omp.h>

long long int sum(int *v, long long int N){
	long long int i, sum = 0;

        //use with export OMP_SCHEDULE="dynamic,4", for example.
        #pragma omp parallel for private(i) reduction(+ : sum) schedule(runtime)
	for(i = 0; i < N; i++)
		sum += v[i];

	return sum;
}
