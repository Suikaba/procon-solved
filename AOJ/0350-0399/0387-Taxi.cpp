// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0387

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int n; cin >> n;
    priority_queue<int, vector<int>, greater<>> que;
    for(int i = 0; i < n; ++i) {
        int m; cin >> m;
        vector<int> b(m);
        for(int j = 0; j < m; ++j) {
            cin >> b[j];
        }
        sort(rbegin(b), rend(b));
        que.push(b[0]);
        for(int j = 1; j < m; ++j) {
            if(que.top() < b[j]) {
                que.pop();
                que.push(b[j]);
            }
        }
    }
    ll ans = 0;
    while(!que.empty()) {
        ans += que.top();
        que.pop();
    }
    cout << ans << endl;
}
