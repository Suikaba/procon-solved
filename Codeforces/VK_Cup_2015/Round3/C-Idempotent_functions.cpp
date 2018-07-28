#include <bits/stdc++.h>
using namespace std;

// http://codeforces.com/contest/542/problem/C

// 反省
// 実装ミスった．
// 最初に n 回だけ遷移させたあとにガチャガチャ計算するみたいな実装にしたけどめんどくさいだけだった．
// (最初に n 回まわせばサイクルの上に必ず行くからそこから計算しようとしていた)

using ll = long long;

ll lcm(ll a, ll b) {
    return a * b / __gcd(a, b);
}

int main() {
    int n;
    cin >> n;
    vector<int> f(n);
    for(int i = 0; i < n; ++i) {
        cin >> f[i];
        f[i]--;
    }

    ll ans = 1;
    int maxi_to_cycle_len = 0;
    for(int i = 0; i < n; ++i) {
        vector<int> ord(n, -1);
        int cur = 0, v = i;
        while(ord[v] == -1) {
            ord[v] = cur++;
            v = f[v];
        }
        ans = lcm(ans, cur - ord[v]);
        maxi_to_cycle_len = max(maxi_to_cycle_len, ord[v]);
    }
    if(maxi_to_cycle_len != 0) {
        ans = (ans + maxi_to_cycle_len - 1) / ans * ans;
    }
    cout << ans << endl;
}
