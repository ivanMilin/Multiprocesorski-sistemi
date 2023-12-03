#include <bits/stdc++.h> 
#include <cmath>
#include <omp.h>

using namespace std; 
  
void storePrimeNumbers(const char *fname,int *prime_numbers, int n){
    FILE *f = fopen(fname,"w");
    for(int i = 0; i != n; i++){
        fprintf(f,"%d ",prime_numbers[i]);
    }
    fclose(f);
}

void SieveOfEratosthenes(int n) { 
    bool prime[n + 1]; 
    int prime_numbers[n];
    memset(prime, true, sizeof(prime)); 
  
    #pragma omp parallel for schedule(static,1)
    for (int p = 2; p <= (int)ceil(sqrt(n)); p++) { 
         
        if (prime[p] == true) { 

            #pragma omp parallel for schedule(static,1)
            for (int i = p * p; i <= n; i += p) 
                prime[i] = false; 
        } 
    } 
   
    for (int p = 2; p <= n; p++){
        if (prime[p]){
            cout << p << " ";
        }
    }        
    storePrimeNumbers("prime_numbers.txt",prime_numbers,n);
}
  
int main() 
{ 
    int number;
    cout << "Uneti broj do kog je potrebno traziti proste brojeve: ";
    cin >> number;
    cout << "\nFollowing are the prime numbers smaller " << " than or equal to " << number << endl; 
    
    double s = omp_get_wtime();
    
    SieveOfEratosthenes(number);

    s = omp_get_wtime() - s;

    cout << "\nElapsed time: "<<s<<" s\n"<<endl;
    return 0; 
}


/*
1. Obrisi brojeve iz fajla pri svakom novom pokretanju
2. Moras da skontas kako da smestan elemente jedan za drugim a ne da postoji offset izmedju svakog koji je zapravo index prosti broj

*/