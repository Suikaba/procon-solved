#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9;

int solve(vector<int> cur) {
    const int m = cur.size();
    if(m == 1) return cur[0];
    int res = inf;
    for(int i = 0; i < m; ++i) {
        for(int j = i + 1; j < m; ++j) {
            vector<int> op, nxt;
            for(int k = 0; k < m; ++k) {
                if(k == i || k == j) op.push_back(cur[k]);
                else                 nxt.push_back(cur[k]);
            }
            {
                vector<int> nxt2 = nxt;
                nxt2.push_back(op[0] * op[1]);
                res = min(res, solve(nxt2));
            }
            {
                vector<int> nxt2 = nxt;
                nxt2.push_back(op[0] + op[1]);
                res = min(res, solve(nxt2));
            }
            {
                vector<int> nxt2 = nxt;
                nxt2.push_back(abs(op[0] - op[1]));
                res = min(res, solve(nxt2));
            }
        }
    }
    return res;
}

int main() {
    int n; cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    if((int)v.size() != n || (int)v.size() >= 7) {
        cout << 0 << endl;
        return 0;
    }

    cout << solve(v) << endl;
}
