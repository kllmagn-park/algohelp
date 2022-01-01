#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

template <class T>
struct comparator {
    int operator()(const T& val1, const T& val2) {
        if (val1 < val2) return 1;
        else if (val1 > val2) return -1;
        return 0;
    }
};

template <class T, class TComp = comparator<T>>
class avl_tree {
private:

    struct Node {
        T key;
        uint8_t h;
        int size;
        Node* left;
        Node* right;
        Node(T key_) : key(key_), h(1), size(1), left(NULL), right(NULL) {}
    };

    Node* tree;

    TComp comp;

    uint8_t h(Node* node) {
        if (!node) return 0;
        return node->h;
    }

    int size(Node* node) {
        if (!node) return 0;
        return node->size;
    }

    uint8_t bfactor(Node* node) {return h(node->right) - h(node->left);}

    Node* balance(Node* node) {
        set_height(node); set_size(node);
        int balance_factor = bfactor(node);
        if (balance_factor == 2) {
            if (bfactor(node->right) < 0) node->right = rot_right(node->right);
            return rot_left(node);
        }
        if (balance_factor == -2) {
            if (bfactor(node->left) > 0) node->left = rot_left(node->left);
            return rot_right(node);
        }
        return node;
    }

    Node* rot_left(Node* y) {
        Node* x = y->right;
        y->right = x->left;
        x->left = y;
        set_height(y); set_height(x);
        set_size(y); set_size(x);
        return x;
    }

    Node* rot_right(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        set_height(y); set_height(x);
        set_size(y); set_size(x);
        return x;
    }

    Node* replace_right(Node* node) {
        if (!node->left) return node->right;
        node->left = replace_right(node->left);
        return balance(node);
    }

    void set_size(Node* node) {
        int lsize = size(node->left);
        int rsize = size(node->right);
        node->size = 1 + lsize + rsize;
    }

    void set_height(Node* node) {
        if (!node) return;
        node->h = std::max(h(node->left), h(node->right)) + 1;
    }

    Node* insert_(Node* node, T key) {
        if (!node) return new Node(key);
        if (comp(node->key, key) > 0) node->right = insert_(node->right, key);
        else node->left = insert_(node->left, key);
        return balance(node);
    }

    Node* remove_(Node* node, T key) {
        if (!node) return NULL;
        if (comp(node->key, key) > 0) node->right = remove_(node->right, key);
        else if (comp(node->key, key) < 0) node->left = remove_(node->left, key);
        else {
            Node* left = node->left;
            Node* right = node->right;
            delete node;
            if (!right) return left;
            Node* min = find_min(right);
            min->right = replace_right(right);
            min->left = left;
            return balance(min);
        }
        return balance(node);
    }

    Node* find_min(Node* node) {
        if (node->left) return find_min(node->left);
        return node;
    }

public:
    avl_tree(TComp comp = TComp()) : tree(NULL), comp(comp) {}
    ~avl_tree() {delete tree;}

    void insert(const T& key) {tree = insert_(tree, key);}
    void remove(const T& key) {tree = remove_(tree, key);}

    T get_k(int key) {
        Node* node = tree;
        while (key != size(node->left)) {
            if (size(node->left) >= key) node = node->left;
            if (size(node->left) < key) {
                key -= size(node->left) + 1;
                node = node->right;
            }
        }
        return node->key;
    }
};

int main() {
    comparator<int> comp;
    avl_tree<int> tree(comp);
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        int key = 0;
        int k = 0;
        cin >> key >> k;
        if (key <= 0) tree.remove(-key);
        else tree.insert(key);
        cout << tree.get_k(k) << endl;
    }
    return 0;
}