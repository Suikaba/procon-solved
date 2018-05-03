// BEGIN CUT HERE
// END CUT HERE

#include <bits/stdc++.h>
using namespace std;

class LineOff {
public:
    int solve(const string& s, int l, int r, vector<vector<int>>& dp) {
        if(dp[l][r] != -1) return dp[l][r];
        if(l + 1 == r) return dp[l][r] = (s[l] == s[r] ? 2 : 0);
        if(l >= r) return 0;

        dp[l][r] = 0;
        for(int m = l; m < r; ++m) {
            dp[l][r] = max(dp[l][r], solve(s, l, m, dp) + solve(s, m + 1, r, dp));
        }
        if(s[l] == s[r]) {
            if(solve(s, l + 1, r - 1, dp) == r - l - 1) {
                dp[l][r] = r - l + 1;
            }
        }
        return dp[l][r];
    }

    int movesToDo(string points) {
        const int n = points.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));
        return solve(points, 0, n - 1, dp) / 2;
    }
};
