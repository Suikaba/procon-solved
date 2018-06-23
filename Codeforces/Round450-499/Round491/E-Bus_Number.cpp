#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    vector<vector<ll>> nCr(1 << 8, vector<ll>(1 << 8));
    for(int i = 0; i < 1 << 8; ++i) {
        for(int j = 0; j <= i; ++j) {
            if(j == 0 || i == j) nCr[i][j] = 1;
            else nCr[i][j] = nCr[i - 1][j - 1] + nCr[i - 1][j];
        }
    }
    string s;
    cin >> s;
    vector<int> cnt(10);
    for(auto c : s) {
        cnt[c - '0']++;
    }
    ll ans = 0;
    vector<int> use(10);
    function<void(int)> calc = [&] (int d) {
        if(d == 10) {
            ll t = 1;
            int sum = accumulate(begin(use), end(use), 0);
            for(int i = 0; i <= 9; ++i) {
                t *= nCr[sum][use[i]];
                sum -= use[i];
            }

            if(use[0] > 0) {
                use[0]--;
                ll sub = 1;
                int sum = accumulate(begin(use), end(use), 0);
                for(int i = 0; i <= 9; ++i) {
                    sub *= nCr[sum][use[i]];
                    sum -= use[i];
                }
                ans -= sub;
                assert(sub < t);
                use[0] += 1;
            }
            ans += t;
        } else {
            for(int i = min(cnt[d], 1); i <= cnt[d]; ++i) {
                use[d] = i;
                calc(d + 1);
            }
        }
    };
    calc(0);

    cout << ans << endl;
}
