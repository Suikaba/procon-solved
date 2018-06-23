#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

int main() {
    vector<string> fld(2);
    for(int i = 0; i < 2; ++i) {
        cin >> fld[i];
    }
    const int n = fld[0].size();

    vector<int> dp(4, -inf);
    dp[0b11] = 0;
    for(int i = 0; i < n; ++i) {
        vector<int> nxt(4, -inf);
        const int cur = ((fld[0][i] == 'X') << 1) | (fld[1][i] == 'X');
        for(int pre = 0; pre < 4; ++pre) {
            if(dp[pre] == -inf) continue;
            nxt[cur] = max(nxt[cur], dp[pre]);
            if(pre == 0 && !(cur & 2)) nxt[cur | 2] = max(nxt[cur | 2], dp[pre] + 1);
            if(!(pre & 2) && cur == 0) nxt[cur | 3] = max(nxt[cur | 3], dp[pre] + 1);
            if(!(pre & 1) && cur == 0) nxt[cur | 3] = max(nxt[cur | 3], dp[pre] + 1);
            if(pre == 0 && !(cur & 1)) nxt[cur | 1] = max(nxt[cur | 3], dp[pre] + 1);
        }
        dp = move(nxt);
        //cout << bitset<2>(cur) << ": " << dp[0] << ' ' << dp[1] << ' ' << dp[2] << ' ' << dp[3] << endl;
    }
    cout << *max_element(begin(dp), end(dp)) << endl;
}
