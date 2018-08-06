
// http://codeforces.com/contest/547/problem/B

// 反省
// 実装方針がダメダメだった．以下のコードはいいやり方のほう．
// 区間を set, multiset で管理して頑張るのが悪いほう．
// てんでだめというわけではない（考え方はシンプルだからね）が，区間のマージの確認とか，
// set の end, begin の処理とか場合分けが増えてバグりかねない．

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<int> st;
    vector<int> llen(n), rlen(n);
    for(int i = 0; i < n; ++i) {
        while(!st.empty() && a[st.back()] >= a[i]) st.pop_back();
        llen[i] = (st.empty() ? i + 1 : i - st.back());
        st.push_back(i);
    }
    st.clear();
    for(int i = n - 1; i >= 0; --i) {
        while(!st.empty() && a[st.back()] >= a[i]) st.pop_back();
        rlen[i] = (st.empty() ? n - i : st.back() - i);
        st.push_back(i);
    }

    vector<int> ans(n);
    for(int i = 0; i < n; ++i) {
        ans[llen[i] + rlen[i] - 2] = max(ans[llen[i] + rlen[i] - 2], a[i]);
    }
    for(int i = n - 1; i >= 1; --i) {
        ans[i - 1] = max(ans[i - 1], ans[i]);
    }

    for(int i = 0; i < n; ++i) {
        cout << ans[i] << " \n"[i + 1 == n];
    }
}
