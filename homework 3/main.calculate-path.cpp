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

  vector<T> operands;
  vector<char> operators;
  MinMaxInterval minmax_interval;

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
  MinMax calc(const MinMax &x, const char op, const MinMax &y) const {
    return minmax({calc(x.first, op, y.first),
                   calc(x.first, op, y.second),
                   calc(x.second, op, y.first),
                   calc(x.second, op, y.second)});
  }

  void fill_minmax_info() {
    for (int w = 0; w < operands.size(); ++w)
      minmax_interval[w][w].first = minmax_interval[w][w].second = operands[w];

    for (int w = 1; w <= operators.size(); ++w)
      for (int w1 = 0; w1 <= operators.size() - w; ++w1) {
        // w1: row, idx: col 目前要算最大值的位置。
        int idx = w + w1;

        // 先做 1 個，避免最大值為負時沒更新。
        minmax_interval[w1][idx] = calc(minmax_interval[w1][w1], operators[w1], minmax_interval[w1 + 1][idx]);

        for (int w2 = w1 + 1; w2 < idx; ++w2) {
          const MinMax val = calc(minmax_interval[w1][w2], operators[w2], minmax_interval[w2 + 1][idx]);
          if (val.first < minmax_interval[w1][idx].first)
            minmax_interval[w1][idx].first = val.first;

          if (val.second > minmax_interval[w1][idx].second)
            minmax_interval[w1][idx].second = val.second;
        }
      }
  }

  string recursive_result(int x, int y, bool max_direct) {
    if (x == y)
      return to_string(operands[x]);
    else if (x + 1 == y) {
      if (x < operators.size())
        return "(" + to_string(operands[x]) + operators[x] + to_string(operands[x + 1]) + ")";
      else
        return to_string(operands[x]);
    }

    T now = max_direct ? minmax_interval[x][y].second : minmax_interval[x][y].first;
    for (int w2 = x; w2 <= y; ++w2) {
      const initializer_list<T> vals = {calc(minmax_interval[x][w2].first, operators[w2], minmax_interval[w2 + 1][y].first),
                                        calc(minmax_interval[x][w2].first, operators[w2], minmax_interval[w2 + 1][y].second),
                                        calc(minmax_interval[x][w2].second, operators[w2], minmax_interval[w2 + 1][y].first),
                                        calc(minmax_interval[x][w2].second, operators[w2], minmax_interval[w2 + 1][y].second)};
      const auto val = minmax_element(vals.begin(), vals.end());
      const pair<bool, bool> table[] = {{false, false}, {false, true}, {true, false}, {true, true}};
      const int val_idx = max_direct ? val.second - vals.begin() : val.first - vals.begin();

      if (*val.first == now || *val.second == now)
        return "(" + recursive_result(x, w2, table[val_idx].first) + operators[w2] + recursive_result(w2 + 1, y, table[val_idx].second) + ")";
    }

    return "";
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

    minmax_interval = MinMaxInterval(operands.size(), vector<MinMax>(operands.size()));
    fill_minmax_info();
  }

  // I give up. I don't have time to implement.
  string maximum_expression() {
    return recursive_result(0, minmax_interval.front().size() - 1, true);
  }
};

int main() {
  auto istmp = istringstream("2+7*5-3*6\n2-7*5+1-4+8*3\n5-8+7*4-8+9\n-11+22--11-22\n1+1*1+1\n");
  cin.rdbuf(istmp.rdbuf());

  string line;
  while (getline(cin, line))
    cout << Expression<int>(line).maximum_expression() << '\n';

  return 0;
}