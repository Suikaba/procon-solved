// http://codeforces.com/contest/566/problem/F

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    constexpr int max_n = 1 << 20;
    int n; cin >> n;
    vector<int> cnt(max_n);
    for(int i = 0; i < n; ++i) {
        int a; cin >> a;
        cnt[a] += 1;
    }
    vector<bool> vis(max_n);
    function<int(int)> solve = [&] (int x) {
        if(x >= max_n) return 0;
        if(vis[x]) return cnt[x];
        vis[x] = true;
        int res = cnt[x];
        for(int to = x + x; to < max_n; to += x) {
            res = max(res, cnt[x] + solve(to));
        }
        return cnt[x] = res;
    };

    cout << solve(1) << endl;
}
