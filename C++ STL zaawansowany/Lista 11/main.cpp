#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

// ----- LUCAS ----------------------------
template <ll n>
struct Lucas {
    static constexpr ll value = \
    Lucas<n - 1>::value \
    + Lucas<n - 2>::value;
};

template <>
struct Lucas<0> {
    static constexpr ll value = 2;
};

template <>
struct Lucas<1> {
    static constexpr ll value = 1;
};


// --- BINOMIAL --------------------------------

template <ll n, ll k>
struct BinomialCoeff {
    static constexpr ll value = \
    BinomialCoeff<n - 1, k>::value \
    + BinomialCoeff<n - 1, k - 1>::value;
};

template <>
struct BinomialCoeff<0, 0> {
    static constexpr ll value = 1;
};

template <int n>
struct BinomialCoeff<n, 0> {
    static constexpr ll value = 1;
};

template <int n>
struct BinomialCoeff<n, n> {
    static constexpr ll value = 1;
};


// ----- NWD ------------------------------------

template <int a, int b>
struct nwd {
    static constexpr int value = \
    nwd<b, a % b>::value;
};

template <int a>
struct nwd<a, 0> {
    static constexpr int value = a;
};

int main()
{
  Lucas <20> l;
  cout << "L(20): "<< l.value << "\n";

  BinomialCoeff <10, 5> b;
  cout << "10 po 5: "<< b.value << "\n";

  nwd <24, 16> n;
  cout << "NWD(24, 16): "<< n.value << "\n";

  return 0;
}
