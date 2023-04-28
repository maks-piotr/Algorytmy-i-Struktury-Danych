#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;

int assign_count, compare_count, partition_count;
int cnt;
bool less_than_fifty;
unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
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
void print_array(int *arr, int s) {

    for (int i= 0; i < s; i++) {
            if (arr[i] < 10) {
                cout << "0";
            }
            cout << arr[i] << " ";
        }
    cout << "\n";
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
    /*if (less_than_fifty) {
        partition_count++;
        cout << "Partycjonowanie " << partition_count << ", ";
        cout << "Pivot: " << pivot << ", ";
        cout << p << " " << q;
        print_array(arr+p,q-p+1);
        
    }*/
    return i;
}
    
int ceili(int numerator, int denominator)
{
    return (numerator / denominator + (numerator % denominator != 0));
} 

int select(int* A, int p, int q, int i) {
    int x = p;
    int* median_arr = new int[ceili((q-p+1),5)];
    // cout << ceili((q-p+1),5) << "\n";
    int j = 0;
    while (x+4 <= q) {
        //cout << "nie";
        //cout << x << "\n";
        insertion_sort(A+x,5);
        median_arr[j] = A[x+2];
        j++;
        x+=5;
    }
    if (x < q || j == 0) {
        //cout << "ok";
        median_arr[j] = A[x];
        j++;
    }
    int median_of_medians = median_arr[0];
    if (j > 1) {
        median_of_medians = select(median_arr, 0, ceili((q-p+1),5)-1, ((q-p+1)/5 + 1)/2);
    }
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
    
    
void quick_sort_select(int *arr, int p , int q) {
    if (p < q) {
        int r = select(arr,p,q,(q-p)/2+1);
        if (less_than_fifty) {
            cnt++;
            cout << "p: " << p << ", q: " << q << ", tab[p..q] po select " << cnt << ": ";
            print_array(arr,q-p+1);
        }
        quick_sort_select(arr,p,p+(q-p)/2-1);
        quick_sort_select(arr,p+(q-p)/2+1,q);
    }
    return;
}

bool is_sorted(int *arr, int s) {
    for (int i=1; i < s; i++) {
        if (arr[i] < arr[i-1]) {
            return false;
        }
    }
    return true;
}


int main(int argc, char *argv[]) {

    partition_count = 0;
    cnt = 0;
    compare_count = 0;
    assign_count = 0;
    int size;
    int *array;
    
    cin >> size;
    array = new int[size];
    for (int i = 0; i < size; i++) {
        cin >> array[i];
    }

    
    less_than_fifty = false;
    if (size < 50) {
        less_than_fifty = true;
        cout << "Tablica wejsciowa:  ";
        print_array(array,size);
    }
    cout << "Sortowanie:\n";
    auto start = chrono::steady_clock::now();
    quick_sort_select(array,0,size-1);
    auto end = chrono::steady_clock::now();
    if (size < 50) {
        cout << "Tablica wyjsciowa:  ";
        print_array(array,size);
    }
    cout << "Czas w mikrosekundach: "
    << chrono::duration_cast<chrono::microseconds>(end - start).count()
    << " µs" << endl;  
    cout << "Liczba porownan miedzy kluczami: " << compare_count << "\n";
    cout << "Liczba przypisan wartosci: " << assign_count << "\n";
    cout << "Czy tablica posortowana: " << is_sorted(array,size) << "\n";
    return 0;
}