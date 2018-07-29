
// http://codeforces.com/contest/543/problem/C

// 反省
// bitDP の更新が難しい．i -> S の順に普段は回す．
// 今回は S -> i の順に回すことで，どのビットに着目するかの探索が削減できるというわけ．
// 普段適当に書いてるループの順番にもちゃんと意味があるから気をつけること．
// バグを埋め込んだりはしなかった．

#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

int main() {
    int n, m;
    cin >> n >> m;
    vector<string> s(n);
    for(int i = 0; i < n; ++i) {
        cin >> s[i];
    }
    vector<vector<int>> a(n, vector<int>(m));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }

    vector<vector<int>> cost(m, vector<int>(n, inf));
    vector<vector<int>> mask(m, vector<int>(n));
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            vector<int> cs;
            int msk = 0;
            for(int k = 0; k < n; ++k) {
                if(s[j][i] == s[k][i]) {
                    cs.push_back(a[k][i]);
                    msk |= (1 << k);
                }
            }
            sort(begin(cs), end(cs));
            cost[i][j] = accumulate(begin(cs), end(cs) - 1, 0);
            mask[i][j] = msk;
        }
    }

    vector<int> dp(1 << n, inf);
    dp[0] = 0;
    for(int S = 0; S < (1 << n) - 1; ++S) {
        int lb = 0;
        while(S & (1 << lb)) ++lb;
        for(int i = 0; i < m; ++i) {
            dp[S | (1 << lb)] = min(dp[S | (1 << lb)], dp[S] + a[lb][i]);
            dp[S | mask[i][lb]] = min(dp[S | mask[i][lb]], dp[S] + cost[i][lb]);
        }
    }

    cout << dp.back() << endl;
}
