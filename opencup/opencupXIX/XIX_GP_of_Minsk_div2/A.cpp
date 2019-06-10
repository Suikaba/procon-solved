#include <bits/stdc++.h>
using namespace std;

string rec(string const& s, int l, int r, vector<vector<string>>& dp) {
    if(r < l) return "";
    if(l == r) {
        if(s[l] == '?') return dp[l][r] = "a";
        if(s[l] == '*') return dp[l][r] = "";
        return dp[l][r] = s[l];
    }
    if(dp[l][r] != "$") return dp[l][r];
    auto& res = dp[l][r];
    if(s[l] == '?') {
        if(s[r] != '*') {
            const auto tmp = rec(s, l + 1, r - 1, dp);
            if(tmp == "&") return dp[l][r] = "&";
            const char c = (s[r] == '?' ? 'a' : s[r]);
            return res = c + tmp + c;
        } else { // "*"
            const auto t1 = rec(s, l + 1, r, dp);
            const auto t2 = rec(s, l, r - 1, dp);
            if(t1 == "&" && t2 == "&") return res = "&";
            if(t2 == "&" || t1.size() + 2 <= t2.size()) {
                return res = 'a' + move(t1) + 'a';
            } else {
                return res = move(t2);
            }
        }
    } else if(s[l] == '*') {
        const auto t1 = rec(s, l, r - 1, dp);
        const auto t2 = rec(s, l + 1, r, dp);
        if(t1 == "&" && t2 == "&") return res = "&";
        if(t2 == "&" || t1.size() + (s[r] != '*' ? 2 : 0) <= t2.size()) {
            if(s[r] == '*')      return res = move(t1);
            else if(s[r] == '?') return res = 'a' + move(t1) + 'a';
            else                 return res = s[r] + move(t1) + s[r];
        } else {
            return res = move(t2);
        }
    } else {
        if(s[r] == '?' || s[l] == s[r]) {
            const auto t = rec(s, l + 1, r - 1, dp);
            if(t == "&") return res = "&";
            return res = s[l] + move(t) + s[l];
        } else if(s[r] == '*') {
            const auto t1 = rec(s, l + 1, r, dp);
            const auto t2 = rec(s, l, r - 1, dp);
            if(t1 == "&" && t2 == "&") return res = "&";
            if(t2 == "&" || t1.size() + 2 <= t2.size()) {
                return res = s[l] + move(t1) + s[l];
            } else {
                return res = move(t2);
            }
        } else {
            return res = "&";
        }
    }
}

int main() {
    string s; cin >> s;
    const int n = s.size();
    vector<vector<string>> dp(n, vector<string>(n, "$"));
    const auto ans = rec(s, 0, n - 1, dp);
    if(ans == "&") {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
}