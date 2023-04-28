#include <iostream>
#include <string>
#include <ctime>
#include <random>

using namespace std;
random_device rd;
mt19937 mt(rd()); 
void print_random_series(int s) {
    for (int i= 0; i < s; i++) {
        cout << mt()%(2*s) << " ";
    }
    cout << "\n";
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Nieprawidlowa liczba elementow.\n";
        return 1;
    }
    cout << argv[1] << " ";
    int s = stoi(argv[1]);
    cout << argv[2] << " ";
    print_random_series(s);
    return 0;
}