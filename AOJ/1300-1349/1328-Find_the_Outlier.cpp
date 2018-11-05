#include <bits/stdc++.h>

constexpr double eps = 1e-9;

namespace detail {
    bool is_zero(double x) {
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

// solve Ax = b
// @note: A must be regular(non-singular)
// @return: x or size 0 vector (when x does not exist or not unique)
template <typename T>
std::vector<T> gauss_jordan(matrix<T>& A, std::vector<T> const& b) {
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

using namespace std;

int main() {
    using ld = long double;
    cout << fixed << setprecision(10);
    constexpr ld max_error = 0.01;

    int d;
    while(cin >> d, d) {
        vector<double> v(d + 3);
        for(int i = 0; i < d + 3; ++i) {
            cin >> v[i];
        }

        int ans = -1;
        for(int i = 0; i < d + 3 && ans == -1; ++i) {
            for(int j = i + 1; j < d + 3; ++j) {
                matrix<ld> A(d + 1, d + 1);
                vector<ld> b(d + 1);
                int iter = 0;
                for(int k = 0; k < d + 3; ++k) {
                    if(i == k || j == k) continue;
                    for(int l = 0; l < d + 1; ++l) {
                        A[iter][l] = pow(k, l);
                        b[iter] = v[k];
                    }
                    iter++;
                }
                auto sol = gauss_jordan(A, b);
                ld vi = 0, vj = 0;
                for(int k = 0; k < d + 1; ++k) {
                    vi += sol[k] * pow(i, k);
                    vj += sol[k] * pow(j, k);
                }
                if(fabs(vi - v[i]) > max_error && fabs(vj - v[j]) > max_error) continue;

                if(fabs(vi - v[i]) <= max_error) ans = j;
                else                             ans = i;

                break;
            }
        }
        cout << ans << endl;
    }
}
