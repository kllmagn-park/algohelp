#include <iostream>
#include <stack>
#include <functional>

using namespace std;

template <typename T>
struct Node {
  Node(T &key_) : key(key_) {}
  T key;
  Node *left = NULL;
  Node *right = NULL;
};

template <typename T, typename Less = less<T>>
class bin_tree {

private:
  Less comp_;
  Node<T> *root_ = NULL;

public:

  explicit bin_tree(Less comp = Less()) : comp_(comp) {}
  ~bin_tree() {handle_tree([](Node<T> *node) { delete node; node = NULL; });}

  void handle_tree(function<void(Node<T>*)> output_handler) {
    if (root_ == NULL) return;

    stack<Node<T> *> st1, st2;
    st1.push(root_);
    Node<T> *node;
    while (!st1.empty()) {
      node = st1.top();
      st1.pop();
      st2.push(node);
      if (node->left) st1.push(node->left);
      if (node->right) st1.push(node->right);
    }

    while (!st2.empty()) {
      node = st2.top();
      st2.pop();
      output_handler(node);
    }
  }

  void insert(T &key) {
    if (!root_) {
      root_ = new Node<T>(key);
      return;
    }

    Node<T> *node = root_;
    while (true) {
      if (comp_(key, node->key)) {
        if (node->left) node = node->left;
        else {
          node->left = new Node<T>(key);
          break;
        }
      }
      else {
        if (node->right) node = node->right;
        else {
          node->right = new Node<T>(key);
          break;
        }
      }
    }
  }
};

int main() {
  auto comp = [](int k1, int k2) { return k1 < k2; };
  bin_tree<int, decltype(comp)> tree(comp);
  int N = 0;
  cin >> N;
  int key = 0;
  for (int i = 0; i < N; i++) {
    cin >> key;
    tree.insert(key);
  }
  function<void(Node<int>*)> output_handler = [](Node<int>* node) { std::cout << node->key << " "; };
  tree.handle_tree(output_handler);
  return 0;
}