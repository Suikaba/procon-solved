#include <bits/stdc++.h>
using namespace std;

// 以下のコードは通ってません
// なんで通らないのかわからん（落ちるケースが作れない

constexpr int inf = 1e9;

int s[401];
int cost[401][1501];

int main() {
    int n; cin >> n;
    vector<int> sum(n + 1);
    for(int i = 0; i < n; ++i) {
        cin >> s[i];
        sum[i + 1] = sum[i] + s[i];
    }

    int max_v = 0;
    while((max_v - 1) * (max_v - 2) <= 2 * n) ++max_v;
    max_v += 10;
    max_v = max(max_v, sum.back() / n + 2);

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j <= 1500; ++j) {
            int tsum = 0;
            for(int k = i + 1; k < n; ++k) {
                const int use = min(s[k], j - tsum);
                tsum += use;
                cost[i][j] += (k - i) * use;
            }
            if(tsum < j) {
                cost[i][j] = inf;
            }
        }
    }

    vector<vector<int>> nidx(n, vector<int>(1501, -1));
    for(int i = 0; i < n; ++i) {
        for(int need = 0; need <= 1500; ++need) {
            int tsum = 0;
            for(int j = i; j < n; ++j) {
                tsum += s[j];
                if(tsum >= need) {
                    nidx[i][need] = j;
                    break;
                }
            }
        }
    }

    // (lst, used)
    vector<vector<int>> dp(max_v, vector<int>(1501, inf));
    for(int i = 0; i < max_v; ++i) {
        dp[i][0] = 0;
    }
    for(int i = 0; i < n; ++i) {
        vector<vector<int>> nxt(max_v, vector<int>(1501, inf));
        for(int lst = 0; lst < max_v; ++lst) {
            for(int used = 0; used < 1501; ++used) {
                if(dp[lst][used] == inf) continue;
                if(used <= sum[i]) { // carry
                    for(int dv = -1; dv <= 1; ++dv) {
                        const int nlst = lst + dv, nused = used + nlst;
                        if(nlst < 0 || max_v <= nlst || 1501 <= nused) continue;
                        const int c = sum[i] - used;
                        const int cs = (c + s[i] >= nlst ? c + s[i] - nlst : cost[i][nlst - s[i] - c]);
                        nxt[nlst][nused] = min(nxt[nlst][nused], dp[lst][used] + cs);
                    }
                } else { // used right side
                    const int ni = nidx[i][used - sum[i]]; // remain position
                    if(ni == -1) continue;
                    const int remain = sum[ni + 1] - used;
                    assert(remain >= 0 && remain < s[ni]);
                    for(int dv = -1; dv <= 1; ++dv) {
                        const int nlst = lst + dv, nused = used + nlst;
                        if(nlst < 0 || max_v <= nlst || 1501 <= nused) continue;
                        const int need = nlst - min(nlst, remain);
                        const int c = ni == i ? max(remain - nlst, 0) : 0; // carry cost
                        nxt[nlst][nused] = min(nxt[nlst][nused], dp[lst][used] + cost[ni][need] + nlst * (ni - i) + c);
                    }
                }
            }
        }
        dp = move(nxt);
        //cout << " ====== " << endl;
        //cout << i << endl;
        //for(int i = 0; i <= 10; ++i) {
        //    cout << "j := " << i << "  => ";
        //    for(int k = 0; k <= min(25, sum.back()); ++k) {
        //        cout << dp[i][k] << " ";
        //    }
        //    cout << endl;
        //}
    }

    int ans = inf;
    for(int i = 0; i < max_v; ++i) {
        ans = min(ans, dp[i][sum.back()]);
    }
    cout << ans << endl;
}
