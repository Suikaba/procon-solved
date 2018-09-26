// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0282

#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    int n, r, l; cin >> n >> r >> l;
    vector<int> d(r), t(r), x(r);
    for(int i = 0; i < r; ++i) {
        cin >> d[i] >> t[i] >> x[i];
        d[i]--;
    }
    vector<int> score(n), ans(n);
    priority_queue<pii> que;
    for(int i = 0; i < n; ++i) que.emplace(0, -i);

    int pre_t = 0;
    for(int i = 0; i < r; ++i) {
        while(score[-que.top().second] != que.top().first) que.pop();
        ans[-que.top().second] += t[i] - pre_t;
        score[d[i]] += x[i];
        que.emplace(score[d[i]], -d[i]);
        pre_t = t[i];
    }
    while(score[-que.top().second] != que.top().first) que.pop();
    ans[-que.top().second] += l - pre_t;

    cout << (max_element(begin(ans), end(ans)) - begin(ans) + 1) << endl;
}
