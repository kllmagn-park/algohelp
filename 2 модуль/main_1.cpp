#include <iostream>
#include <string>
#include <vector>

auto LF_MAX = 3./ 4.;
size_t A1 = 47; size_t A2 = 53;

using namespace std;

enum class states { ACTIVE, NONACTIVE, DELETED };

template <class TKey>
struct Node {
  TKey key;
  states state = states::NONACTIVE;
  Node() = default;
  Node(TKey &key_)  : key(key_), state(states::ACTIVE) {}
  ~Node() = default;
};

template <class TKey, class hash_func>
class hash_table {
 public:
  hash_table(hash_func h_func, size_t bsize = 8) 
      : table_(vector<Node<TKey>>(bsize)), h_func_(h_func), bsize_(bsize) {}

  hash_table &operator=(hash_table &&o) {
    if (this != &o) {
      table_ = move(o.table_);
      bsize_ = o.bsize_;
      size_ = o.size_;
      h_func_ = o.h_func_;
      exp_factor_ = o.exp_factor_;      
    }
    return *this;
  }

  bool insert(TKey &key) {
    if (size_ >= static_cast<size_t>(bsize_ * LF_MAX)) grow();
    auto elem = find_elem(key);
    if (elem.first) return false;
    if (table_[elem.second].state == states::NONACTIVE) ++size_;
    table_[elem.second] = Node<TKey>(key);
    return true;
  }

  bool remove(TKey &key)  {
    if (size_ == 0) return false;
    auto found = find(key);
    if (found.first) {
      table_[found.second].state = states::DELETED;
      return true;
    }
    return false;
  }

  bool exists(TKey &key)  { return find(key).first; }

  size_t size()  { return size_; }
  size_t bsize()  { return bsize_; }

 private:
  pair<bool, size_t> find(TKey &key)  {
    size_t h1 = get_hash(key, A1);
    size_t h2 = get_hash(key, A2) * 2 + 1;
    size_t h = h1 % bsize_;

    for (size_t i = 0; i < bsize_; ++i) {
      if (table_[h].key == key) return {table_[h].state == states::ACTIVE, h};
      else if (table_[h].state == states::NONACTIVE) return {false, h};
      h = (h + h2) % bsize_;
    }

    return {false, h};
  }

  pair<bool, size_t> find_elem(TKey &key)  {
    bool found = false;
    size_t h_del = 0;
    
    size_t h1 = get_hash(key, A1);
    size_t h2 = get_hash(key, A2) * 2 + 1;
    size_t h = h1 % bsize_;

    for (size_t i = 0; i < bsize_; ++i) {
      if (table_[h].state == states::NONACTIVE) break;
      else if (table_[h].state == states::DELETED && !found) {
        h_del = h;
        found = true;
      }
      else if (table_[h].key == key) break;
      h = (h + h2) % bsize_;
    }

    return {table_[h].state == states::ACTIVE, found ? h_del : h};
  }

  void grow() {
    hash_table new_table(h_func_, bsize_ * exp_factor_);
    for (auto &node : table_) if (node.state == states::ACTIVE) new_table.insert(node.key);
    *this = move(new_table);
  }

  size_t get_hash(TKey &key, size_t prime)  { return h_func_(key, prime); }

  vector<Node<TKey>> table_ = vector<Node<TKey>>(bsize_);
  size_t bsize_ = 8;
  size_t size_ = 0;
  hash_func h_func_;
  size_t exp_factor_ = 4;
};

size_t get_hash(string &s, size_t prime) {
  size_t h = 0;
  for (char c : s) h = h * prime + c;
  return h;
}

int main() {
  hash_table<string, decltype(&get_hash)> table(get_hash);

  string line;
  bool res;

  while (getline(cin, line) && !line.empty()) {
    string key = line.substr(2);
    switch (line[0]) {
      case '+':
        res = table.insert(key);
        break;
      case '-':
        res = table.remove(key);
        break;
      case '?':
        res = table.exists(key);
        break;
      default:
        return 0;
    }
    cout << (res ? "OK" : "FAIL") << endl;
  }
  return 0;
}
