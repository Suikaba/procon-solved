#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    int n; cin >> n;
    vector<string> ans(n);
    priority_queue<pii> que;
    for(int i = 0; i < n; ++i) {
        int a; cin >> a;
        if(a == 0) {
            vector<pii> v;
            for(int j = 0; j < 3 && !que.empty(); ++j) {
                v.push_back(que.top());
                que.pop();
            }
            if(!v.empty()) ans[v[0].second] = "pushStack";
            if(v.size() >= 2u) ans[v[1].second] = "pushQueue";
            if(v.size() == 3u) ans[v[2].second] = "pushFront";
            while(!que.empty()) {
                auto p = que.top(); que.pop();
                ans[p.second] = "pushBack";
            }
            if(v.empty()) ans[i] = "0";
            else if(v.size() == 1) ans[i] = "1 popStack";
            else if(v.size() == 2) ans[i] = "2 popStack popQueue";
            else if(v.size() == 3) ans[i] = "3 popStack popQueue popFront";
        } else {
            que.emplace(a, i);
        }
    }
    while(!que.empty()) {
        auto p = que.top(); que.pop();
        ans[p.second] = "pushBack";
    }

    for(auto& s : ans) {
        cout << s << endl;
    }
}
