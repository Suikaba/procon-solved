// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1379

#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    int m; cin >> m;
    vector<int> x(m), y(m);
    for(int i = 0; i < m; ++i) {
        cin >> x[i] >> y[i];
    }

    auto slope = [&] (int i, int j) {
        if(x[i] == x[j]) return make_pair(0, 1);
        if(y[i] == y[j]) return make_pair(1, 0);
        if(x[i] > x[j]) swap(i, j);
        const int g = __gcd(abs(y[j] - y[i]), x[j] - x[i]);
        return make_pair((y[j] - y[i]) / g, (x[j] - x[i]) / g);
    };

    vector<pii> as;
    function<int(int)> solve = [&] (int S) {
        int res = 0;
        if(S == (1 << m) - 1) {
            map<pii, int> cnt;
            for(auto& p : as) cnt[p] += 1;
            for(auto& p : cnt) {
                res += p.second * (p.second - 1) / 2;
            }
            return res;
        }
        int i = 0;
        while(S & (1 << i)) i++;
        for(int j = i + 1; j < m; ++j) {
            if(S & (1 << j)) continue;
            as.push_back(slope(i, j));
            res = max(res, solve(S | (1 << j) | (1 << i)));
            as.pop_back();
        }
        return res;
    };

    cout << solve(0) << endl;
}
