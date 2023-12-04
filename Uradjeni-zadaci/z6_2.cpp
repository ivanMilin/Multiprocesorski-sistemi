#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <bits/stdc++.h>
#include <iostream>
#include <vector>

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

void sieveOfEratosthenes(int count, std::vector<int>& prime_numbers) {
    bool arr[count];

    memset(arr, true, sizeof(arr));

    #pragma omp parallel for schedule(static, 1)
        for (int i = 2; i < count; i++) {
            for (int j = i * i; j < count; j += i) {
                arr[j - 1] = false;
            }
        }

        for (int i = 2; i < count; i++) {
            if (arr[i - 1] == true)
                prime_numbers.push_back(i);
        }
}

int main(int argc, char* argv[]) {
    int count;
    std::vector<int> prime_numbers;

    const char* type[5] = {"static","dynamic", "guided", "auto", "runtime"};

    printf("\nBroj do kog je potrebno traziti proste brojeve: ");
    scanf("%d", &count);

    double s = omp_get_wtime();

    sieveOfEratosthenes(count, prime_numbers);

    savePrimeNumbersToFile("prime_numbers.txt", prime_numbers);

    s = omp_get_wtime() - s;
    
    printf("Elapsed time %lf s\n",s);

    return 0;
}



