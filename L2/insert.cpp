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
    insertion_sort(array,size);
    if (size < 50) {
        cout << "Tablica wyjsciowa:  ";
        print_array(array,size);
    }
    cout << "Liczba porownan miedzy kluczami: " << compare_count << "\n";
    cout << "Liczba przypisan wartosci: " << assign_count << "\n";
    cout << "Czy tablica posortowana: " << is_sorted(array,size) << "\n";
    return 0;
}