/* 
Student : Milin Ivan E1-79/2023

Zadatak : sekvencijalna implementacija MERGE-SORT algoritma

// g++ -fopenmp -Wall -o merge_sort_sequential merge_sort_sequential.cpp 
// ./merge_sort_sequential 
*/

#include <iostream> 
#include<cstdlib>
#include <chrono>

using namespace std::chrono;
using namespace std; 

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
	auto start_time = high_resolution_clock::now();
	int length;
    //time_t t;
    
    printf("Length of an array : ");
	scanf("%d", &length);

	int array[length];
    for(int i = 0; i != length; i++){
        srand(i);
		array[i] = rand()%500;
    }

	printf("Array before sort is saved in file : 'before_conversion.txt'\n");
	saveArrayInFile("before_conversion.txt",length,array);

	mergeSort(array, 0, length - 1);

	for(int i = 0; i < length-1; i++){
		if(array[i+1]<array[i]){
			printf("Sort does not work, index is %d\n",i);
		}
	}
	
	printf("Array after sort is saved in file  : 'before_conversion.txt'\n");
	saveArrayInFile("after_conversion.txt",length,array);

	auto stop_time = high_resolution_clock::now();
	auto duration_time = duration_cast<milliseconds>((stop_time - start_time));

	cout << "Elapsed time is : " << duration_time.count() << "ms"<< endl;
	
	return 0;
}

/*
Length of an array : 2000000
Array before sort is saved in file : 'before_conversion.txt'
Array after sort is saved in file  : 'before_conversion.txt'
Elapsed time is : 6560ms
*/