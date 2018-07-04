#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1148&lang=jp

int main() {
    int N, M;
    while(cin >> N >> M, N) {
        int R; cin >> R;
        vector<vector<int>> t_log(M, vector<int>(N));
        vector<vector<int>> sum(M, vector<int>(1 << 11));
        for(int i = 0; i < R; ++i) {
            int t, n, m, s;
            cin >> t >> n >> m >> s;
            if(s == 1) {
                t_log[m - 1][n - 1] = t;
            } else {
                sum[m - 1][t_log[m - 1][n - 1]] += 1;
                sum[m - 1][t]--;
            }
        }
        for(int i = 0; i < M; ++i) {
            for(int j = 0; j + 1 < 1 << 11; ++j) {
                sum[i][j + 1] += sum[i][j];
            }
        }

        int q;
        cin >> q;
        while(q--) {
            int ts, te, m;
            cin >> ts >> te >> m;
            int ans = 0;
            for(int i = ts; i < te; ++i) {
                ans += sum[m - 1][i] > 0;
            }
            cout << ans << endl;
        }
    }
}
