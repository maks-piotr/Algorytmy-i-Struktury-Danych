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
    //int temp = *a;
    int temp;
    assign(&temp,*a);
    assign(a,*b);
    assign(b,temp);
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
        if (i == s/2 && less_than_fifty) {
            cout << "Polowa posortowana: ";
            print_array(arr,s);
        }
    }
}
int hoare_partition(int *arr, int p, int q) {
    int pivot = arr[(p+q)/2];
    int i = p - 1;
    int j = q + 1;
    while (true) {
        do {
            i++;
        } while(is_greater(pivot,arr[i]));
        do {
            j--;
        } while(is_greater(arr[j],pivot));
        if (i >= j) {
            if (less_than_fifty) {
                partition_count++;
                cout << "Partycjonowanie " << partition_count << ": ";
                print_array(arr+p,q-p+1); 
            }
            
            return j;
        }
        swp(&arr[i],&arr[j]);
    }
    

}
void quick_sort(int *arr, int p , int q) {
    if (q-p+1 <= 7) {
        insertion_sort(arr+p,q-p+1);
    }
    else if (p < q) {
        int r = hoare_partition(arr,p,q);
        quick_sort(arr,p,r);
        quick_sort(arr,r+1,q);
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