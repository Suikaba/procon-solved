#include <bits/stdc++.h>
using namespace std;

// tag: 乱択(randomized)

// 問題概要
// n 要素の数列 a が与えられる。
// 次の条件を満たす最大の g を求めよ。
// ・a のうちの半分以上の要素が、g を約数に持つ。
// n <= 10^6, a[i] <= 10^12

// 解法
// 「何でもいいから半分以上が～」みたいな制約のときに乱択が選択肢にないのは精進不足。
// 適当に要素 a[k] を1つ選ぶ。
// この要素の約数のうちに、求める答えが存在する確率が 1/2 となる。
// 約数を全列挙して、それぞれが条件を満たすかどうかを調べる。
// 約数の個数を d とする。
// 愚直に調べてしまうと O(d * n * 乱択の回数) かかるのでだめ。
// a[i] を見る代わりに、gcd(a[i], a[k]) (i = 1, ..., n) について考える。
// gcd(a[i], a[k]) が取りうる値は d 個以下であるから、このうえで調べると O(d^2) に改善することができる。
// 数を数えるときに map を使うと TLE したので、vector で定数倍早くしたほうがいいかもしれない。
// 乱択回数を x とすれば、正しい答えが求まる確率は 1 - (1/2)^x なので10回程度で十分だと思う。

// 感想
// にしても TL が厳しい。どう頑張っても 3sec ぐらいになる。
// n <= 10^5 じゃなにかまずかったのか？

using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> rnd(0, n - 1);
    ll ans = 1;
    for(int lp = 0; lp < 11; ++lp) {
        const ll v = a[rnd(mt)];
        vector<ll> divs;
        for(ll x = 1; x * x <= v; ++x) {
            if(v % x != 0) continue;
            divs.push_back(x);
            if(x * x != v) divs.push_back(v / x);
        }
        sort(begin(divs), end(divs));
        const int sz = divs.size();
        vector<int> cnt(sz);
        for(int i = 0; i < n; ++i) {
            const int idx = lower_bound(begin(divs), end(divs), __gcd(a[i], v)) - begin(divs);
            cnt[idx] += 1;
        }
        for(int i = 0; i < sz; ++i) {
            int tcnt = 0;
            for(int j = i; j < sz; ++j) {
                if(divs[j] % divs[i] == 0) {
                    tcnt += cnt[j];
                }
            }
            if(tcnt * 2 >= n) {
                ans = max(ans, divs[i]);
            }
        }
    }

    cout << ans << endl;
}
