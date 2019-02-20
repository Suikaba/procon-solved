#include <bits/stdc++.h>
using namespace std;

struct point {
    int y, x, kind;
};

int main() {
    int n, m, k, s; cin >> n >> m >> k >> s;
    vector<vector<int>> a(n, vector<int>(m));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            cin >> a[i][j];
            a[i][j]--;
        }
    }
    vector<int> q(s);
    for(int i = 0; i < s; ++i) {
        cin >> q[i];
        q[i]--;
    }


    vector<point> ps;
    for(int ki = 0; ki < k; ++ki) {
        auto search = [&] (int y, int x) {
            int cy = -1, cx = -1;
            for(int i = 0; i < n; ++i) {
                for(int j = 0; j < m; ++j) {
                    if(a[i][j] != ki) continue;
                    if(cy == -1 || abs(cy - y) + abs(cx - x) > abs(i - y) + abs(j - x)) {
                        cy = i, cx = j;
                    }
                }
            }
            if(cy != -1) {
                ps.push_back(point{cy, cx, ki});
            }
        };
        search(0, 0);
        search(n - 1, 0);
        search(0, m - 1);
        search(n - 1, m - 1);
    }
    vector<vector<int>> dist(k, vector<int>(k));
    for(const auto& p1 : ps) {
        for(const auto& p2 : ps) {
            dist[p1.kind][p2.kind] = max(dist[p1.kind][p2.kind], abs(p1.x - p2.x) + abs(p1.y - p2.y));
        }
    }

    int ans = 0;
    for(int i = 0; i + 1 < s; ++i) {
        ans = max(ans, dist[q[i]][q[i + 1]]);
    }
    cout << ans << endl;
}
