#include <bits/stdc++.h>
using namespace std;

constexpr double eps = 1e-9;

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
        return res;
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
        if(detail::is_zero(a[i][i])) return 0;
        for(int j = i + 1; j < n; ++j) {
            for(int k = n - 1; k >= i; --k) {
                a[j][k] -= a[i][k] * a[j][i] / a[i][i];
            }
        }
    }
    return res;
}

int main() {
    random_device seed_gen;
    default_random_engine engine(seed_gen());
    uniform_real_distribution<> dist(0.0, 1.0);

    int n, m; cin >> n >> m;
    vector<vector<int>> g(n, vector<int>(n));
    for(int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        g[a - 1][b - 1] = g[b - 1][a - 1] = 1;
    }

    constexpr int loop_cnt = 100;
    bool ans = false;
    for(int lp = 0; lp < loop_cnt; ++lp) {
        matrix<double> A(n, n, 0);
        for(int i = 0; i < n; ++i) {
            for(int j = i; j < n; ++j) {
                if(g[i][j] == 0) continue;
                A[i][j] = dist(engine);
                if(i == 0 && dist(engine) >= 0.5) A[j][i] = A[i][j];
                else                     A[j][i] = -A[i][j];
            }
        }

        const auto d = det(A);
        ans |= !detail::is_zero(d);
    }

    cout << (ans ? "Yes": "No") << endl;
}
