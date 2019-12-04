#include <stdlib.h>
#include <assert.h>

void matmul(int n, int m, int k,
           int (* restrict A)[m], int (* restrict B)[k], int (* restrict C)[k]
) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			int acc = 0;
			for (int l = 0; l < m; l++) {
				acc += A[i][l] * B[l][j];
			}
			C[i][j] = acc;
		}
	}
}


int main(int argc, char **argv) {
	int n = atoi(argv[1]);
	int m1 = atoi(argv[2]);
	int m2 = atoi(argv[3]);
	int k = atoi(argv[4]);
	assert(n > 0 && m1 > 0 && k > 0 && m1 == m2);

	int *A = malloc(n*m1*sizeof(int));
	int *B = malloc(m1*k*sizeof(int));
	int *C = malloc(n*k*sizeof(int));

	if (!A || !B || !C)
		assert(0);

	for (int i = 0; i < n*m1; i++)
		A[i] = 1;
	for (int i = 0; i < m1*k; i++)
		B[i] = 1;

	for (int repeat = 0; repeat < 300; repeat++) {
		matmul(n, m1, k, (int (*)[m1])A, (int (*)[m1])B, (int (*)[m1])C);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < k; j++)
				assert(C[i*k+j] == m1);
	}
	return 0;
}
