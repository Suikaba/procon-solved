#include <bits/stdc++.h>
using namespace std;

// http://codeforces.com/contest/995/problem/C

// 反省点
// この解法の場合乱択やるぐらいメリットしか無いんだからやればいいのに
// なぜやらない．通す気ある？

using ll = long long;

constexpr ll max_d = 1500000LL * 1500000LL;

int main() {
    constexpr ll ub = 1e6;
    int n; cin >> n;
    vector<int> x(n), y(n);
    vector<int> idx(n);
    for(int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
        idx[i] = i;
    }
    vector<int> c(n);
    mt19937 rnd(random_device{}());
    bool ok = false;
    while(!ok) {
        ll cur_x = 0, cur_y = 0;
        shuffle(begin(idx), end(idx), rnd);
        for(int j = 0; j < n; ++j) {
            int i = idx[j];
            if(abs(cur_x) == abs(cur_y) && abs(x[i]) > abs(y[i]) || abs(cur_x) > abs(cur_y)) {
                if(cur_x < 0 && x[i] > 0 || cur_x > 0 && x[i] < 0) {
                    cur_x += x[i];
                    cur_y += y[i];
                    c[i] = 1;
                } else {
                    cur_x -= x[i];
                    cur_y -= y[i];
                    c[i] = -1;
                }
            } else {
                if(cur_y < 0 && y[i] > 0 || cur_y > 0 && y[i] < 0) {
                    cur_x += x[i];
                    cur_y += y[i];
                    c[i] = 1;
                } else {
                    cur_x -= x[i];
                    cur_y -= y[i];
                    c[i] = -1;
                }
            }
        }
        if(abs(cur_x) > ub || abs(cur_y) > ub) {
            for(int i = 0; i < n; ++i) {
                if(c[i] == 1 && abs(cur_x - 2 * x[i]) <= ub && abs(cur_y - 2 * y[i]) <= ub) {
                    c[i] = -1;
                    break;
                } else if(c[i] == -1 && abs(cur_x + 2 * x[i]) <= ub && abs(cur_y + 2 * y[i]) <= ub) {
                    c[i] = 1;
                    break;
                }
            }
        }
        ll dist = cur_x * cur_x + cur_y * cur_y;
        ok |= dist <= max_d;
        //cout << cur_x << ' ' << cur_y << endl;
    }
    for(int i = 0; i < n; ++i) {
        cout << c[i] << " \n"[i + 1 == n];
    }
}
