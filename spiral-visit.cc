#include <array>
#include <cassert>

// http://cpptruths.blogspot.com/2011/10/multi-dimensional-arrays-in-c11.html
template<class T, size_t R, size_t C>
using Mat2 = std::array<std::array<T, C>, R>;

template<class T, size_t L>
using Mat1 = std::array<T, L>;

template<class T, size_t R, size_t C>
Mat1<T, R*C> SpiralVisit(const Mat2<T,R,C>& a) {
  Mat1<T, R*C> o;
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
  Mat2<int, 2, 3> a1 = { {
    { { 1,2,3 } },
    { { 4,5,6 } }
  } };

  auto a1o = SpiralVisit<int, 2, 3>(a1);
  Mat1<int, 6> a1oe = { 1,2,3,6,5,4 };
  assert(a1o == a1oe);

  Mat2<int, 3, 3> a2 = { {
    { { 1, 2, 3 } },
    { { 4, 5, 6 } },
    { { 7, 8, 9 } }
  } };
  Mat1<int, 9> a2oe = { 1,2,3,6,9,8,7,4,5 };
  auto a2o = SpiralVisit<int, 3, 3>(a2);
  assert(a2o == a2oe);

  return 0;
}
