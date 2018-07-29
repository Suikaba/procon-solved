
// http://codeforces.com/contest/543/problem/D

// 反省
// おおまかな考察はまあ流石にはいで，伝搬させかたの実装方針がダメだった．
// dp[v] := 根を v として，ダメな奴が部分木にある場合の数
// としてあとで係数をいい感じに割ろうとしてテストケースで落ちてた（未だによくわからない）．
// よくわからないので方針転換して今の形に．今のほうが明らかに楽．

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int mod = 1e9 + 7;

int add(int x, int y) {
    x %= mod; y %= mod;
    return (x + y) % mod;
}
int sub(int x, int y) {
    x %= mod; y %= mod;
    return (x - y + mod) % mod;
}
int mul(int x, int y) {
    x %= mod; y %= mod;
    return (1LL * x * y) % mod;
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for(int i = 1; i < n; ++i) {
        int p; cin >> p;
        g[p - 1].push_back(i);
        g[i].push_back(p - 1);
    }

    vector<int> dp(n, 1), ans(n);
    function<void(int, int)> dfs1 = [&] (int v, int p) {
        for(auto to : g[v]) {
            if(to == p) continue;
            dfs1(to, v);
            dp[v] = mul(dp[v], add(dp[to], 1));
        }
    };
    function<void(int, int, int)> dfs2 = [&] (int v, int p, int pval) {
        ans[v] = mul(dp[v], pval + 1);
        vector<int> childs;
        for(auto to : g[v]) {
            if(to == p) continue;
            childs.emplace_back(add(dp[to], 1));
        }
        const int m = childs.size();
        vector<int> lsum(m + 1, 1), rsum(m + 1, 1);
        for(int i = 0; i < m; ++i) {
            lsum[i + 1] = mul(lsum[i], childs[i]); // [0, i)
            rsum[m - i - 1] = mul(rsum[m - i], childs[m - 1 - i]); // [i, m - 1]
        }

        for(int i = 0, idx = 0; i < m + (p != -1); ++i) {
            if(g[v][i] == p) continue;
            dfs2(g[v][i], v, mul(mul(lsum[idx], rsum[idx + 1]), add(pval, 1)));
            idx++;
        }
    };
    dfs1(0, -1);
    dfs2(0, -1, 0);

    for(int i = 0; i < n; ++i) {
        cout << ans[i] << " \n"[i + 1 == n];
    }
}
