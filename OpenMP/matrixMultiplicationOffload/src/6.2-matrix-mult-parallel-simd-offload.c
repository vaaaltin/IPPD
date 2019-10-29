void matrix_mult(double *A, double *B, double *C, int N){
	int i, j, k;

	#pragma offload target(mic) in(A:length(N*N)) in(B:length(N*N)) out(C:length(N*N))
	{
		#pragma omp parallel for default(shared) private(i, j, k)
		for(i = 0; i < N; i++)
			for(k = 0; k < N; k++){
				#pragma vector aligned
				#pragma simd
				for(j = 0; j < N; j++)
					C[i * N + j] += A[i * N + k] * B[k * N + j];
			}
	}
}