#include <vector>
#include <iostream>
#include <ctime>
#include <cassert>

using namespace std;

void matmul(int n, int m, int k, vector<int> &A, vector<int> &B, vector<int> &C) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			int acc = 0;
			for (int l = 0; l < m; l++) {
				acc += A.at(i*m+l) * B.at(l*k+j);
			}
			C.at(i*k+j) = acc;
		}
	}
}

int main(int argc, char **argv) {
	for (int size = 20; size < 150; size += 20) {
		vector<int> A(size*size, 1);
		vector<int> B(size*size, 1);
		vector<int> C;
		C.resize(size*size);

		auto start = clock();
		for (int repeat = 0; repeat < 300; repeat++) {
			matmul(size, size, size, A, B, C);
		}
		cout << "Time taken for size " << size << ": " 
			<< (clock() - start) /  (CLOCKS_PER_SEC / 1000) << endl;

		for (int i = 0; i < size * size; i++)
			assert(C[i] == size);
	}
	return 0;
}
