#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <list>
#include <random>
#include <vector>

using namespace std;

mt19937 rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
// const int fastio = []() {ios_base::sync_with_stdio(false); cin.tie(0); return 0; }();

template <typename T>
class DynamicBinarySearchArray {
private:
  list<vector<T>> data;
  size_t size;

  void merge(const vector<T> &x, vector<T> &y) const {
    y.reserve(y.size() << 1);

    typename vector<T>::const_iterator first1 = x.begin();
    typename vector<T>::iterator first2 = y.begin();
    for (; first1 != x.end() && first2 != y.end(); ++first2)
      if (*first1 <= *first2)
        y.insert(first2, *first1++);

    y.insert(first2, first1, x.end());
  }

public:
  DynamicBinarySearchArray<T>() : size(0) {}

  void insert(const T &val) {
    typename list<vector<T>>::iterator prev_it = data.insert(data.begin(), vector<T>{val});
    typename list<vector<T>>::iterator now_it = next(prev_it);

    while (now_it != data.end())
      if (prev_it->size() == now_it->size()) {
        merge(*prev_it, *now_it);
        data.erase(prev_it);
      } else {
        prev_it = now_it;
        now_it = next(now_it);
      }

    ++size;
  }

  template <typename... Args>
  void insert(T first, Args... val) { insert(first), insert(val...); }

  pair<int, int> search(const T &val) const {
    for (const vector<T> &sub_arr : data) {
      typename vector<T>::const_iterator found = lower_bound(sub_arr.begin(), sub_arr.end(), val);
      if (*found == val)
        return {sub_arr.size(), found - sub_arr.begin()};
    }

    return {-1, -1};
  }

  void print() {
    typename list<vector<T>>::iterator now = data.begin();
    if (now == data.end())
      cout << "Empty!\n";
    else
      for (int w = 1; w <= size; w <<= 1)
        if (now->size() == w) {
          cout << w << ": { ";

          for (int w1 = 0; w1 < w; ++w1)
            cout << (*now)[w1] << (w1 + 1 == w ? " " : ", ");

          cout << "}\n";
          ++now;
        } else
          cout << w << ": { }\n";
  }
};

int main() {
  DynamicBinarySearchArray<int> bsa;
  cout <<
      R"(Dynamic Binary Search Operation:
  (1) Insert
  (2) Insert n random number
  (3) Search
  (4) Print
  (5) Reset
  (6) Exit

)";

  int inp;
  bool status = true;
  string line;
  while (status) {
    cout << "Input a operation: ";
    if (!(cin >> inp) || inp == 6)
      break;

    switch (inp) {
      case 1:
        cout << "Input a integer: ";
        cin >> inp;
        bsa.insert(inp);
        bsa.print();
        break;
      case 2:
        cout << "Input count n: ";
        cin >> inp;
        while (inp--)
          bsa.insert((rng() % 1000) - 500);
        bsa.print();
        break;
      case 3: {
        cout << "Input a integer: ";
        cin >> inp;
        pair<int, int> result = bsa.search(inp);
        if (result.first == -1 || result.second == -1)
          cout << "Not found.\n";
        else
          cout << '[' << result.first << ']'
               << '[' << result.second << "]\n";
        break;
      }
      case 4:
        bsa.print();
        break;
      case 5:
        bsa = DynamicBinarySearchArray<int>();
        break;
      case 6:
        status = false;
        break;
      default:
        cout << "Undefined operation.\n";
    }
  }

  return 0;
}