#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    while(cin >> n >> m) {
        vector<int> cs(n), pos(n);
        vector<bool> ok(2000);
        pos[0] = m;
        ok[m] = true;
        for(int i = 0; i < n; ++i) {
            string s; cin >> s;
            if(s == "A") cs[i] = 11;
            else if(isdigit(s[0])) cs[i] = stoi(s);
            else cs[i] = 10;
        }
        for(int i = 0; i < n - 1; ++i) {
            pos[i + 1] = pos[i] + cs[i];
            ok[pos[i + 1]] = true;
        }

        vector<double> dp(pos.back() + 100, -1);
        function<double(int)> solve = [&] (int p) -> double {
            if(p > (int)pos.back()) return 0;
            if(dp[p] >= 0) return dp[p];
            if(ok[p]) return dp[p] = 1;
            dp[p] = 0;
            for(int i = 2; i <= 9; ++i) {
                dp[p] += solve(p + i);
            }
            dp[p] += solve(p + 10) * 4 + solve(p + 11);
            dp[p] /= 13;
            return dp[p];
        };

        double ans = 0;
        for(int i = 1; i <= 10; ++i) {
            ans += solve(i) / 10;
        }
        cout << fixed << setprecision(10) << ans << endl;
    }
}
