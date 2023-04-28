#include <iostream>
#include <string>

using namespace std;

int assign_count, compare_count, merge_count;
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
pair<int,int*> merge(pair<int,int*> A, pair<int,int*> B) {
    int s1 = A.first;
    int* arr1 = A.second;
    int s2 = B.first;
    int* arr2 = B.second;
    int i = 0, j =0;
    int* arr3 = new int[s1 + s2];
    while( i!= s1 || j != s2) {
        if (i!= s1 && j != s2) {
            if (is_greater(arr2[j],arr1[i])) {
                assign(&arr3[i+j],arr1[i]);
                i++;
            }
            else {
                assign(&arr3[i+j],arr2[j]);
                j++;
            }
        }
        else if (i != s1) {
            assign(&arr3[i+j],arr1[i]);
            i++;
        }
        else {
            assign(&arr3[i+j],arr2[j]);
            j++;
        }
    }
    if (s1>1) {
        delete[] arr1;
    }
    return make_pair(s1+s2,arr3);

    
}
pair<int,int*> merge_sort(int *arr, int s)
{
    if (s== 1) {
        return make_pair(s,arr);
    }
    else {
        pair<int,int*> B = merge_sort(arr,s/2);
        pair<int,int*> C = merge_sort(arr + s/2,(s+1)/2);
        pair<int,int*> A = merge(B,C);
        if (less_than_fifty) {
            merge_count++;
            cout << "Scalenie " << merge_count << ": ";
            print_array(A.second,A.first);
        }
        return A;
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
    merge_count = 0;

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
    pair<int,int*> sorted = merge_sort(array,size);
    if (size < 50) {
        cout << "Tablica wyjsciowa:  ";
        print_array(sorted.second,size);
    }
    cout << "Liczba porownan miedzy kluczami: " << compare_count << "\n";
    cout << "Liczba przypisan wartosci: " << assign_count << "\n";
    cout << "Czy tablica posortowana: " << is_sorted(sorted.second,size) << "\n";
    return 0;
}