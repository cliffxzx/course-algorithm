#include <iostream>
#include <vector>

using namespace std;

struct Item {
  int weight;
  double value;
};

double solve(int K, int n, const vector<Item> &items) {
  vector<double> knapsacks(K + 1);
  for (int w = 0; w < n; ++w) {
    for (int w1 = K; w1 > items[w].weight; --w1)
      if (knapsacks[w1 - items[w].weight])
        knapsacks[w1] = max(knapsacks[w1], knapsacks[w1 - items[w].weight] + items[w].value);

    knapsacks[items[w].weight] = max(knapsacks[items[w].weight], items[w].value);
  }

  return knapsacks[K];
}

int main() {
  vector<Item> items = {{1, 2}, {3, .5}, {2, 1}, {8, 4}, {7, 1.5}, {4, 2.5}, {2, .5}};
  cout << solve(10, 7, items) << '\n';

  return 0;
}
