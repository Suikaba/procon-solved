
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1382

// 解法

// いかにも DP の高速化をする見た目をしている。
// DP を考える前に、操作を観察する。
// 色々実験などして考えてみると、
// - ある位置を3回以上塗るのは最適ではなさそう
// - 2つの区間を違う色で塗る時、それらは互いに全く交わらないか、一方がもう一方を完全に内包している
// ことがわかる。特に2つ目が本質である。
// 例えば [0, 5] を B で、[2, 7] を W で塗る操作を考えてみれば、これは [0, 1] を B でぬり、[2, 7] を W で塗る操作と同値である。

// つまり、考える必要があるのは、ある区間を一色で塗ったときに、その区間を目的の色にするのに最小何手かかるか、ということである。
// 結論を言えば、B を W が交互にあらわれる（つまり B と W の境界）個数を２で割って切り上げたものが最小手数である。
// 例えば、WWWWWW を WBWBWB にしたいとする。仮に全体を B で塗って BBBBBB としよう。すると、ここから目的の色にするためには、独立して現れる W の数だけ塗るのが最適である。この数が、"WB" または "BW" となる位置の数（今回なら、5 箇所ある）を２で割って切り上げた数に等しい。

// こうして、DPを考えるに必要な情報が揃った。
// 今、
// dp[i] := i 文字目までみて最小手数はいくらか
// sum[i] := i までみて、W と B の境界は何回現れるか
// と定義する。sum は累積和で予め計算しておく。
// すると遷移は
// - s[i - 1] == t[i - 1] のとき：dp[i] = dp[i - 1]
// - s[i - 1] != t[i - 1] のとき： dp[i] = min(dp[j] + ceil((sum[i] - sum[j + 1]) / 2) + 1)  (i - k <= j < i)
// となる。２つ目の遷移で +1 しているのは、注目区間を t[i - 1] 一色で塗る操作の分である。

// この状態だと O(nk) なので、高速化する。２つ目の遷移式を整理すると
// - dp[i] = ceil(min((2 * dp[j] + sum[i] - sum[j + 1]) / 2) + 1)  (i - k <= j < i)
// となり、min の j に依存している部分は 2 * dp[j] - sum[j + 1] だけであるから、この部分だけ取り出して、適切なデータ構造 (deque や segment tree) で管理すると良い。

#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    int n, k; cin >> n >> k;
    string s, t; cin >> s >> t;

    vector<int> sum(n + 1);
    for(int i = 0; i < n; ++i) {
        sum[i + 1] = sum[i] + (i == 0 || t[i - 1] != t[i]);
    }

    vector<int> dp(n + 1);
    deque<pii> deq;
    deq.emplace_back(0, -1);
    for(int i = 1; i <= n; ++i) {
        if(deq.front().first < i - k) deq.pop_front();
        if(s[i - 1] == t[i - 1]) {
            dp[i] = dp[i - 1];
        } else {
            dp[i] = (deq.front().second + sum[i] + 1) / 2 + 1;
        }
        if(i != n) {
            const int added = 2 * dp[i] - sum[i + 1];
            while(!deq.empty() && deq.back().second >= added) deq.pop_back();
            deq.emplace_back(i, added);
        }
    }

    cout << dp[n] << endl;
}