/* 
Student : Milin Ivan E1-79/2023

Zadatak : paralelna implementacija MERGE-SORT algoritma

// g++ -fopenmp -Wall -o merge_sort_parallel merge_sort_parallel.cpp
// ./merge_sort_parallel <number_of_threads> <array_length>
*/

#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <math.h>
#include <bits/stdc++.h>

using namespace std;

// Merges two subarrays of array[].
// First subarray is arr[begin..mid]
// Second subarray is arr[mid+1..end]
void merge(int array[], int const left, int const mid,
		int const right)
{
	int const subArrayOne = mid - left + 1;
	int const subArrayTwo = right - mid;

	// Create temp arrays
	auto *leftArray = new int[subArrayOne],
		*rightArray = new int[subArrayTwo];

	// Copy data to temp arrays leftArray[] and rightArray[]
	for (auto i = 0; i < subArrayOne; i++)
		leftArray[i] = array[left + i];
	for (auto j = 0; j < subArrayTwo; j++)
		rightArray[j] = array[mid + 1 + j];

	auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
	int indexOfMergedArray = left;

	// Merge the temp arrays back into array[left..right]
	while (indexOfSubArrayOne < subArrayOne
		&& indexOfSubArrayTwo < subArrayTwo) {
		if (leftArray[indexOfSubArrayOne]
			<= rightArray[indexOfSubArrayTwo]) {
			array[indexOfMergedArray]
				= leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
		}
		else {
			array[indexOfMergedArray]
				= rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}

	// Copy the remaining elements of
	// left[], if there are any
	while (indexOfSubArrayOne < subArrayOne) {
		array[indexOfMergedArray]
			= leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}

	// Copy the remaining elements of
	// right[], if there are any
	while (indexOfSubArrayTwo < subArrayTwo) {
		array[indexOfMergedArray]
			= rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
	delete[] leftArray;
	delete[] rightArray;
}

// begin is for left index and end is right index
// of the sub-array of arr to be sorted
void mergeSort(int array[], int const begin, int const end)
{
	if (begin >= end)
		return;

	int mid = begin + (end - begin) / 2;
	mergeSort(array, begin, mid);
	mergeSort(array, mid + 1, end);
	merge(array, begin, mid, end);
}

// Function to print an array
void printArray(int A[], int size)
{
	for (int i = 0; i < size; i++)
		cout << A[i] << " ";
	cout << endl;
}

void saveArrayInFile(const char *filename, int length, int *array) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Nisam uspeo da otvorim fajl");
        return;
    }

    for (int i = 0; i < length; i++) {
        fprintf(f, "%d ", array[i]);
    }

    fclose(f);
}

int main(int argc, char *argv[])
{
    //time_t t;
	double s = omp_get_wtime();
    
	int tc = strtol(argv[1],NULL,10);
    int length = strtol(argv[2],NULL,10);
	
    int array[length];

    for(int i = 0; i != length; i++){
        srand(i);
		array[i] = rand()%500;
    }

	printf("Length of an array : %d\n",length);
	printf("Array before sort is saved in file : 'before_conversion.txt'\n");
	saveArrayInFile("before_conversion.txt",length,array);


	#pragma omp parallel num_threads(tc)
	{
	    int trank = omp_get_thread_num();	
	    double i = (double) trank;
	    double ds =(double) tc;

	    int start  = length*i/ds;
	    int finish = length*(i + 1)/ds-1;
	    mergeSort(array,start,finish);   
	}

	mergeSort(array, 0, length - 1);
	
	for(int i = 0; i < length-1; i++){
		if(array[i+1]<array[i]){
			printf("Sort does not work, index is %d\n",i);
		}
	}
	
	printf("Array after sort is saved in file  : 'before_conversion.txt'\n");
	saveArrayInFile("after_conversion.txt",length,array);

    s = (omp_get_wtime() - s)*1000;

    printf("Elapsed time is : %.0lf ms\n", s);

	return 0;
}

/*
				./merge_sort_parallel 2 2000000
Length of an array : 2000000
Array before sort is saved in file : 'before_conversion.txt'
Array after sort is saved in file  : 'before_conversion.txt'
Elapsed time is : 3510 ms
				
				./merge_sort_parallel 3 2000000
Length of an array : 2000000
Array before sort is saved in file : 'before_conversion.txt'
Array after sort is saved in file  : 'before_conversion.txt'
Elapsed time is : 3392 ms

				./merge_sort_parallel 4 2000000
Length of an array : 2000000
Array before sort is saved in file : 'before_conversion.txt'
Array after sort is saved in file  : 'before_conversion.txt'
Elapsed time is : 3383 ms
				
				 ./merge_sort_parallel 5 2000000
Length of an array : 2000000
Array before sort is saved in file : 'before_conversion.txt'
Array after sort is saved in file  : 'before_conversion.txt'
Elapsed time is : 3363 ms
				
				./merge_sort_parallel 6 2000000
Length of an array : 2000000
Array before sort is saved in file : 'before_conversion.txt'
Array after sort is saved in file  : 'before_conversion.txt'
Elapsed time is : 3347 ms
				
				./merge_sort_parallel 7 2000000
Length of an array : 2000000
Array before sort is saved in file : 'before_conversion.txt'
Array after sort is saved in file  : 'before_conversion.txt'
Elapsed time is : 3391 ms
				
				./merge_sort_parallel 8 2000000
Length of an array : 2000000
Array before sort is saved in file : 'before_conversion.txt'
Array after sort is saved in file  : 'before_conversion.txt'
Elapsed time is : 3357 ms*/
