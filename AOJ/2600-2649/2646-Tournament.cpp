#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    int n, m; cin >> n >> m;
    vector<int> a(m + 1), b(m);
    for(auto& x : a) cin >> x;
    for(auto& x : b) cin >> x;

    vector<map<pii, int>> dp(n + 1);
    // consider ['l', 'r'), 'd' is depth, 'final_rank' represents this block winner's rank (2^r)
    function<int(int, int, int, int)> solve = [&] (int l, int r, int d, int final_rank) {
        if(final_rank == d && dp[final_rank].count({l, r})) return dp[final_rank][{l, r}];
        const int i = lower_bound(begin(a), end(a), r) - begin(a) - 1;
        int res = 0;
        if(0 <= i && a[i] <= l && r <= a[i + 1]) { // contain completely
            if(b[i] >= d + 1) {
                res = r - l - (r - l) / (1 << (n - b[i] + 1));
            } else {
                res = r - l - (b[i] == final_rank);
            }
        } else { // choose which block win
            const int mid = (l + r) / 2;
            res = min(solve(l, mid, d + 1, final_rank) + solve(mid, r, d + 1, d + 1),
                      solve(l, mid, d + 1, d + 1) + solve(mid, r, d + 1, final_rank));
        }
        if(final_rank == d) return dp[final_rank][{l, r}] = res;
        else return res;
    };

    cout << solve(0, 1 << n, 0, 0) << endl;
}
