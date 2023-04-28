#include <iostream>
#include <string>

using namespace std;

int assign_count, compare_count, partition_count;
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
bool is_greater_or_equal(int a, int b) {
    compare_count++;
    if (a >= b) {
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
void swp(int* a, int* b) {
    int temp;
    assign(&temp,*a);
    //int temp = *a;
    assign(a,*b);
    assign(b,temp);
}
int dual_partition(int *arr, int p, int q, int *lp) {
    if (is_greater(arr[p],arr[q])) 
        swp(&arr[p], &arr[q]);
    int b = p + 1;
    int c = q - 1, k = p + 1;
    int pV = arr[p], qV = arr[q];
    
    int l, s;
    while (k <= c) {
        if (s > l) {
            if (is_greater(pV,arr[k])) {
                s++;
                swp(&arr[k], &arr[b]);
                b++;
            }
            else if (is_greater_or_equal(arr[k],qV)) {
                l++;
                while (is_greater(arr[c],qV) && k < c) {
                    c--;
                }
                swp(&arr[k], &arr[c]);
                c--;
                if (is_greater(pV,arr[k])) {
                    swp(&arr[k], &arr[b]);
                    b++;
                }
            }
        }
        else {
            
            if (is_greater_or_equal(arr[k],qV)) {
                l++;
                while (is_greater(arr[c],qV) && k < c) {
                    c--;
                }
                swp(&arr[k], &arr[c]);
                c--;
                if (is_greater(pV,arr[k])) {
                    swp(&arr[k], &arr[b]);
                    b++;
                }
            }
            else if (is_greater(pV,arr[k])) {
                s++;
                swp(&arr[k], &arr[b]);
                b++;
            }
        }

        k++;
    }
    b--;
    c++;
    swp(&arr[p], &arr[b]);
    swp(&arr[q], &arr[c]);
    *lp = b;
    if(less_than_fifty) {
        partition_count++;
        cout << "Partycjonowanie " << partition_count << ": ";
        print_array(arr+p,q-p+1);
    }
    return c; 
}
void quick_sort(int *arr, int p , int q) {
    if (p < q) {
        int lp, rp;
        rp = dual_partition(arr,p,q,&lp);
        quick_sort(arr,p,lp-1);
        quick_sort(arr,lp+1,rp-1);
        quick_sort(arr,rp+1,q);
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

    partition_count = 0;
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
    quick_sort(array,0,size-1);
    if (size < 50) {
        cout << "Tablica wyjsciowa:  ";
        print_array(array,size);
    }
    cout << "Liczba porownan miedzy kluczami: " << compare_count << "\n";
    cout << "Liczba przypisan wartosci: " << assign_count << "\n";
    cout << "Czy tablica posortowana: " << is_sorted(array,size) << "\n";
    return 0;
}