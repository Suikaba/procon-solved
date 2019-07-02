#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, k;
    while(cin >> n >> m >> k, n) {
        const int max_len = n + k + 10;
        vector<double> t1(n), t2(n), V(m);
        vector<int> idx(max_len, -1);
        vector<double> gate_time(n);
        for(int i = 0; i < n; ++i) {
            int X, L, F, D, UD;
            cin >> X >> L >> F >> D >> UD;
            t1[i] = (double)L / D; // east -> west
            t2[i] = (double)L / F; // west -> east
            if(UD == 1) {
                swap(t1[i], t2[i]);
                gate_time[i] = t1[i];
            }
            idx[X] = i;
        }
        for(auto& v : V) cin >> v;

        vector<vector<double>> reach(m, vector<double>(max_len));
        for(int i = 0; i < m; ++i) {
            double cur = 0;
            for(int j = 0; j < max_len; ++j) {
                if(j == 0) {
                    cur = i / V[i];
                } else {
                    cur += 1 / V[i];
                }
                if(i != 0 && j + 1 < max_len) {
                    cur = max(cur, reach[i - 1][j + 1]);
                }
                reach[i][j] = cur;

                if(idx[j] != -1) {
                    const int id = idx[j];
                    const double enter = max(cur, gate_time[id]);
                    cur = enter + t2[id];
                    gate_time[id] = enter + t1[id] + t2[id];
                }
            }
        }

        cout << fixed << setprecision(10) << reach[m - 1][k] << endl;
    }
}
