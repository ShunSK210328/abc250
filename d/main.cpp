#include <bits/stdc++.h>
using namespace std;

// #define __NL_IS_ENDL__
// #define __YESNO__
// #define __yesno__

////////////////////////////////////////////////////////////////////////////////
//
// マクロ
//
#define rep(i, a, b) for (ll i = (a); i < (b); ++i)
#define repe(i, a, b) for (ll i = (a); i <= (b); ++i)
#define rrep(i, a, b) for (ll i = (a); i > (b); --i)
#define rrepe(i, a, b) for (ll i = (a); i >= (b); --i)
#define fore(a, b) for (auto a : (b))
#define rng(a) (a).begin(), (a).end()
#define rrng(a) (a).rbegin(), (a).rend()
#define to_char(a) static_cast<char>(a)
#define to_int(a) static_cast<int>(a)
#define to_ll(a) static_cast<ll>(a)
#define to_double(a) static_cast<double>(a)
#define trace(a) cerr << __LINE__ << ">>> " << #a << "=" << a << NL
//
////////////////////////////////////////////////////////////////////////////////
//
// 型エイリアス
//
// clang-format off
using uint = unsigned int;
using ull = unsigned long long;
using ll = long long;
using pii = pair<int, int>;
template <class T> using vc = vector<T>;
template <class T> using vv = vc<vc<T>>;
using vi = vc<int>;
using vvi = vv<int>;
using vll = vc<ll>;
using vvll = vv<ll>;
using vpii = vc<pii>;
using vvpii = vv<pii>;
using vb = vc<bool>;
using vvb = vc<vb>;
using vs = vc<string>;
// clang-format on
//
////////////////////////////////////////////////////////////////////////////////
//
// ライブラリ
//
#if defined(__NL_IS_ENDL__)
#define NL endl
#else
#define NL '\n'
#endif
#if defined(__YESNO__)
const string YES = "YES";
const string NO = "NO";
#elif defined(__yesno__)
const string YES = "yes";
const string NO = "no";
#else
const string YES = "Yes";
const string NO = "No";
#endif

template <class T>
inline T input() {
    T a;
    cin >> a;
    return a;
}

template <class T1, class T2>
istream& operator>>(istream& is, pair<T1, T2>& a) {
    return is >> a.first >> a.second, is;
}

template <class T>
istream& operator>>(istream& is, vc<T>& a) {
    fore(&a_i, a) is >> a_i;
    return is;
}

template <class T>
istream& operator>>(istream& is, vv<T>& a) {
    fore(&a_i, a) fore(&a_ij, a_i) is >> a_ij;
    return is;
}

template <class T1, class T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& a) {
    return os << a.first << ' ' << a.second, os;
}

template <class T>
inline void respond(bool ans, const T& t, const T& f) {
    cout << (ans ? t : f) << NL;
}

inline void yesno(bool ans) { respond(ans, YES, NO); }

template <class T>
inline bool chmin(T& a, const T& b) {
    return a > b ? a = b, true : false;
}

template <class T>
inline bool chmax(T& a, const T& b) {
    return a < b ? a = b, true : false;
}

template <class T>
inline int len(const T& a) {
    return a.size();
}

template <ll X, int N>
struct Pow {
    static const ll value_ = Pow<X, N - 1>::value_ * X;
};

template <ll X>
struct Pow<X, 0> {
    static const ll value_ = 1LL;
};

template <class InputIterator>
struct Formatter {
    InputIterator first_, last_;
    const string delimiter_;

    Formatter(InputIterator first, InputIterator last, const string& delimiter = " ")
        : first_(first), last_(last), delimiter_(delimiter) {}
};

template <class InputIterator>
ostream& operator<<(ostream& os, const Formatter<InputIterator>& f) {
    bool flag = false;
    for (InputIterator p = f.first_; p != f.last_; p = ++p) {
        if (flag) os << f.delimiter_;
        os << *p;
        flag = true;
    }
    return os;
}

//
////////////////////////////////////////////////////////////////////////////////
//
// 問題の実装
//
// #include <atcoder/all>
// using namespace atcoder;

const ll LINF = Pow<10, 18>::value_ + 1LL;
const int INF = Pow<10, 9>::value_ + 1;
const array<int, 4> DX = {-1, 0, 1, 0};
const array<int, 4> DY = {0, -1, 0, 1};

struct Problem {
    Problem() = default;

    void solve() {
        ll N = input<ll>();

        // Nの上限が 10e18 なので、素数の範囲を 10e6　に限定する。
        ll m = pow(N, 1.0 / 3.0);

        // エラトステネスの篩で素数を列挙する。
        // prime_count_list は、素数なら 1 、そうでないなら 0
        vll prime_count_list(m + 1, 1);
        prime_count_list[0] = prime_count_list[1] = 0;
        rep(x, 2, m + 1) {
            if (prime_count_list[x] == 0) continue;
            for (ll i = x + x; i < m + 1; i += x) prime_count_list[i] = 0;
        }

        // prime_list に素数を格納する。
        // prime_count_list を素数の個数の累積和にする。
        vll prime_list;
        rep(x, 2, m + 1) {
            if (prime_count_list[x] == 1) prime_list.push_back(x);
            prime_count_list[x] += prime_count_list[x - 1];
        }

        // 列挙したすべての素数について、(p, q) の数を数える。
        ll ans = 0;
        fore(q, prime_list) ans += prime_count_list[min(N / (q * q * q), q - 1)];
        
        cout << ans << NL;
    }

    void repeat_solve() {
        int t = input<int>();
        rep(i, 0, t) solve();
    }
};

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    Problem problem;
    problem.solve();
    // problem.repeat_solve()

    return 0;
}
