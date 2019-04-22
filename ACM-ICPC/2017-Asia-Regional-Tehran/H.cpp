#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

int main() {
    int n; 
    while(cin >> n, n) {
        string a, b, res; cin >> a >> b >> res;
        reverse(begin(res), end(res));
        reverse(begin(a), end(a));
        reverse(begin(b), end(b));

        vector<vector<int>> dp(n + 1, vector<int>(2, inf));
        dp[0][0] = 0;
        for(int i = 0; i < n; ++i) {
            for(int carry = 0; carry < 2; ++carry) {
                if(dp[i][carry] == inf) continue;
                const int d1 = a[i] - '0', d2 = b[i] - '0', r = res[i] - '0';
                const int sum = d1 + d2 + carry;
                if(sum % 10 == r) {
                    dp[i + 1][sum / 10] = min(dp[i + 1][sum / 10], dp[i][carry]);
                }
                dp[i + 1][carry] = min(dp[i + 1][carry], dp[i][carry] + 1);
            }
        }

        cout << dp[n][0] << endl;
    }
}