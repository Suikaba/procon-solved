#include <bits/stdc++.h>
using namespace std;

using ld = long double;
using point2d = complex<ld>;
using point3d = array<ld, 3>;

constexpr ld eps = 1e-8;

ld abs(point3d const& p) {
    return sqrt(p[0] * p[0] + p[1] * p[1] + p[2] * p[2]);
}

point3d operator-(point3d a, point3d const& b) {
    for(int i = 0; i < 3; ++i) a[i] -= b[i];
    return a;
}

class union_find {
public:
    union_find(int n) : par(n, -1) {}

    int root(int x) {
        return par[x] < 0 ? x : par[x] = root(par[x]);
    }

    void unite(int x, int y) {
        x = root(x), y = root(y);
        if(x == y) return;
        if(par[x] < par[y]) swap(x, y);
        par[x] += par[y];
        par[y] = x;
    }

private:
    vector<int> par;
};

int main() {
    int n;
    while(cin >> n, n) {
        vector<point3d> p(n);
        vector<ld> r(n);
        for(int i = 0; i < n; ++i) {
            ld x, y, z;
            cin >> x >> y >> z >> r[i];
            p[i] = {{x, y, z}};
        }

        auto contains = [&] (int i, int j) { // j contains i ?
            if(r[i] > r[j]) return false;
            // j is bigger than i
            return abs(p[i] - p[j]) + r[i] <= r[j];
        };
        vector<bool> ban(n);
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                if(i == j) continue;
                if(abs(p[i] - p[j]) < eps) { // center is same
                    if(r[i] == r[j]) { // same sphere
                        ban[i] = ban[i] || i > j;
                    } else {
                        ban[i] = ban[i] || contains(i, j);
                    }
                } else {
                    ban[i] = ban[i] || contains(i, j);
                }
            }
        }

        vector<ld> zs;
        for(int i = 0; i < n; ++i) {
            if(ban[i]) continue;
            zs.push_back(p[i][2] - r[i]);
            zs.push_back(p[i][2] + r[i]);
            for(int j = i + 1; j < n; ++j) {
                if(ban[j]) continue;
                const ld d = abs(p[i] - p[j]);
                if(d >= r[i] + r[j]) continue;
                const auto v1 = point2d(p[j][0], p[j][1]) - point2d(p[i][0], p[i][1]);
                const ld phi = arg(v1);
                const auto pj_x = real(point2d(p[i][0], p[i][1]) + v1 * exp(point2d(0, -phi)));
                const ld d1 = (r[i] * r[i] - r[j] * r[j] + d * d) / 2 / d;
                const ld theta = acos(d1 / r[i]);
                const auto v2 = point2d(pj_x, p[j][2]) - point2d(p[i][0], p[i][2]);
                zs.push_back(imag(point2d(p[i][0], p[i][2]) + v2 / abs(v2) * exp(point2d(0, -theta)) * r[i]));
                zs.push_back(imag(point2d(p[i][0], p[i][2]) + v2 / abs(v2) * exp(point2d(0, theta)) * r[i]));
            }
        }
        sort(begin(zs), end(zs));
        {
            vector<ld> zzs;
            for(auto z : zs) {
                if(zzs.empty() || (z - zzs.back()) > eps) {
                    zzs.push_back(z);
                }
            }
            zs = move(zzs);
        }

        string ans;
        int prev = 0;
        for(int i = 0; i < (int)zs.size() - 1; ++i) {
            const ld z = (zs[i + 1] + zs[i]) / 2;
            vector<ld> r2(n);
            for(int j = 0; j < n; ++j) {
                if(r[j] - abs(p[j][2] - z) < eps) continue;
                r2[j] = sqrt(r[j] * r[j] - abs(p[j][2] - z) * abs(p[j][2] - z));
            }
            union_find uf(n);
            for(int j = 0; j < n; ++j) {
                if(r2[j] == 0) continue;
                for(int k = j + 1; k < n; ++k) {
                    if(r2[k] == 0) continue;
                    if(abs(point2d(p[j][0], p[j][1]) - point2d(p[k][0], p[k][1])) < r2[j] + r2[k]) {
                        uf.unite(j, k);
                    }
                }
            }
            set<int> s;
            for(int j = 0; j < n; ++j) {
                if(r2[j] == 0) continue;
                s.insert(uf.root(j));
            }
            if(prev != (int)s.size()) {
                ans += (prev < (int)s.size() ? '1' : '0');
            }
            prev = s.size();
        }
        ans += '0';

        cout << ans.size() << endl;
        cout << ans << endl;
    }
}
