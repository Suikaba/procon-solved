#include <bits/stdc++.h>
using namespace std;

constexpr int dx[3] = {-1, 0, 1};
constexpr int dy[3] = {0, 1, 0};

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

    int size(int x) {
        return -par[root(x)];
    }

private:
    vector<int> par;
};

int main() {
    int n, m, k; cin >> n >> m >> k;
    vector<string> v(n);
    for(int i = 0; i < n; ++i) {
        cin >> v[i];
    }

    union_find uf(n * m);
    int ans = -1;
    auto in_range = [&] (int y, int x) {
        return 0 <= y && y < n && 0 <= x && x < m;
    };
    for(int i = n - 1; i >= 0; --i) {
        for(int j = 0; j < m; ++j) {
            if(v[i][j] == '#') continue;
            for(int d = 0; d < 3; ++d) {
                const int ny = i + dy[d], nx = j + dx[d];
                if(!in_range(ny, nx) || v[ny][nx] == '#') continue;
                uf.unite(i * m + j, ny * m + nx);
            }
            if(uf.size(i * m + j) >= k) {
                ans = max(ans, i + 1);
            }
        }
    }

    cout << ans << endl;
}
