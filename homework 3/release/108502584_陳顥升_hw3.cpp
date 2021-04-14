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

  inline const T calc(const T &x, const char op, const T &y) const {
    if (op == '+')
      return x + y;
    else if (op == '-')
      return x - y;
    else if (op == '*')
      return x * y;

    throw std::invalid_argument("op is undefined");
  }

  // calculate maximun and minimun value.
  inline MinMax calc(const MinMax &x, const char op, const MinMax &y) const {
    return minmax({calc(x.first, op, y.first),
                   calc(x.first, op, y.second),
                   calc(x.second, op, y.first),
                   calc(x.second, op, y.second)});
  }

  const void fill_minmax_interval() {
    for (int w = 0; w < operands.size(); ++w)
      minmax_interval[w][w].first = minmax_interval[w][w].second = operands[w];

    for (int w = 1; w <= operators.size(); ++w)
      for (int w1 = 0; w1 <= operators.size() - w; ++w1) {
        // w1: row, idx: col now position.
        int idx = w + w1;

        // do a operator, avoid maximun or minimun value didn't update.
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

  const string recursive_minmax_expression(const int x, const int y, const bool max_direct) const {
    if (x == y)
      return to_string(operands[x]);
    else if (x + 1 == y) {
      if (x < operators.size())
        return "(" + to_string(operands[x]) + operators[x] + to_string(operands[x + 1]) + ")";
      else
        return to_string(operands[x]);
    }

    const T now = max_direct ? minmax_interval[x][y].second : minmax_interval[x][y].first;
    for (int w2 = x; w2 <= y; ++w2) {
      const initializer_list<T> vals = {calc(minmax_interval[x][w2].first, operators[w2], minmax_interval[w2 + 1][y].first),
                                        calc(minmax_interval[x][w2].first, operators[w2], minmax_interval[w2 + 1][y].second),
                                        calc(minmax_interval[x][w2].second, operators[w2], minmax_interval[w2 + 1][y].first),
                                        calc(minmax_interval[x][w2].second, operators[w2], minmax_interval[w2 + 1][y].second)};
      const auto val = minmax_element(vals.begin(), vals.end());
      const int val_idx = max_direct ? val.second - vals.begin() : val.first - vals.begin();

      if (*val.first == now || *val.second == now)
        return (
            "(" +
            recursive_minmax_expression(x, w2, val_idx >= 2) +
            operators[w2] +
            recursive_minmax_expression(w2 + 1, y, val_idx & 1) +
            ")");
    }

    return "";
  }

public:
  Expression(const string &expression) {
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
    fill_minmax_interval();
  }

  const string minimum_expression() const { return recursive_minmax_expression(0, minmax_interval.front().size() - 1, false); }
  const string maximum_expression() const { return recursive_minmax_expression(0, minmax_interval.front().size() - 1, true); }
};

int main() {
  // auto test_data = istringstream("2+7*5-3*6\n5-8+7*4-8+9\n-11+22--11-22\n2-7*5+1-4+8*3\n1+1*1+1\n");
  // cin.rdbuf(test_data.rdbuf());

  string line;
  while (getline(cin, line))
    cout << Expression<int>(line).minimum_expression() << '\n';

  return 0;
}