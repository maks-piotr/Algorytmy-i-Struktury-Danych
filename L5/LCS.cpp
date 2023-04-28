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
void print_double_array(int** arr, int* arr1, int* arr2, int size1, int size2) {
    cout << "      ";
    for (int j = 0; j < size2; j++) {
        if (arr2[j] < 10) {
            cout << "0";
        }
        cout << arr2[j] << " ";
    }
    cout << "\n";
    for (int i = 0; i <= size1; i++) {
        if (i == 0) {
            cout << "   ";
        }
        else {
            if (arr1[i-1] < 10) {
                cout << "0";
            }
            cout << arr1[i-1] << " ";
        }
        for (int j = 0; j <= size2; j++) {
            if (arr[i][j] < 10) {
                cout << "0";
            }
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
}
void print_double_array2(int** arr, int* arr1, int* arr2, int size1, int size2) {
    cout << "      ";
    for (int j = 0; j < size2; j++) {
        if (arr2[j] < 10) {
            cout << "0";
        }
        cout << arr2[j] << " ";
    }
    cout << "\n";
    for (int i = 0; i <= size1; i++) {
        if (i == 0) {
            cout << "   ";
        }
        else {
            if (arr1[i-1] < 10) {
                cout << "0";
            }
            cout << arr1[i-1] << " ";
        }
        for (int j = 0; j <= size2; j++) {
            if (arr[i][j] == 1) {
                cout << "^- ";
            }
            else if (arr[i][j] == 2) {
                cout << "^^ ";
            }
            else {
                cout << "<- ";
            }
        }
        cout << "\n";
    }
}
void lcs_length(int* array1,int  size1, int* array2, int size2, int** c, int** b) {
    for (int i =0; i <= size1; i++) {
        assign(c[i], 0);
    }
    for (int i =0; i <= size2; i++) {
        assign(c[0]+i, 0);
    }
    for (int i = 1; i <= size1; i++) {
        for (int j = 1; j <= size2; j++) {
            if (array1[i-1] == array2[j-1]) {
                compare_count++;
                //c[i][j]  = c[i-1][j-1] + 1;
                assign(c[i]+j, c[i-1][j-1] + 1);
                //b[i][j] = 1;
                assign(b[i]+j, 1);
            }
            else if (is_greater(c[i-1][j], c[i][j-1])) {
                //c[i][j] = c[i-1][j];
                assign(c[i]+j, c[i-1][j]);
                //b[i][j] = 2;
                assign(b[i]+j, 2);
            }
            else {
                assign(c[i]+j, c[i][j-1]);
                //c[i][j] = c[i][j-1];
                //b[i][j] = 3;
                assign(b[i]+j, 3);
            }
        }
        if (less_than_fifty) {
            cout << "Tablica c:\n";
            print_double_array(c, array1, array2, size1,size2);
            cout << "Tablica b:\n";
            print_double_array2(b, array1, array2, size1,size2);
        }
    }

}
void print_lcs(int** b, int* array1, int i, int j) {
    if (i == 0 || j == 0) {
        return;
    }
    if (b[i][j] == 1) {
        print_lcs(b,array1,i-1,j-1);
        cout << array1[i-1] << ", ";
    }
    else if (b[i][j] == 2) {
        print_lcs(b,array1,i-1,j);
    }
    else {
        print_lcs(b,array1, i, j-1);
    }
}




int main(int argc, char *argv[]) {

    compare_count = 0;
    assign_count = 0;
    int size1, size2;
    int* array1, * array2;
    int** c, **b;
    
    cin >> size1;
    cin >> size2;
    array1 = new int[size1];
    for (int i = 0; i < size1; i++) {
        cin >> array1[i];
    }
    array2 = new int[size2];
    for (int i = 0; i < size2; i++) {
        cin >> array2[i];
    }
    c = new int*[size1+1];
    for (int i = 0; i <= size1; i++) {
        c[i] = new int[size2+1];
    }
    b = new int*[size1+1];
    for (int i = 0; i <= size1; i++) {
        b[i] = new int[size2+1];
    }
    less_than_fifty = false;
    if (size1 < 50 && size2 < 50) {
        less_than_fifty = true;
        cout << "Ciag 1:  ";
        print_array(array1,size1);
        cout << "Ciag 2:  ";
        print_array(array2,size2);
    }
    lcs_length(array1,size1,array2,size2,c,b);
    cout << "LCS: ";
    print_lcs(b,array1,size1,size2);
    cout << "\n";
    

    cout << "Liczba porownan miedzy kluczami: " << compare_count << "\n";
    cout << "Liczba przypisan wartosci: " << assign_count << "\n";
    //cout << "Czy tablica posortowana: " << is_sorted(array,size) << "\n";
    return 0;
}