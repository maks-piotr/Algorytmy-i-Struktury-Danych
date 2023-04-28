#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;

int odczyty_podstawienia;
int porownania;

class Node {
    private:
    Node *left;
    Node *right;
    Node *parent;
    
    public:
    int value;
    Node* get_left() {
        odczyty_podstawienia++;
        return left;
    }
    Node* get_right() {
        odczyty_podstawienia++;
        return right;
    }
    Node* get_parent() {
        odczyty_podstawienia++;
        return parent;
    }
    void set_left(Node* n) {
        odczyty_podstawienia++;
        left = n;
    }
    void set_right(Node* n) {
        odczyty_podstawienia++;
        right = n;
    }
    void set_parent(Node* n) {
        odczyty_podstawienia++;
        parent = n;
    }

    Node(int val) {
        left = nullptr;
        right = nullptr;
        value = val;
    }
    
};

class SplayTree {
    Node *root;
    void inorder_sub(Node* n)
    {
        if (n == nullptr) {
            return;
        }
        inorder_sub(n->get_left());
        cout << n->value << endl;
        inorder_sub(n->get_right());
    }
    bool compare(int a, int b) {
        porownania++;
        if (a > b) {
            return true;
        }
        return false;
    }
    
    Node* minimum(Node* n)
    {
        Node* temp = n;
    
        while (temp->get_left() != nullptr)
            temp = temp->get_left();
    
        return temp;
    }
    Node* successor(Node* n) {
        if (n->get_right() != nullptr) {
            return minimum(n->get_right());
        }
        Node* y = n->get_parent();
        while(y != nullptr && n == y->get_right()) {
            n = y;
            y = y->get_parent();
        }
        return y;
    }
    int height_sub(Node* n)
    {
        if (n == nullptr)
            return -1;
        else
        {
            int left_height = height_sub(n->get_left());
            int right_height = height_sub(n->get_right());
        
            if (left_height > right_height)
                return(left_height + 1);
            else return(right_height + 1);
        }
    }
    void print_branches_sub( Node* n, int depth,char prefix, char* l_t, char* r_t){
        if( n == nullptr ) return;
        if( n->get_left() != nullptr ){
            print_branches_sub(n->get_left(), depth+1, '/', l_t, r_t);
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
        printf("[%d]\n", n->value);
        l_t[depth]=' ';
        if( n->get_right() != NULL ){
            r_t[depth]='|';
            print_branches_sub(n->get_right(), depth+1, '\\', l_t, r_t);
        }
    }
    void left_rotate(Node *x) {
        Node *y = x->get_right();
        if (y) {
            x->set_right(y->get_left());
            if (y->get_left()) y->get_left()->set_parent(x);
            y->set_parent(x->get_parent());
        }

        if (!x->get_parent()) { 
            root = y;
        }
        else if (x == x->get_parent()->get_left()) { 
            x->get_parent()->set_left(y);
        }
        else  {
            x->get_parent()->set_right(y);
        }
        if (y) {
            y->set_left(x);
        }
        x->set_parent(y);
    }
  
    void right_rotate(Node *x) {
        Node *y = x->get_left();
        if (y) {
            x->set_left(y->get_right());
            if (y->get_right()) y->get_right()->set_parent(x);
            y->set_parent(x->get_parent());
        }
        if (!x->get_parent()) {
            root = y;
        } 
        else if (x == x->get_parent()->get_left()) {
            x->get_parent()->set_left(y);
        }
        else {
            x->get_parent()->set_right(y);
        }
        if (y) {
            y->set_right(x);
        }
        x->set_parent(y);
    }
    void splay(Node* n) {
        while (n->get_parent() != nullptr) {
            if (root->get_left() == n) {
                right_rotate(root);
            }
            else if (root->get_right() == n) {
                left_rotate(root);
            }
            else if (n->get_parent()->get_left() == n && n->get_parent()->get_parent()->get_left() == n->get_parent()) {
                right_rotate(n->get_parent()->get_parent());
                right_rotate(n->get_parent());
            }
            else if (n->get_parent()->get_right() == n && n->get_parent()->get_parent()->get_right() == n->get_parent()) {
                left_rotate(n->get_parent()->get_parent());
                left_rotate(n->get_parent());
            }
            else if (n->get_parent()->get_left() == n && n->get_parent()->get_parent()->get_right() == n->get_parent()) {
                right_rotate(n->get_parent());
                left_rotate(n->get_parent());
            }
            else if (n->get_parent()->get_right() == n && n->get_parent()->get_parent()->get_left() == n->get_parent()) {
                left_rotate(n->get_parent());
                right_rotate(n->get_parent());
            }
        }
    }
    public:
    SplayTree() {
        root = nullptr;
    }
    Node* search(Node* n, int key)
    {
        if (n == NULL || n->value == key)
            return n;

        if (compare(key, n->value)) {
            return search(n->get_right(), key);
        }

        return search(n->get_left(), key);
    }
 
    void inorder() {
        inorder_sub(root);
    }
    void insert(int key) {
        Node* y = nullptr;
        Node* x = root;
        Node* new_node = new Node(key);
        while (x != nullptr) {
            y = x;
            if (compare(x->value, key)) {
                x = x->get_left();
            }
            else {
                x = x->get_right();
            }
        }
        new_node->set_parent(y);
        if (y == nullptr) {
            root = new_node;
        }
        else if (compare(y->value,key)) {
            y->set_left(new_node);
        }
        else {
            y->set_right(new_node);
        }
        splay(new_node);
    }
    void delete_val(int v) {
        Node* z = search(root,v);

        if (z == nullptr) {
            return;
        }
        

        Node* x;
        Node* y;
        if (z->get_left() == nullptr || z->get_right() == nullptr) {
            y = z;
        }
        else {
            y = successor(z);
        }
        if (y->get_left() != nullptr) {
            x = y->get_left();
        }
        else {
            x = y->get_right();
        }
        if (x != nullptr) {
            x->set_parent(y->get_parent());
        }
        if (y->get_parent() == nullptr) {
            root = x;
        }
        else if (y == y->get_parent()->get_left()) {
            y->get_parent()->set_left(x);
        }
        else {
            y->get_parent()->set_right(x);
        }
        if (y != z) {
            z->value = y->value;
        }
        if (y->get_parent() != nullptr) {
            splay(y->get_parent());
        }
        delete y;
    }
    int height() {
        return height_sub(root);
    }
    
    void print_branches(int s) {
        // init traces
        char* left_trace= (char*)malloc( s*sizeof(char) );
        char* right_trace= (char*)malloc( s*sizeof(char) );
        for(int i=0; i<=s; i++){
            left_trace[i]=' ';
            left_trace[i]=' ';
        }
        print_branches_sub(root,0,'-',left_trace,right_trace);
        free(left_trace);
        free(right_trace);
    }
    
};

int main()
{
    int wysokosc = 0; porownania = 0; odczyty_podstawienia = 0;
    int max_wysokosc = 0; int max_porownania = 0; int max_odczyty_podstawienia = 0;
    double avg_wysokosc = 0; double avg_porownania = 0; double avg_odczyty_podstawienia = 0;
    SplayTree b;
    int s;
    std::random_device rd;
    std::mt19937 g(rd());
    vector<int> keys;
    cin >> s;
    auto start = chrono::steady_clock::now();
    for (int i = 0; i < s; i++) {
        //cout << "insert " << i << "\n";
        int x;
        cin >> x;
        b.insert(x);
        if (s <= 50) {
            cout << i << ", insert " << x << "\n";
            cout << "height: " << b.height() << "\n";
        }
        max_porownania = max(max_porownania,porownania);
        max_odczyty_podstawienia = max(max_odczyty_podstawienia, odczyty_podstawienia);
        avg_odczyty_podstawienia += double(odczyty_podstawienia)/(2*s);
        avg_porownania += double(porownania)/(2*s);
        wysokosc = b.height();
        max_wysokosc = max(max_wysokosc, b.height());
        avg_wysokosc += double(wysokosc)/(2*s);
        porownania = 0; odczyty_podstawienia = 0;
        if (s <= 50) {
            b.print_branches(s);
            cout << "\n";
        }
        keys.push_back(x);
    }

    auto end = chrono::steady_clock::now();
    cout << "Czas insert w sekundach: "
    << chrono::duration_cast<chrono::seconds>(end - start).count() << "\n";
    start = chrono::steady_clock::now();
    shuffle(keys.begin(),keys.end(), g);
    for (int i = 0; i < s; i++) {
        //cout << "delete " << i << "\n";
        b.delete_val(keys[i]);
        if (s <= 50) {
            cout << i << ", delete " << keys[i] << "\n";
            cout << "height: " << b.height() << "\n";
        }
        max_porownania = max(max_porownania,porownania);
        max_odczyty_podstawienia = max(max_odczyty_podstawienia, odczyty_podstawienia);
        avg_odczyty_podstawienia += double(odczyty_podstawienia)/(2*s);
        avg_porownania += double(porownania)/(2*s);
        wysokosc = b.height();
        max_wysokosc = max(max_wysokosc, b.height());
        avg_wysokosc += double(wysokosc)/(2*s);
        porownania = 0; odczyty_podstawienia = 0;
        if (s <= 50) {
            b.print_branches(s);
            cout << "\n";
        }
    }
    end = chrono::steady_clock::now();
    cout << "Czas delete w sekundach: "
    << chrono::duration_cast<chrono::seconds>(end - start).count() << "\n";
    cout << "Srednia wysokosc: " << avg_wysokosc << "\n";
    cout << "Srednia porowania: " << avg_porownania << "\n";
    cout << "Srednia odczyty, podstawienia: " << avg_odczyty_podstawienia << "\n";
    cout << "Max wysokosc: " << max_wysokosc << "\n";
    cout << "Max porownan: " << max_porownania << "\n";
    cout << "Max odczyty, porowania: " << max_odczyty_podstawienia << "\n";
    return 0;
}
 