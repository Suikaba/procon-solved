// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0328

#include <bits/stdc++.h>
using namespace std;

int main() {
    constexpr int max_m = 1 << 21;
    int n; cin >> n;
    vector<int> cnt(max_m);
    for(int i = 0; i < n; ++i) {
        int a, b; cin >> a >> b;
        cnt[a + b] += 1;
    }
    for(int i = 0; i + 1 < max_m; ++i) {
        cnt[i + 1] += cnt[i] / 2;
        cnt[i] &= 1;
        if(cnt[i] & 1) cout << i << " " << 0 << endl;
    }
}
