#include <bits/stdc++.h>
using namespace std;

// ・解法
// dp[k] := b + k から b に移る最小ステップ、とする
// Th: dp[k] は単調増加である
// Proof: いま、dp[0..k-1] に単調性があると仮定しよう。
//        ある t にたいし、dp[k] = dp[k - t] + 1 であり、これが最適な遷移だとする。
//        - t == 1 のときは、明らかに dp[0..k] は単調増加である。
//        - t != 1 のときは、dp[k - 1] <= dp[k - t] + 1 = dp[k] となり、単調増加である。
//          というのも、k -> k - t に移れる場合、k - 1 -> k - t に移る方法も存在するからである。
//          そのうえ、k - 1 に関しては、これが最適な遷移とは限らないため、dp[k - 1] <= dp[k - t] + 1 が成り立つ。
//
// 以上から、遷移は貪欲にやっていけばよいことがわかる。
// 明らかに不必要になった値を適宜除去するようにすれば、計算量は O(b - a + nlogn) となる。

int main() {
    int n; cin >> n;
    vector<int> x(n);
    for(int i = 0; i < n; ++i) {
        cin >> x[i];
    }
    sort(begin(x), end(x));
    x.erase(unique(begin(x), end(x)), end(x));
    int a, b; cin >> a >> b;

    int ans = 0;
    while(a > b) {
        int nxt = a - 1;
        for(int i = (int)x.size() - 1; i >= 0; --i) {
            int tnxt = a - a % x[i];
            if(tnxt >= b && tnxt < nxt) nxt = tnxt;
        }
        while(!x.empty() && a - a % x.back() < b) x.pop_back();
        a = nxt;
        ans += 1;
    }

    cout << ans << endl;
}
