#include <bits/stdc++.h>
using namespace std;

// 準オイラーグラフであることが本質
// あとは1の個数の整合性をチェックする
// 始点は左上から純に見ていって初めて 1 となった場所としてよい（自然に角になる）
// あとは k を決め打ちすれば、始点を (a, b) として (a + kx, b + ky) となる点を頂点とするグラフを作る
// k は愚直に全部試せば、調和級数で log になるのでトータル O(nmlog(min(n, m)) で解ける

constexpr int dx[4] = {0, 1, 0, -1};
constexpr int dy[4] = {1, 0, -1, 0};

class union_find {
public:
    union_find(int n) : par(n, -1) {}

    int root(int x) {
        return par[x] < 0 ? x : par[x] = root(par[x]);
    }

    void unite(int x, int y) {
        x = root(x), y = root(y);
        if(x == y) return;
        if(par[x] > par[y]) swap(x, y);
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
    int n, m; cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    vector<vector<int>> vsum(n + 1, vector<int>(m)), hsum(n, vector<int>(m + 1));
    int sum = 0;
    int sy = -1, sx = -1;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            cin >> a[i][j];
            if(a[i][j] == 1 && sy == -1) {
                sy = i, sx = j;
            }
            sum += a[i][j];
        }
    }
    if(sum == 1) {
        cout << -1 << endl;
        return 0;
    }
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            hsum[i][j + 1] = hsum[i][j] + a[i][j];
            vsum[i + 1][j] = vsum[i][j] + a[i][j];
        }
    }

    vector<int> ans;
    vector<vector<int>> idx(n, vector<int>(m, -1));
    auto is_euler = [] (vector<int> const& deg) {
                        int cnt = 0;
                        for(auto d : deg) {
                            cnt += d & 1;
                        }
                        return cnt == 0 || cnt == 2;
                    };
    for(int k = 2; k < min(n, m); ++k) {
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                idx[i][j] = -1;
            }
        }
        int cnt = 0;
        for(int y = sy; y < n; y += k) {
            for(int x = sx % k; x < m; x += k) {
                if(a[y][x] == 1) {
                    idx[y][x] = cnt++;
                }
            }
        }
        union_find uf(cnt);
        vector<int> deg(cnt);
        auto in_range = [&] (int y, int x) {
                            return 0 <= y && y < n && 0 <= x && x < m;
                        };
        int tcnt = 0;
        for(int y = sy; y < n; y += k) {
            for(int x = sx % k; x < m; x += k) {
                if(idx[y][x] == -1) continue;
                for(int i = 0; i < 4; ++i) {
                    const int ny = y + k * dy[i], nx = x + k * dx[i];
                    if(!in_range(ny, nx) || idx[ny][nx] == -1) continue;
                    if((ny == y && abs(hsum[y][nx] - hsum[y][x]) != k)
                      || (nx == x && abs(vsum[ny][x] - vsum[y][x]) != k)) continue;
                    tcnt += k - 1;
                    uf.unite(idx[y][x], idx[ny][nx]);
                    deg[idx[y][x]] += 1;
                }
            }
        }
        tcnt /= 2;
        tcnt += cnt;
        if(uf.size(0) == cnt && is_euler(deg) && tcnt == sum) {
            ans.push_back(k);
        }
    }

    if(ans.empty()) {
        cout << -1 << endl;
    } else {
        for(int i = 0; i < (int)ans.size(); ++i) {
            cout << ans[i] << " \n"[i + 1 == (int)ans.size()];
        }
    }
}
