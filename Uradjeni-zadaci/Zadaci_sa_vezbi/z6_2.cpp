/* 
Student : Milin Ivan E1-79/2023

Zadatak 6.2 : Eratostenovo sito

// g++ -fopenmp -Wall -o z6_2 z6_2.cpp
// ./z6_2
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <bits/stdc++.h>
#include <iostream>
#include <vector>

void savePrimeNumbersToFile(const char *, const std::vector<int>&);
void sieveOfEratosthenes(int, std::vector<int>&,int);

int main(int argc, char* argv[]) {
    int count,index;
    std::vector<int> prime_numbers;

    const char *schedule_type[5] = {"static","dynamic", "guided", "auto", "runtime"};

    printf("\nBroj do kog je potrebno traziti proste brojeve: ");
    scanf("%d", &count);

    printf("\n0 - static\n1 - dynamic\n2 - guided\n3 - auto\n4 - runtime\n");
    printf("\nU zavisnosti od strategije rasporedjivanja, uneti broj od 0-4 : ");
    scanf("%d", &index);

    double s = omp_get_wtime();

    sieveOfEratosthenes(count, prime_numbers,index);

    savePrimeNumbersToFile("prime_numbers.txt", prime_numbers);

    s = omp_get_wtime() - s;

    printf("\nIskoriscen je tip : %s\n", schedule_type[index]);    
    printf("\nElapsed time %lf s\n\n",s);

    return 0;
}

/* Funkcija u kojoj se prosti brojevi iz niza u upisuju fajl*/
void savePrimeNumbersToFile(const char *filename, const std::vector<int>& primes) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Nisam uspeo da otvorim fajl");
        return;
    }

    for (int i = 0; i < primes.size(); i++) {
        fprintf(f, "%d ", primes[i]);
    }

    fclose(f);
}

/* Funkcija u kojoj se odredjuje koji brojevi su prosti*/
void sieveOfEratosthenes(int count, std::vector<int>& prime_numbers,int index) {
    bool arr[count];

    memset(arr, true, sizeof(arr));

    switch(index){
        case 0:
                #pragma omp parallel for schedule(static, 1)
                for (int i = 2; i < count; i++) {
                    #pragma omp parallel for schedule(static, 1)
                    for (int j = i * i; j < count; j += i) {
                        arr[j - 1] = false;
                    }
                }

                for (int i = 2; i < count; i++) {
                    if (arr[i - 1] == true)
                        prime_numbers.push_back(i);
                }
                break;

        case 1:
                #pragma omp parallel for schedule(dynamic, 1)
                for (int i = 2; i < count; i++) {
                    #pragma omp parallel for schedule(dynamic, 1)
                    for (int j = i * i; j < count; j += i) {
                        arr[j - 1] = false;
                    }
                }

                for (int i = 2; i < count; i++) {
                    if (arr[i - 1] == true)
                        prime_numbers.push_back(i);
                }
                break;

        case 2:
                #pragma omp parallel for schedule(guided, 1)
                for (int i = 2; i < count; i++) {
                    #pragma omp parallel for schedule(guided, 1)
                    for (int j = i * i; j < count; j += i) {
                        arr[j - 1] = false;
                    }
                }

                for (int i = 2; i < count; i++) {
                    if (arr[i - 1] == true)
                        prime_numbers.push_back(i);
                }
                break;

        case 3:
                #pragma omp parallel for schedule(auto)
                for (int i = 2; i < count; i++) {
                    #pragma omp parallel for schedule(auto)
                    for (int j = i * i; j < count; j += i) {
                        arr[j - 1] = false;
                    }
                }

                for (int i = 2; i < count; i++) {
                    if (arr[i - 1] == true)
                        prime_numbers.push_back(i);
                }
                break;

        case 4:
            #pragma omp parallel for schedule(runtime)
            for (int i = 2; i < count; i++) {
                #pragma omp parallel for schedule(runtime)
                for (int j = i * i; j < count; j += i) {
                    arr[j - 1] = false;
                }
            }

            for (int i = 2; i < count; i++) {
                if (arr[i - 1] == true)
                    prime_numbers.push_back(i);
            }
            break;

        default: printf("Pogresan unos broja");
    }
}




