#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2345

int main() {
    int n, m;
    double p;
    cin >> n >> m >> p;
    p /= 100;
    vector<int> cnt(1 << n);
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        for(int S = 0; S < (1 << n); ++S) {
            if((S & (1 << a)) && (S & (1 << b))) {
                cnt[S]++;
            }
        }
    }
    vector<double> dp(1 << n, 1);
    for(int S = 1; S < (1 << n); ++S) {
        if(!(S & 1)) continue;
        for(int T = S & (S - 1); T > 0; T = (T - 1) & S) {
            if(!(T & 1)) continue;
            dp[S] -= dp[T] * pow(p, cnt[S] - cnt[T] - cnt[(~T) & S]);
        }
    }
    cout << fixed << setprecision(10) << dp.back() << endl;
}
