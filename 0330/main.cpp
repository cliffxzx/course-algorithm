#include <algorithm>
#include <iostream>

using namespace std;

int cut_rod(int price[], int n) {
  int *dp = new int[n + 1]{};
  int *from = new int[n + 1]{};

  for (int w = 1; w <= n; ++w)
    for (int w1 = 0; w1 < w; ++w1)
      if (dp[w - w1 - 1] + price[w1] > dp[w])
        dp[w] = dp[from[w] = w - w1 - 1] + price[w1];

  while (n) {
    cout << n - from[n] << " ";
    n = from[n];
  }

  cout << "\n";

  int result = dp[n];
  delete[] dp;
  delete[] from;
  return result;
}

int main() {
  // int price[] = {1, 5, 8, 9, 10, 17, 17, 20};
  int price[] = {3, 5, 8, 9, 10, 17, 17, 20};
  cout << cut_rod(price, 8) << endl;
  price[0] = 3;
  cout << cut_rod(price, 1) << endl;
}