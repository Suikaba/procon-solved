// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0353

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    { // compress
        auto b = a;
        sort(begin(b), end(b));
        for(int i = 0; i < n; ++i) {
            a[i] = lower_bound(begin(b), end(b), a[i]) - begin(b);
        }
    }

    using S = priority_queue<int, vector<int>, greater<>>;
    function<void(S&, S&)> merge = [] (S& s1, S& s2) {
        if(s1.size() < s2.size()) swap(s1, s2);
        while(!s2.empty()) {
            s1.push(s2.top()); s2.pop();
        }
    };

    queue<shared_ptr<S>> que;
    for(int i = 0; i < n; ++i) {
        auto q = make_shared<S>(); q->push(a[i]);
        que.push(move(q));
    }
    ll ans = 0;
    for(int i = 0; i < n; ++i) {
        auto s = que.front(); que.pop();
        while(s->top() != i) {
            auto v = que.front(); que.pop();
            merge(*s, *v);
        }
        s->pop();
        ans += s->size();
        que.push(s);
    }

    cout << ans << endl;
}
