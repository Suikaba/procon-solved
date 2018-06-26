#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<string> post(n);
    for(int i = 0; i < n; ++i) {
        cin >> post[i];
    }

    vector<map<string, string>> dp(1 << n);
    function<string(int, string)> rec = [&](int S, string order) {
        if(S == (1 << n) - 1) return string();
        if(dp[S].count(order)) return dp[S][order];
        string& res = dp[S][order];
        res = "invalid";
        for(int i = 0; i < n; ++i) {
            if(S & (1 << i)) continue;
            int idx = 0;
            for(int j = 0; j < n; ++j) {
                if(post[i][idx] == order[j]) {
                    idx++;
                }
            }
            if(idx != k) continue;
            string nord = post[i];
            reverse(begin(nord), end(nord));
            for(auto c : order) {
                if(find(begin(nord), end(nord), c) == end(nord)) {
                    nord += c;
                }
            }
            string s = rec(S | (1 << i), nord);
            if(s != "invalid") {
                res = (char)('A' + i) + s;
                break;
            }
        }
        return res;
    };

    string ans = "Z";
    for(int fst = 0; fst < n && ans == "Z"; ++fst) {
        string s = post[fst];
        reverse(begin(s), end(s));
        string remain;
        for(char c = 'A'; c < 'A' + n; ++c) {
            if(find(begin(s), end(s), c) == end(s)) {
                remain += c;
            }
        }
        do {
            string ord = s + remain;
            auto t = rec(1 << fst, ord);
            if(t != "invalid") {
                ans = min(ans, (char)('A' + fst) + t);
            }
        } while(next_permutation(begin(remain), end(remain)));
    }

    cout << ans << endl;
}
