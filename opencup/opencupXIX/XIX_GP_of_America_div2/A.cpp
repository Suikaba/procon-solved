#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
typedef std::complex<ld> point;
typedef std::vector<point> polygon;

const ld pi = std::acos(-1.0);

int n, k;
ld nCr[2501][2501];
ld dist[2501][2501];

void init() {
    for(int i = 0; i <= n; ++i) {
        for(int j = 0; j <= i; ++j) {
            if(j == 0 || j == i) {
                nCr[i][j] = 1;
            } else {
                nCr[i][j] = nCr[i - 1][j - 1] + nCr[i - 1][j];
            }
            assert(!isnan(nCr[i][j]));
        }
    }
}

ld cross(point const& a, point const& b) {
    return std::imag(std::conj(a) * b);
}

ld area(polygon const& p) {
    const int N = p.size();
    ld res = 0;
    for(int i = 0; i < N; ++i) {
        res += cross(p[i], p[(i + 1)%N]);
    }
    return res / 2;
}

ld area(const ld a, const ld b, const ld c) {
    const ld s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

int main() {
    cout << fixed << setprecision(10);
    cin >> n >> k;
    init();
    polygon ps;
    for(int i = 0; i < n; ++i) {
        ld x, y; cin >> x >> y;
        ps.push_back(point(x, y));
    }
    reverse(ps.begin(), ps.end());
    for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            dist[i][j] = dist[j][i] = abs(ps[i] - ps[j]);
        }
    }

    ld ans = area(ps) * nCr[n][k];
    for(int i = 0; i < n; ++i) {
        ld cur_s = 0;
        for(int jj = 2; jj < n; ++jj) {
            const int j = (i + jj) % n;
            cur_s += area(dist[i][j], dist[j][(j - 1 + n) % n], dist[i][(j - 1 + n) % n]);
            ans -= cur_s * nCr[n - jj - 1][k - 2];
        }
    }
    ans /= nCr[n][k];

    //assert(!isnan(ans));
    cout << ans << endl;
}
