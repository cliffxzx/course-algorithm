#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

void lengthOfLIS(vector<int> nums) {
  int *dp = new int[nums.size()]{}, *from = new int[nums.size()];
  pair<int, int> max_arr;

  fill(from, from + nums.size(), -1);

  for(int w = 0; w < nums.size(); ++w)
    for(int w1 = 0; w1 < w; ++w1)
      if (nums[w1] < nums[w] && dp[w] <= dp[w1]) {
        dp[w] = dp[w1] + 1;
        from[w] = w1;
        max_arr = max(max_arr, pair<int, int>{dp[w], w});
      }

  string result;
  while(max_arr.second != -1) {
    result = to_string(nums[max_arr.second]) + " " + result;
    max_arr.second = from[max_arr.second];
  }

  cout << result.substr(0, result.size() - 1) << '\n';

  delete[] dp;
  delete[] from;
}

int main() {
  lengthOfLIS(vector<int>{7,7,7,7,7});
  return 0;
}