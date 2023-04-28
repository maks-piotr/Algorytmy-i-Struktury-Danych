#include <iostream>
#include <string>

using namespace std;

int assign_count, compare_count;
bool less_than_fifty;
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
void print_array(int *arr, int s) {

    for (int i= 0; i < s; i++) {
            if (arr[i] < 10) {
                cout << "0";
            }
            cout << arr[i] << " ";
        }
    cout << "\n";
}
int parent(int i) {
    return i/2;
}
int left(int i) {
    return 2*i +1;
}
int right(int i) {
    return 2*i +2;
}

void heapify(int *arr, int n, int i)
{
    int l = left(i);
    int r = right(i);
    int largest = i;
    if (l < n && is_greater(arr[l], arr[i])) {
        largest = l;
    }
    if (r < n && is_greater(arr[r], arr[largest])) {
        largest = r;
    }
    if (largest != i) {
        int tmp = arr[i];
        assign(arr+i,arr[largest]);
        assign(arr+largest,tmp);
        heapify(arr, n, largest);
    }
}
void build_heap(int *arr, int n) {
    for (int i = n/2 -1; i >= 0; i--) {
        heapify(arr,n,i);
    }
}
void heap_sort(int* arr, int n) {
    build_heap(arr,n);
    //print_array(arr,n);
    for (int i = n-1; i > 0; i--) {
        int tmp = arr[0];
        assign(arr,arr[i]);
        assign(arr+i,tmp);
        if (less_than_fifty) {
            cout << "Pre-Heapify " << n-i << "\n";
            print_array(arr, n);
        }
        heapify(arr,i,0);
        if (less_than_fifty) {
            cout << "Heapify " << n-i << "\n";
            print_array(arr, n);
        }
    }
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
    heap_sort(array,size);
    if (size < 50) {
        cout << "Tablica wyjsciowa:  ";
        print_array(array,size);
    }
    cout << "Liczba porownan miedzy kluczami: " << compare_count << "\n";
    cout << "Liczba przypisan wartosci: " << assign_count << "\n";
    cout << "Czy tablica posortowana: " << is_sorted(array,size) << "\n";
    return 0;
}