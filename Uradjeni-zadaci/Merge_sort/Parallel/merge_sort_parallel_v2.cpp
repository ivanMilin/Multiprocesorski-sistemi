#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <new>
#include <omp.h>
#include <bits/stdc++.h>

using namespace std::chrono;
using namespace std; 

void merge(int array[], int const left, int const mid, int const right) {
    int const subArrayOne = mid - left + 1;
    int const subArrayTwo = right - mid;

    auto *leftArray = new int[subArrayOne], *rightArray = new int[subArrayTwo];

    for (auto i = 0; i < subArrayOne; ++i)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; ++j)
        rightArray[j] = array[mid + 1 + j];

    auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;

    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            ++indexOfSubArrayOne;
        } else {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            ++indexOfSubArrayTwo;
        }
        ++indexOfMergedArray;
    }

    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        ++indexOfSubArrayOne;
        ++indexOfMergedArray;
    }

    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        ++indexOfSubArrayTwo;
        ++indexOfMergedArray;
    }
    delete[] leftArray;
    delete[] rightArray;
}

void mergeSort(int array[], int const begin, int const end) {
    if (begin >= end)
        return;

    int mid = begin + (end - begin) / 2;

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            mergeSort(array, begin, mid);
        }
        #pragma omp section
        {
            mergeSort(array, mid + 1, end);
        }
    }

    merge(array, begin, mid, end);
}

void printArray(int A[], int size) {
    for (int i = 0; i < size; i++)
        cout << A[i] << " ";
    cout << endl;
}

void sortChecking(int *array, int start, int finish) {
    for (int i = start; i < finish; i++) {
        if (array[i + 1] < array[i]) {
            printf("Sort does not work, index is %d\n", i);
        }
    }
}

int main(int argc, char *argv[]) {

    int tc = strtol(argv[1], NULL, 10);
    int length = strtol(argv[2], NULL, 10);

    omp_set_num_threads(tc);

    int *array = new int[length];

    double s = omp_get_wtime();
    srand(time(NULL));
    for (int i = 0; i < length; i++) {
        array[i] = rand() % 500;
    }
    
    mergeSort(array, 0, length - 1);

    sortChecking(array, 0, length - 1);

    s = (omp_get_wtime() - s)*1000;
    printf("Elapsed time is : %.0lf ms\n",s);

    delete[] array;
    return 0;
}

/*
./merge_sort_parallel_v2 2 10000000
Elapsed time is : 9324 ms
*/