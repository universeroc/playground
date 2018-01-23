
#include <array>
#include <cassert>

template<class T, size_t R, size_t C>
std::array<T, R*C> SpiralVisit(const std::array<std::array<T, C>, R>& a) {
  std::array<T, R*C> o;
  size_t oc = 0;
  for (int i = 0, j = 0; i < R / 2 + 1 && j < C / 2 + 1 && oc < R*C; i++, j++) {
    auto r = i, c = j;
    // Right
    for (; c < C - j; c++, oc++) {
      o[oc] = a[r][c];
    }

    --c;  // reset to good range
    ++r;
    // Down
    for (; r < R - i; r++, oc++) {
      o[oc] = a[r][c];
    }

    --c; // already visited
    --r;  // reset to good range
          // Left
    for (; c > j; --c, oc++) {
      o[oc] = a[r][c];
    }

    // Up
    for (; r > i; --r, oc++) {
      o[oc] = a[r][c];
    }
  }
  return o;
}

int main()
{
  std::array<std::array<int, 3>, 2> a1 = { {
    { { 1,2,3 } },
    { { 4,5,6 } }
    } };

  auto a1o = SpiralVisit<int, 2, 3>(a1);
  std::array<int, 6> a1oe = { 1,2,3,6,5,4 };
  assert(a1o == a1oe);

  std::array<std::array<int, 3>, 3> a2 = { {
    { { 1, 2, 3 } },
    { { 4, 5, 6 } },
    { { 7, 8, 9 } }
    } };
  std::array<int, 9> a2oe = { 1,2,3,6,9,8,7,4,5 };
  auto a2o = SpiralVisit<int, 3, 3>(a2);
  assert(a2o == a2oe);

  return 0;
}
