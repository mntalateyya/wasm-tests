#include <stdio.h>
#include <time.h>
#include <assert.h>

short A[1000][1000];
short B[1000][1000];
short C[1000][1000];

void matmul_unchecked(int n, int m, int k) {
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

int main() {
	for (int size = 100; size <= 500; size += 100) {
		for (int i = 0; i < size ; i++)
			for (int j = 0; j < size; ++j)
				A[i][j] = B[i][j] = 1;

		long long start = clock();
		for (int repeat = 0; repeat < 5; repeat++) {
			matmul_unchecked(size, size, size);
		}

		long long end = clock();
		printf("%d, %lld\n", size, (end - start) /  (CLOCKS_PER_SEC / 1000));
	}
	return 0;
}
