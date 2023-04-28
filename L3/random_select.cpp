#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;

int assign_count, compare_count, partition_count;
bool less_than_fifty;
unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
int siz;
int *arry;
std::mt19937 g1 (seed1);
int random(int a, int b) {
    return g1()%(b-a+1)+a;
}
void assign(int *p, int val) {
    assign_count++;
    *p = val;
}
bool is_greater(int a, int b) {
    compare_count++;
    if (a > b) {
        return true;
    }
    return false;
}
void swp(int* a, int* b) {
    //int temp = *a;
    int temp;
    assign(&temp,*a);
    assign(a,*b);
    assign(b,temp);
}
void print_arr(int *arr, int s) {

    for (int i= 0; i < s; i++) {
            if (arr[i] < 10) {
                cout << "0";
            }
            cout << arr[i] << " ";
        }
}

    
int ceili(int numerator, int denominator)
{
    return (numerator / denominator + (numerator % denominator != 0));
} 

int randPartition(int *arr, int p, int q) {
    int rand = random(p,q);
    swp(arr+p,arr+rand);
    int pivot = arr[p];
    int i = p;
    for (int j = p+1; j <= q; j++) {
        if(!is_greater(arr[j],pivot)) {
            i++;
            swp(arr+i,arr+j);
        }
    }
    swp(arr+i,arr+p);
    if (less_than_fifty) {
        partition_count++;
        cout << "Partycjonowanie " << partition_count << ", ";
        cout << "Pivot: " << pivot << ", Partitioned elements: ";
        print_arr(arr+p,q-p+1);
        if (arr == arry) {
            cout << "\nCala tablica: ";
            print_arr(arr,siz);
            cout << "\n";
        }
        cout << "\n";
        
    }
    return i;
}

int randSelect(int* A, int p, int q, int i) {
    if (p == q) {
        return A[p];
    }
    int r = randPartition(A,p,q);
    int k = r - p + 1;
    if (k == i) {
        return A[r];
    }
    else if (i < k) {
        return randSelect(A, p, r-1, i);
    }
    else {
        return randSelect(A, r+1, q, i-k);
    }
}


int main(int argc, char** argv) {

    partition_count = 0;
    compare_count = 0;
    assign_count = 0;
    
    int k;
    
    cin >> siz;
    cin >> k;
    arry = new int[siz];
    for (int i = 0; i < siz; i++) {
        cin >> arry[i];
    }  

    less_than_fifty = false;
    if (siz < 50) {
        less_than_fifty = true;
        cout << "Tablica wejsciowa:  ";
        print_arr(arry,siz);
    }
    cout << "k = " << k << "\n";
    cout << "Select:\n";
    int stat = randSelect(arry,0,siz-1,k);
    cout << "k-ta statystyka pozycyjna: " << stat << "\n";
    if (siz < 50) {
        cout << "Końcowy stan tablicy:  ";
        print_arr(arry,siz);
        cout << "\n";
    }
    sort(arry, arry+siz);
    if (siz < 50) {
        cout << "Posortowany ciag kluczy: ";
        print_arr(arry,siz);
        cout << "\n";
    }
    if (stat == arry[k-1]) {
        cout << "Zgadza sie.\n";
    }
    else {
        cout << "Blad.\n";
    }
    cout << "Liczba porownan miedzy kluczami: " << compare_count << "\n";
    cout << "Liczba przypisan wartosci: " << assign_count << "\n";
    
    return 0;
}