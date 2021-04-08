#include <iostream>
#include <vector>

#define INF 0x3f3f3f3f

using namespace std;

int main() {
  int n = 8;
  vector<double> p{0, 0.04, 0.06, 0.08, 0.02, 0.10, 0.12, 0.14};
  vector<double> q{0.06, 0.06, 0.06, 0.06, 0.05, 0.05, 0.05, 0.05};
  // int n = 6;
  // vector<double> p{0, 0.15, 0.10, 0.05, 0.10, 0.20};
  // vector<double> q{0.05, 0.10, 0.05, 0.05, 0.05, 0.10};
  vector<vector<double>> pw(n + 1, vector<double>(n)), pe(n + 1, vector<double>(n, INF));
  vector<vector<int>> pr(n, vector<int>(n, INF));
  for (int w = 1; w <= n; ++w)
    for (int w1 = w - 1; w1 <= n; ++w1)
      if (w1 + 1 == w)
        pe[w][w1] = pw[w][w1] = q[w - 1];
      else
        pw[w][w1] = pw[w][w1 - 1] + p[w1] + q[w1];

  for (int l = 1; l < n; ++l)
    for (int i = 1; i < n - l + 1; ++i) {
      int j = i + l - 1;
      for (int r = i; r <= j; ++r) {
        double val = pe[i][r - 1] + pe[r + 1][j] + pw[i][j];
        if (val < pe[i][j]) {
          pe[i][j] = val;
          pr[i][j] = r;
        }
      }
    }

  return 0;
}