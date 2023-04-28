#include <iostream>
#include <string>
#include <ctime>
#include <random>
#include <vector>
#include <algorithm>

using namespace std;
vector<int> v;
void generate_random_series(int s) {
    mt19937 mt(time(nullptr)); 
    for (int i= 0; i < s; i++) {
        v.push_back(mt()%(2*s));
    }
    cout << "\n";
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Nieprawidlowa liczba elementow.\n";
        return 1;
    }
    cout << argv[1] << " ";
    generate_random_series(stoi(argv[1]));
    sort(v.begin(), v.end(), greater<int>());
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    return 0;
}