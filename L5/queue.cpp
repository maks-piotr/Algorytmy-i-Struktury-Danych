#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

int assign_count, compare_count;
bool less_than_fifty;
int heap_size=0;
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

void heapify(int *arr, int i)
{
    int l = left(i);
    int r = right(i);
    int largest = i;
    if (l < heap_size && is_greater(arr[l], arr[i])) {
        largest = l;
    }
    if (r < heap_size && is_greater(arr[r], arr[largest])) {
        largest = r;
    }
    if (largest != i) {
        int tmp = arr[i];
        assign(arr+i,arr[largest]);
        assign(arr+largest,tmp);
        heapify(arr, largest);
    }
}
void build_heap(int *arr, int n) {
    heap_size = n;
    for (int i = n/2 -1; i >= 0; i--) {
        heapify(arr,i);
    }
}
void heap_sort(int* arr, int n) {
    build_heap(arr,n);
    //print_array(arr,n);
    for (int i = n-1; i > 0; i--) {
        int tmp = arr[0];
        assign(arr,arr[i]);
        assign(arr+i,tmp);
        heap_size--;
        heapify(arr,0);
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
int heap_extract_max(int* arr) {
    if (heap_size < 1) {
        cerr << "kopiec pusty";
    }
    int maximum = arr[0];
    assign(arr,arr[heap_size-1]);
    arr[0] = arr[heap_size-1];
    heap_size--;
    heapify(arr,0);
    return maximum;
}
void heap_insert(int* arr, int key) {
    heap_size++;
    int i = heap_size-1;
    while (i > 0 && is_greater(key,arr[parent(i)])) {
        assign(arr+i,arr[parent(i)]);
        i = parent(i);
    }
    assign(arr+i,key);
    //print_array(arr,heap_size);
}
void print_branches_sub(int* arr, int n, int depth,char prefix, char* l_t, char* r_t){
        //cout << n << " " << heap_size << "\n" << flush;
        if( n >= heap_size ) return;
        if( left(n) < heap_size ){
            print_branches_sub(arr, left(n), depth+1, '/', l_t, r_t);
        }
        
        if(prefix == '/') l_t[depth-1]='|';
        if(prefix == '\\') r_t[depth-1]=' ';
        if( depth==0) printf("-");
        if( depth>0) printf(" ");
        for(int i=0; i<depth-1; i++)
            if( l_t[i]== '|' || r_t[i]=='|' ) {
            printf("| ");
            } else {
            printf("  ");
            }
        if( depth>0 ) printf("%c-", prefix);
        //cout << n << "\n" << flush;
        printf("[%d]\n", arr[n]);
        l_t[depth]=' ';
        if( right(n) < heap_size ){
            r_t[depth]='|';
            print_branches_sub(arr, right(n), depth+1, '\\', l_t, r_t);
        }
    }
void print_branches(int* arr, int s) {
        // init traces
        char* left_trace= (char*)malloc( s*sizeof(char) );
        char* right_trace= (char*)malloc( s*sizeof(char) );
        for(int i=0; i<=s; i++){
            left_trace[i]=' ';
            left_trace[i]=' ';
        }
        print_branches_sub(arr,0,0,'-',left_trace,right_trace);
        free(left_trace);
        free(right_trace);
    }
    
int main()
{
    compare_count = 0; assign_count = 0;
    int max_porownania = 0; int max_podstawienia = 0;
    double avg_porownania = 0; double avg_podstawienia = 0;
    int s;
    std::random_device rd;
    std::mt19937 g(rd());
    vector<int> keys;
    
    cin >> s;
    int* arr = new int[s];
    auto start = chrono::steady_clock::now();
    for (int i = 0; i < s; i++) {
        //cout << "insert " << i << "\n";
        int x;
        cin >> x;
        heap_insert(arr,x);
        if (s <= 50) {
            cout << i+1 << ", insert " << x << "\n";
        }
        max_porownania = max(max_porownania,compare_count);
        max_podstawienia = max(max_podstawienia, assign_count);
        avg_podstawienia += double(assign_count)/(2*s);
        avg_porownania += double(compare_count)/(2*s);
        assign_count = 0; compare_count = 0;
        if (s <= 50) {
            print_branches(arr,s);
            cout << "\n";
        }
        keys.push_back(x);
    }

    auto end = chrono::steady_clock::now();
    cout << "Czas insert w sekundach: "
    << chrono::duration_cast<chrono::seconds>(end - start).count() << "\n";
    start = chrono::steady_clock::now();
    //heap_extract_max(arr);
    assign_count = 0; compare_count = 0;
    for (int i = 0; i < s; i++) {
        //cout << "delete " << i << "\n";
        int x = heap_extract_max(arr);
        if (s <= 50) {
            cout << i+1 << ", extract " << x << "\n";
        }
        max_porownania = max(max_porownania,compare_count);
        max_podstawienia = max(max_podstawienia, assign_count);
        avg_podstawienia += double(assign_count)/(2*s);
        avg_porownania += double(compare_count)/(2*s);
        assign_count = 0; compare_count = 0;
        if (s <= 50) {
            print_branches(arr,s);
            cout << "\n";
        }
        keys.push_back(x);
    }
    end = chrono::steady_clock::now();
    cout << "Czas delete w sekundach: "
    << chrono::duration_cast<chrono::seconds>(end - start).count() << "\n";
    cout << "Srednia porowania: " << avg_porownania << "\n";
    cout << "Srednia podstawienia: " << avg_podstawienia << "\n";
    cout << "Max porownan: " << max_porownania << "\n";
    cout << "Max podstwaienia: " << max_podstawienia << "\n";
    return 0;
}
 