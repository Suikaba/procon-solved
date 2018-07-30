
// http://codeforces.com/contest/546/problem/C

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<deque<int>> st(2);
    for(int i = 0; i < 2; ++i) {
        int k; cin >> k;
        st[i].resize(k);
        for(int j = 0; j < k; ++j) {
            cin >> st[i][j];
        }
    }
    set<pair<deque<int>, deque<int>>> vis;
    vis.emplace(st[0], st[1]);
    while(!st[0].empty() && !st[1].empty()) {
        const vector<int> vs = {st[0].front(), st[1].front()};
        st[0].pop_front();
        st[1].pop_front();
        st[vs[0] < vs[1]].push_back(vs[vs[0] > vs[1]]);
        st[vs[0] < vs[1]].push_back(vs[vs[1] > vs[0]]);
        if(vis.count(make_pair(st[0], st[1]))) {
            cout << -1 << endl;
            return 0;
        }
        vis.emplace(st[0], st[1]);
    }

    cout << vis.size() - 1 << ' ';
    cout << (st[0].empty() ? 2 : 1) << endl;
}
