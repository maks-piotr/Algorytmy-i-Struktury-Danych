#include <iostream>
#include <chrono>
using namespace std;

int compare_count;

bool is_greater(int a, int b) {
    compare_count++;
    if (a > b) {
        return true;
    }
    return false;
}
bool is_equal(int a, int b) {
    compare_count++;
    if (a == b) {
        return true;
    }
    return false;
}
int binSearch(int* arr, int p, int q, int x)
{
    if (!is_greater(p,q)) {
        int s = p + (q - p) / 2;
        if (is_equal(arr[s],x))
            return 1;
        if (is_greater(arr[s],x))
            return binSearch(arr, p, s - 1, x);
        return binSearch(arr, s + 1, q, x);
    }
    return 0;
}

int main (int argc, char** argv) {
    int size, x;
    int *array;
    compare_count =0;
    cin >> size;
    cin >> x;
    array = new int[size];
    for (int i = 0; i < size; i++) {
        cin >> array[i];
    }
    
    cout << "Szukana liczba: " << x << "\n";
    auto start = chrono::steady_clock::now();
    int z = binSearch(array,0,size-1, x);
    auto end = chrono::steady_clock::now();
    cout << "Czy znaleziono: " << z << "\n";
    cout << "Liczba porownan: " << compare_count << "\n";
    cout << "Czas w nanosekundach: "
    << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
    << " ns" << endl; 
    return 0;
}