#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int dx[4] = {-2, -1, 1, 2};

const double ans[51] = {0,
                        1.0000000000,
                        1.5000000000,
                        2.5000000000,
                        2.8437500000,
                        3.2187500000,
                        3.4140625000,
                        3.5649414062,
                        3.6575927734,
                        3.7217712402,
                        3.7633666992,
                        3.7912769318,
                        3.8096590042,
                        3.8218834400,
                        3.8299714029,
                        3.8353368267,
                        3.8388911989,
                        3.8412475297,
                        3.8428090416,
                        3.8438440399,
                        3.8445299852,
                        3.8449846198,
                        3.8452859366,
                        3.8454856423,
                        3.8456180016,
                        3.8457057260,
                        3.8457638673,
                        3.8458024018,
                        3.8458279415,
                        3.8458448685,
                        3.8458560872,
                        3.8458635227,
                        3.8458684508,
                        3.8458717170,
                        3.8458738817,
                        3.8458753164,
                        3.8458762673,
                        3.8458768976,
                        3.8458773153,
                        3.8458775921,
                        3.8458777756,
                        3.8458778972,
                        3.8458779778,
                        3.8458780312,
                        3.8458780666,
                        3.8458780901,
                        3.8458781056,
                        3.8458781159,
                        3.8458781228,
                        3.8458781273,
                        3.8458781303
};

ll fill(int n, ll S, int p) {
    queue<int> que;
    que.push(p);
    ll mask = 0;
    while(!que.empty()) {
        const int p = que.front(); que.pop();
        for(int i = 0; i < 4; ++i) {
            int np = (p + dx[i]) % n;
            if(np < 0) np += n;
            if(S & (1LL << np) || (mask & (1LL << np))) continue;
            mask |= 1LL << np;
            que.push(np);
        }
    }
    return ((1LL << n) - 1) & ~mask;
}

double dfs(const int n, ll S, int p, map<pair<ll, int>, double>& dp) {
    if(dp.count(make_pair(S, p))) return dp[make_pair(S, p)];
    for(int i = 0; i < 4; ++i) {
        int np = (p + dx[i]) % n;
        if(np < 0) np += n;
        if(S & (1LL << np)) {
            dp[make_pair(S, p)] += 0.25;
        } else {
            const ll nS = fill(n, S | (1LL << np), np);
            dp[make_pair(S, p)] += (dfs(n, nS, np, dp) + 1) * 0.25;
        }
    }
    return dp[make_pair(S, p)];
}

int main() {
    int n; cin >> n;
    cout << fixed << setprecision(10) << ans[n] << endl;
}
