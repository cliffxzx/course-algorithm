#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
class Expression {
private:
  using MinMax = pair<T, T>;
  using MinMaxInterval = vector<vector<MinMax>>;

  class Path {
  public:
    int val;
    bool left, right;
  };
  class MinMaxPath {
  public:
    Path min, max;
  };
  using MinMaxIntervalPath = vector<vector<MinMaxPath>>;

  vector<T> operands;
  vector<char> operators;

  const T calc(const T &x, const char op, const T &y) const {
    if (op == '+')
      return x + y;
    else if (op == '-')
      return x - y;
    else if (op == '*')
      return x * y;

    throw std::invalid_argument("op is undefined");
  }

  // calculate maximun and minimun value.
  pair<MinMax, tuple<bool, bool, bool, bool>> calc(const MinMax &x, const char op, const MinMax &y) const {
    const auto vals = {calc(x.first, op, y.first), calc(x.first, op, y.second), calc(x.second, op, y.first), calc(x.second, op, y.second)};
    const auto minmax_val = std::minmax_element(vals.begin(), vals.end());

    return {
        {*minmax_val.first, *minmax_val.second},
        {
            minmax_val.first - vals.begin() < 2,
            minmax_val.first - vals.begin() >= 2,
            minmax_val.second - vals.begin() < 2,
            minmax_val.second - vals.begin() >= 2,
        },
    };
  }

  const pair<MinMaxInterval, MinMaxIntervalPath> minmax_info() const {
    MinMaxInterval interval(operands.size(), vector<MinMax>(operands.size()));
    MinMaxIntervalPath from(operators.size(), vector<MinMaxPath>(operators.size()));

    for (int w = 0; w < operands.size(); ++w)
      interval[w][w].first = interval[w][w].second = operands[w];

    for (int w = 1; w <= operators.size(); ++w)
      for (int w1 = 0; w1 <= operators.size() - w; ++w1) {
        // w1: row, idx: col 目前要算最大值的位置。
        int idx = w + w1;

        // 先做 1 個，避免最大值為負時沒更新。
        interval[w1][idx] = calc(interval[w1][w1], operators[w1], interval[w1 + 1][idx]).first;
        from[w1][idx - 1] = {{w1, false, false}, {w1, false, false}};

        for (int w2 = w1 + 1; w2 < idx; ++w2) {
          const pair<MinMax, tuple<bool, bool, bool, bool>> val = calc(interval[w1][w2], operators[w2], interval[w2 + 1][idx]);
          if (val.first.first < interval[w1][idx].first) {
            interval[w1][idx].first = val.first.first;
            from[w1][idx - 1].min = {w2, get<0>(val.second), get<1>(val.second)};
          }

          if (val.first.second > interval[w1][idx].second) {
            interval[w1][idx].second = val.first.second;
            from[w1][idx - 1].max = {w2, get<2>(val.second), get<3>(val.second)};
          }
        }
      }

    return {interval, from};
  }

public:
  Expression(string expression) {
    operands.reserve(expression.size() / 2 + 1);
    operators.reserve(expression.size() / 2);

    stringstream ss(expression);
    T val;
    char op;
    while (ss >> val) {
      operands.emplace_back(val);

      if (ss >> op)
        operators.emplace_back(op);
      else
        break;
    }
  }

  void maximun_expression_recursive(const MinMaxIntervalPath &from, string &now, int start, int end, bool direct) const {
    if (start > end)
      return;

    string result;
    Path root = direct ? from[start][end].max : from[start][end].min;

    now += "(";
    maximun_expression_recursive(from, now, start, root.val - 1, root.left);
    if (now.back() == '(')
      now += to_string(operands[root.val]);

    now += operators[root.val];
    maximun_expression_recursive(from, now, root.val + 1, end, root.right);
    if (now.back() != ')')
      now += to_string(operands[root.val + 1]);
    now += ")";
    // if (start == end)
    //   now += to_string(operands[root.val + 1]);
  }

  // I give up. I don't have time to implement.
  string maximum_expression() const {
    MinMaxInterval interval;
    MinMaxIntervalPath from;

    tie(interval, from) = minmax_info();
    string result;
    maximun_expression_recursive(from, result, 0, from.front().size() - 1, true);
    vector<string> stk(result.size());
    return result;
  }
};

int main() {
  auto istmp = istringstream("5-8+7*4-8+9\n-11+22--11-22\n2-7*5+1-4+8*3\n");
  cin.rdbuf(istmp.rdbuf());

  string line;
  while (getline(cin, line))
    cout << Expression<int>(line).maximum_expression() << '\n';

  return 0;
}