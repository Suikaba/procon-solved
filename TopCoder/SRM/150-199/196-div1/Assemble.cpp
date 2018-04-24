// BEGIN CUT HERE
// END CUT HERE

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll inf = 1e18;

class Assemble {
public:
    int minCost(vector <int> connect) {
        const int n = connect.size();

        vector<vector<ll>> dp(n, vector<ll>(n, inf));
        function<ll(int, int)> solve = [&](int l, int r) {
            if(l + 1 == r) return 0LL;
            if(dp[l][r] != inf) return dp[l][r];
            for(int i = l + 1; i < r; ++i) {
                assert(i + 1 < n);
                ll left = solve(l, i);
                ll right = solve(i, r);
                ll cost = 1LL * (connect[l] + i - l) * connect[i] * (connect[r] + r - i);
                dp[l][r] = min(dp[l][r], left + right + cost);
            }

            return dp[l][r];
        };

        return solve(0, n - 1);
    }
};
