#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

using namespace std;

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

  bool search(const T &val) const {
    return find_if(data.begin(), data.end(), [&val](const vector<T> &sub_arr) { return *lower_bound(sub_arr.begin(), sub_arr.end(), val) == val; }) != data.end();
  }

  void print() { cout << *this; }

  friend ostream &operator<<(std::ostream &stream, const DynamicBinarySearchArray<T> &bsa) {
    vector<T> result;
    result.reserve(bsa.size);
    for (const vector<T> &x : bsa.data)
      bsa.merge(x, result);

    cout << "{ ";
    for (int w = 0; w < result.size(); ++w)
      cout << result[w] << (w + 1 == result.size() ? " " : ", ");

    cout << "}";

    return stream;
  }
};

int main() {
  DynamicBinarySearchArray<short> bsa;
  bsa.insert(434, 91, 906, 36, 683, -741, 268, 189, -197, 225, 547, 759, -619);
  bsa.insert(-459, -391, 451, 183, -402, -822, -562, 542, 684, 727, -730, -180);
  bsa.insert(-191, -293, 61, 86, -667, 294, -76, -431, 202, -850, 696, -263, 861);
  bsa.insert(-888, -439, 213, -10, -262, 404, -997, -392, 390, 727, -131, 232);
  bsa.insert(-979, 312, 327, 329, 24, -91, -335, 692, 734, -234, 39, -675, 282);
  bsa.insert(-505, -966, 82, 211, -930, 779, 365, -937, -539, 601, 454, -693);
  bsa.insert(-616, 503, 603, -581, -790, -739, 263, 236, 663, 949, -476, -91);
  bsa.insert(-825, 303, -596, 552, -807, 910, -200, -107, 654, -778, 425, 59);
  bsa.insert(-709, 754, -772, 36, 613, -734, -1023, 633, 730, 916, 938, -492, 317);
  bsa.insert(-864, 849, 573, 689, 890, 802, 233, 758, -868, -185, -627, -533, 124);
  bsa.insert(-300, -309, -872, -86, -898, 1010, -335, 179, -155, -822, 1021, -52);
  bsa.insert(-165, -688, 553, 303, -56, -954, 828, -289, 595, 560, -340, -1019);
  bsa.insert(-494, 652, 938, 216, 924, -792, 372, -327, -581, -499, 91, -524);
  bsa.insert(756, 16, 5, -558, 249, 457, -171, 919, 246, -838, -767, -57);
  bsa.insert(-233, 790, -736, 676, -576, 666, 671, -982, 720, -93, 582, -648);
  bsa.insert(-125, 796, -759, -75, -128, 275, -833, 107, 1018, 157, -931, -427);
  bsa.insert(300, -594, -997, -987, -719, 542, -823, -75, -52, 219, 329, -700);
  bsa.insert(175, -125, -901, 343, 126, -505, 458, -729, 872, 238, -530, 164);
  bsa.insert(747, 400, -848, 192, -893, 23, 183, 766, -234, -253, -154, -239);
  bsa.insert(-121, -906, 961, 496, 69, -322, 27, 1017, -693, 740, -211, 498, -192);
  bsa.insert(-740, -473, 354, -847, 234, -496, 428, -147, 357, 459, -783, 551);
  bsa.insert(-653, 631, 890, -710, -227, -733, 710, -114, -870, -35, 728, 721, 976, -280);
  bsa.insert(287, 319, 21, -136, -39, -288, -891, 995, -170, -258, 906, 600, 237, -25, 213);
  bsa.insert(-802, 737, 209, 216, -1023, 948, -110, 1017, -900, -30, 576, 615, -136, 579);
  bsa.insert(924, 919, -667, -676, 104, -380, 187, -311, 32, -55, -26, -750, 464, 849, 859);
  bsa.insert(197, 629, 841, 382, 856, 765, 59, -469, -872, 242, 389, 254, 905, -661, -413);
  bsa.insert(823, -174, -302, -91, -469, -762, -517, -879, -781, -944, -586, 121, -435);
  bsa.insert(-311, -310, 952, -943, -245, -341, 1003, 592, -871, -422, -443, 901, 384, -116);
  bsa.insert(428, -610, -223, 150, 988, -118, 793, -527, -40, -761, 502, 611, 124, 748, 886);
  bsa.insert(296, 914, -425, 1018, -184, -208, 22, 608, -7, -85, 672, 17, -773, -82, -22);
  bsa.insert(-858, -74, -130, -379, -630, 882, 166, -947, -78, -627, -446, -700, -976, 588);
  bsa.insert(244, -778, 468, 587, 405, -932, 445, 677, 768, -270, -108, -437, 323, -547);
  bsa.insert(-542, 257, -895, -333, 373, -383, 755, -51, 976, 775, 907, -152, -843, 431);
  bsa.insert(-773, 193, 752, 12, -890, -961, 805, 801, -362, -617, -523, -595, -855, -256);
  bsa.insert(-220, 666, 1021, -768, -96, -349, 104, 416, 500, 1012, 279, 383, 796, -983);
  bsa.insert(-136, -324, 780, -843, -825, 924, -832, 228, 507, -488, 138, -232, -597, -54);
  bsa.insert(395, 781, -177, 142, 732, 689, -850, -808, -662, -258, -326, -756, -619, 56);
  bsa.insert(484, -810, 702, 566, -706, -450, 167, -856, 888, 457, 956, -446, -822, -241);
  bsa.insert(798, 528, 300, -398, 738, -500, -219, -885, -433, -901, 746);

  cout << boolalpha << "434: " << bsa.search(434) << ", -1 " << bsa.search(-1) << endl;
  cout << bsa << endl;

  return 0;
}