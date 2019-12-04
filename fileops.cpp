#include <string>
#include <cstring>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <ctime>

const int bufsize = 1<<10;

void file_ops(const char *internalDataPath) {
    for (int chunks = 100; chunks < 1000; chunks += 100) {
        auto start = clock();
        for (int repeat = 0; repeat < 300; ++repeat) {
            FILE *f = fopen("tmp", "w+");
            unsigned char *buffer = new unsigned char[bufsize];
            for (int i = 0; i < bufsize; i++)
                buffer[i] = (i % 90) + 32;

            for (int i = 0; i < chunks; i++)
                fwrite(buffer, sizeof(char), bufsize, f);

            fseek(f, 0, SEEK_SET);
            for (int i = 0; i < chunks; i++) {
                memset(buffer, 0, bufsize);
                fread(buffer, sizeof(char), bufsize, f);
                assert(buffer[0] == 32 && buffer[100] == 42 && buffer[500] == (500 % 90) + 32);
            }
            fclose(f);
        }
        printf("Time taken for %d chunks = %lld\n",
                chunks, (clock() - start) /  (CLOCKS_PER_SEC / 1000));
    }
}

int main(int argc, char **argv) {
	file_ops(".");
	return 0;
}
