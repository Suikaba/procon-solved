// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0298

#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    vector<pii> ans;
    for(int lp = 0; lp < 2; ++lp) {
        int n; cin >> n;
        for(int i = 0; i < n; ++i) {
            int h, m; cin >> h >> m;
            ans.emplace_back(h, m);
        }
    }
    sort(begin(ans), end(ans));
    ans.erase(unique(begin(ans), end(ans)), end(ans));
    const int n = ans.size();
    for(int i = 0; i < n; ++i) {
        if(i != 0) printf(" ");
        printf("%d:%02d", ans[i].first, ans[i].second);
    }
    printf("\n");
}
