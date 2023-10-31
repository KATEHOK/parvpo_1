#define _CRT_RAND_S
#include <stdlib.h>
#include <omp.h>
#include <iostream>

void qwerty(const int threads, const int* array, const unsigned int count)
{
    int max = -1;
    int i;
    #pragma omp parallel num_threads(threads) reduction(max: max) private(i)
    {
        #pragma omp for
        for (i = 0; i < count; ++i) if (array[i] > max) max = array[i];
    }
}

int main(int argc, char** argv)
{
    float start, end;
    const unsigned int c = 100000000;
    start = omp_get_wtime();

    int* arr = (int*)malloc(10 * c * sizeof(int));
    if (arr == NULL) return 1;

    for (int i = 0; i < 10 * c; i++) rand_s((unsigned int*)(arr)+i);

    for (int th = 1; th <= 16; ++th)
        for (int i = 0; i < 10; ++i) qwerty(th, arr + i * c, c);

    free(arr);
    end = omp_get_wtime();
    std::cout << end - start;

	return 0;
}