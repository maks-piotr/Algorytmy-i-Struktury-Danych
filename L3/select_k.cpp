#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;

int assign_count, compare_count, partition_count;
bool less_than_fifty;
unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
int siz, grp;
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
void insertion_sort(int *arr, int s)
{
    for (int i = 1; i < s; i++)
    {
        int k = arr[i];
        int j = i - 1;
        while (j >= 0 && is_greater(arr[j],k))
        {
            assign(&arr[j+1],arr[j]);
            j--;
        }
        arr[j + 1] = k;
    }
}
int partition(int *arr, int p, int q, int piv) {
    int pivot = piv;
    int i = p;
    for (int j = p+1; j <= q; j++) {
        if (arr[j] == pivot) {
            swp(arr+p,arr+j);
            break;
        }
    }
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
    
int ceili(int numerator, int denominator)
{
    return (numerator / denominator + (numerator % denominator != 0));
} 

int select(int* A, int p, int q, int i) {
    int x = p;
    //cout << ceili((q-p+1),grp) << "\n" << flush;
    int* median_arr = new int[ceili((q-p+1),grp)];
    
    int j = 0;
    while (x+(grp-1) <= q) {
        //cout << "nie";
        //cout << x << "\n";
        insertion_sort(A+x,grp);
        median_arr[j] = A[x+(grp/2)];
        j++;
        x+=grp;
    }
    if (x <= q || j == 0) {
        //cout << "ok";
        median_arr[j] = A[x];
        j++;
    }
    int median_of_medians = median_arr[0];
    if (j > 1) {
        median_of_medians = select(median_arr, 0, ceili((q-p+1),grp)-1, ((q-p+1)/grp + 1)/2);
    }
    free(median_arr);
    int r = partition(A,p,q,median_of_medians);
    int k = r  - p + 1;
    if (i == k) {
        return median_of_medians;
    }
    if (i < k) {
        return select(A, p, r-1, i);
    }
    else {
        return select(A,r+1,q,i-k);
    }
}

int main(int argc, char** argv) {

    partition_count = 0;
    compare_count = 0;
    assign_count = 0;
    grp = stoi(argv[1]);
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
    int stat = select(arry,0,siz-1,k);
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