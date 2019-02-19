#include <bits/stdc++.h>
using namespace std;

template <int Mod, bool IsPrime = false>
class mod_int {
    using ll = long long;

public:
    constexpr mod_int() : n(0) {}
    constexpr mod_int(int n_) : n(n_) {
        if(n >= Mod)     n %= Mod;
        else if(n < 0) n = (n % Mod + Mod) % Mod;
    }
    constexpr mod_int(ll n_) : n(n_) { n = (n + Mod) % Mod; }

    constexpr operator int() const { return n; }
    constexpr operator ll() const  { return n; }

    constexpr bool operator==(mod_int const& other) const { return n == other.n; }
    constexpr mod_int& operator+=(mod_int const& other) {
        if((n += other.n) >= Mod) n -= Mod;
        return *this;
    }
    constexpr mod_int& operator-=(mod_int const& other) {
        if((n += Mod - other.n) >= Mod) n -= Mod;
        return *this;
    }
    constexpr mod_int& operator*=(mod_int const& other) {
        n = (unsigned long long)n * other.n % Mod;
        return *this;
    }
    constexpr typename std::enable_if<IsPrime, mod_int>::type& operator/=(mod_int const& other) {
        return *this *= other.inverse();
    }
    constexpr mod_int operator+(mod_int other) const { return mod_int(*this) += other; }
    constexpr mod_int operator-(mod_int other) const { return mod_int(*this) -= other; }
    constexpr mod_int operator*(mod_int other) const { return mod_int(*this) *= other; }
    constexpr mod_int operator/(mod_int other) const { return mod_int(*this) /= other; }

    constexpr typename std::enable_if<IsPrime, mod_int>::type inverse() const {
        ll a = n, b = Mod, u = 1, v = 0;
        while(b) {
            ll t = a / b;
            a -= t * b; std::swap(a, b);
            u -= t * v; std::swap(u, v);
        }
        return mod_int(u);
    }

private:
    ll n;
};

template <int Mod, bool IsPrime>
std::ostream& operator<<(std::ostream& os, mod_int<Mod, IsPrime> const& n) {
    os << (int)n;
    return os;
}

constexpr int default_mod = 1000000007;

template <int Mod = default_mod>
mod_int<Mod, true> fact(int n) {
    static std::vector<mod_int<Mod, true>> v = {1};
    if(n >= static_cast<int>(v.size())) {
        const int from = v.size(), to = n + 1024;
        v.reserve(to);
        for(int i = from; i < to; ++i) {
            v.push_back(v.back() * mod_int<Mod, true>(i));
        }
    }
    return v[n];
}

template <int Mod = default_mod>
mod_int<Mod, true> comb(int n, int r) { // nCr
    if(r < 0 || r > n) return 0;
    return fact<Mod>(n) / fact<Mod>(r) / fact<Mod>(n - r);
}

using mint = mod_int<default_mod, true>; // default

constexpr double eps = 1e-10;

namespace detail {
    bool is_zero(double x) {
        return std::fabs(x) < eps;
    }
    bool is_zero(long double x) {
        return std::fabs(x) < eps;
    }
}

template <typename T>
class matrix {
public:
    matrix() : matrix(0, 0) {}
    matrix(int r, int c, T init = T())
        : a(r, std::vector<T>(c, init)), row_sz(r), col_sz(c)
    {}

    void init(int r, int c) {
        *this = matrix(r, c);
    }

    matrix& operator+=(matrix const& that) {
        assert(row_sz == that.row_size() && col_sz == that.col_size());
        for(int i = 0; i < row_sz; ++i) {
            for(int j = 0; j < col_sz; ++j) {
                a[i][j] += that[i][j];
            }
        }
    }
    matrix& operator-=(matrix const& that) {
        assert(row_sz == that.row_size() && col_sz == that.col_size());
        for(int i = 0; i < row_sz; ++i) {
            for(int j = 0; j < col_sz; ++j) {
                a[i][j] -= that[i][j];
            }
        }
    }
    matrix& operator*=(matrix const& that) {
        assert(col_sz == that.row_size());
        matrix res(row_sz, that.col_size());
        for(int i = 0; i < row_sz; ++i) {
            for(int k = 0; k < that.col_size(); ++k) {
                for(int j = 0; j < col_sz; ++j) {
                    res[i][j] += a[i][k] * that[k][j];
                }
            }
        }
        return *this = res;
    }
    std::vector<T> operator*(std::vector<T> const& that) {
        assert(col_sz == (int)that.size());
        std::vector<T> res(row_sz);
        for(int i = 0; i < row_sz; ++i) {
            for(int j = 0; j < col_sz; ++j) {
                res[i] += a[i][j] * that[j];
            }
        }
        return res;
    }
    matrix operator+(matrix const& that) const { return matrix(*this) += that; }
    matrix operator-(matrix const& that) const { return matrix(*this) -= that; }
    matrix operator*(matrix const& that) const { return matrix(*this) *= that; }

    bool operator==(matrix const& that) const { return a == that.a; }
    bool operator!=(matrix const& that) const { return !(*this == that); }

    std::vector<T>& operator[](size_t i)             { return a[i]; }
    std::vector<T> const& operator[](size_t i) const { return a[i]; }

    int row_size() const { return row_sz; }
    int col_size() const { return col_sz; }

private:
    std::vector<std::vector<T>> a;
    int row_sz, col_sz;
};

template <typename T>
matrix<T> eye(int n) {
    matrix<T> res(n, n);
    for(int i = 0; i < n; ++i) {
        res[i][i] = 1;
    }
    return res;
}

template <typename T>
int rank_matrix(matrix<T> a) {
    const int R = a.row_size(), C = a.col_size();
    int r = 0;
    for(int i = 0; i < C && r < R; ++i) {
        int pivot = r;
        for(int j = r + 1; j < R; ++j) {
            if(std::abs(a[j][i]) > std::abs(a[pivot][i])) {
                pivot = j;
            }
        }
        std::swap(a[pivot], a[r]);
        if(detail::is_zero(a[r][i])) continue;
        for(int k = C - 1; k >= i; --k) {
            a[r][k] = a[r][k] / a[r][i];
        }
        for(int j = r + 1; j < R; ++j) {
            for(int k = C - 1; k >= i; --k) {
                a[j][k] -= a[r][k] * a[j][i];
            }
        }
        ++r;
    }
    return r;
}

template <typename T> // for double or long double
T det(matrix<T> a) {
    assert(a.row_size() == a.col_size());
    const int n = a.row_size();
    T res = 1;
    for(int i = 0; i < n; ++i) {
        int pivot = i;
        for(int j = i + 1; j < n; ++j) {
            if(std::abs(a[j][i]) > std::abs(a[pivot][i])) {
                pivot = j;
            }
        }
        swap(a[pivot], a[i]);
        res *= a[i][i] * (i != pivot ? -1.0 : 1.0);
        if(detail::is_zero(a[i][i])) break;
        if(res == T(0)) assert(false);
        for(int j = i + 1; j < n; ++j) {
            for(int k = n - 1; k >= i; --k) {
                a[j][k] -= a[i][k] * a[j][i] / a[i][i];
            }
        }
    }
    return res;
}

// solve Ax = b
// @note: A must be regular(non-singular)
// @return: x or size 0 vector (when x does not exist or not unique)
template <typename T>
std::vector<T> gauss_jordan(matrix<T> const& A, std::vector<T> const& b) {
    const int n = A.row_size();
    matrix<T> B(n, n + 1);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            B[i][j] = A[i][j];
        }
    }
    for(int i = 0; i < n; ++i) {
        B[i][n] = b[i];
    }

    for(int i = 0; i < n; ++i) {
        int pivot = i;
        for(int j = i; j < n; ++j) {
            if(std::abs(B[j][i]) > std::abs(B[pivot][i])) {
                pivot = j;
            }
        }
        std::swap(B[i], B[pivot]);

        if(detail::is_zero(B[i][i])) return std::vector<T>(); // no solution

        for(int j = i + 1; j <= n; ++j) {
            B[i][j] /= B[i][i];
        }
        for(int j = 0; j < n; ++j) {
            if(i == j) continue;
            for(int k = i + 1; k <= n; ++k) {
                B[j][k] -= B[j][i] * B[i][k];
            }
        }
    }

    std::vector<T> x(n);
    for(int i = 0; i < n; ++i) {
        x[i] = B[i][n];
    }
    return x;
}

template <typename T>
struct lu_data {
    matrix<T> A;
    std::vector<int> pi;
};

// A -> LU (A is n * n matrix)
// Verified
template <typename T>
lu_data<T> lu_decomposition(matrix<T> A) {
    std::vector<int> pi;
    const int n = A.row_size();
    for(int i = 0; i < n; ++i) {
        int pivot = i;
        for(int j = i + 1; j < n; ++j) {
            if(std::fabs(A[pivot][i]) < std::fabs(A[j][i])) {
                pivot = j;
            }
        }
        pi.push_back(pivot);
        std::swap(A[pivot], A[i]);
        for(int j = i + 1; j < n; ++j) {
            for(int k = i + 1; k < n; ++k) {
                A[j][k] -= A[i][k] * A[j][i] / A[i][i];
            }
            A[j][i] /= A[i][i];
        }
    }
    return lu_data<T>{A, pi};
}

// solve Ax = LUx = b
template <typename T>
std::vector<T> lu_solve(lu_data<T> LU, std::vector<T> b) {
    matrix<T>& A = LU.A;
    std::vector<int> &pi = LU.pi;
    const int n = A.row_size();
    for(int i = 0; i < (int)pi.size(); ++i) {
        std::swap(b[i], b[pi[i]]);
    }
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < i; ++j) {
            b[i] -= A[i][j] * b[j];
        }
    }
    for(int i = n - 1; i >= 0; --i) {
        for(int j = i + 1; j < n; ++j) {
            b[i] -= A[i][j] * b[j];
        }
        b[i] /= A[i][i];
    }
    return b;
}

template <typename T>
matrix<T> matpow(matrix<T> x, long long n) {
    auto res = eye<T>(x.row_size());
    while(n > 0) {
        if(n & 1) res = res * x;
        x = x * x;
        n >>= 1;
    }
    return res;
}

using ll = long long;

int main() {
    ll n, m; cin >> n >> m;
    matrix<mint> A(m, m);
    vector<mint> b(m);
    b[0] = 1;
    A[0][0] = 1, A[0][m - 1] = 1;
    for(int i = 1; i < m; ++i) {
        A[i][i - 1] = 1;
    }
    A = matpow(A, n);
    auto c = A*b;
    cout << c[0] << endl;
}
