#include <bits/stdc++.h>
using namespace std;

// tag: 累積和、典型
// 解法
// この形なら (i, j, k, l) の総和は (a[i] + ... + a[k]) * (a[j] + ... + a[l]) と表せる。（割とよく見る
// なので累積和を取って区間の和を全部列挙し、片方の数を決めうってもう片方の数の個数を調べる。
// これは map とかでやればよい。
// 実装によっては 0 の扱いが若干面倒かもしれないので注意。
// 計算量は O(n^2 log n)

using ll = long long;

int main() {
    int a; cin >> a;
    string s; cin >> s;
    const int n = s.size();
    vector<int> sum(n + 1);
    for(int i = 0; i < n; ++i) {
        sum[i + 1] = sum[i] + (s[i] - '0');
    }

    map<int, ll> cnt;
    for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j <= n; ++j) {
            cnt[sum[j] - sum[i]] += 1;
        }
    }

    ll ans = 0;
    for(const auto& p : cnt) {
        if(p.first == 0 && a != 0) continue;
        if(p.first == 0) {
            ans += n * (n + 1) / 2 * p.second;
            continue;
        }
        if(a % p.first != 0) continue;
        const int b = a / p.first;
        if(cnt.count(b) == 0) continue;
        ans += p.second * cnt[b];
    }

    cout << ans << endl;
}
