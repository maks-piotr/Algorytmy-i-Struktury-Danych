#include <iostream>
#include <string>
#include <ctime>
#include <random>
#include <algorithm>

using namespace std;
random_device rd;
mt19937 mt(rd());
void create_random_sorted_series(int* array, int s) {
    for (int i= 0; i < s; i++) {
        array[i] = mt()%(2*s);
    }
    sort(array,array+s);
}

void print_random_sorted_series(int* array, int s) {
    for (int i= 0; i < s; i++) {
        cout << array[i] << " ";
    }
    cout << "\n";
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Nieprawidlowa liczba elementow.\n";
        return 1;
    }
    cout << argv[1] << " ";
    int s = stoi(argv[1]);
    int* array = new int[s];
    create_random_sorted_series(array, s);
    cout << 2*s << " ";
    print_random_sorted_series(array, s);
    return 0;
}