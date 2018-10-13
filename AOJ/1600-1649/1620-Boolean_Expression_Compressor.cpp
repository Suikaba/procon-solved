// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1620

#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

constexpr int inf = 1e9;

int eval_impl(string const& s, int& p, const int S) {
    if(s[p] == '0' || s[p] == '1') {
        return s[p++] == '1';
    }
    if(isalpha(s[p])) {
        return (S >> (s[p++] - 'a')) & 1;
    }
    if(s[p] == '-') {
        return !eval_impl(s, ++p, S);
    }
    if(s[p] == '(') {
        const bool t1 = eval_impl(s, ++p, S);
        const char op = s[p++];
        const bool t2 = eval_impl(s, p, S);
        p++; // )
        if(op == '^') return t1 ^ t2;
        else          return t1 & t2;
    }
    assert(false);
    return -1;
}

int eval(string const& s) {
    int truth = 0;
    for(int S = 0; S < 1 << 4; ++S) {
        int p = 0;
        truth |= (eval_impl(s, p, S) << S);
    }
    return truth;
}

int main() {
    constexpr int all_mask = (1 << 16) - 1;
    vector<int> ans(1 << 16, inf);
    ans[0] = ans[(1 << 16) - 1] = 1;
    ans[eval("a")] = ans[eval("b")] = ans[eval("c")] = ans[eval("d")] = 1;
    vector<int> ts = {0, (1 << 16) - 1, eval("a"), eval("b"), eval("c"), eval("d")};
    vector<int> len = {1, 1, 1, 1, 1, 1};
    priority_queue<pii, vector<pii>, greater<>> que;
    for(int i = 0; i < (int)ts.size(); ++i) {
        que.emplace(len[i], ts[i]);
    }
    while(!que.empty()) {
        const auto l = que.top().first;
        const auto t = que.top().second;
        que.pop();
        if(ans[t ^ all_mask] > l + 1) {
            ans[t ^ all_mask] = l + 1;
            que.emplace(l + 1, t ^ all_mask);
            ts.push_back(t ^ all_mask), len.push_back(l + 1);
        }
        const int m = ts.size();
        for(int i = 0; i < m; ++i) {
            if(len[i] + l + 3 > 16) continue;
            if(ans[t & ts[i]] > len[i] + l + 3) {
                ans[t & ts[i]] = len[i] + l + 3;
                ts.push_back(t & ts[i]), len.push_back(len[i] + l + 3);
                que.emplace(len[i] + l + 3, t & ts[i]);
            }
            if(ans[t ^ ts[i]] > len[i] + l + 3) {
                ans[t ^ ts[i]] = len[i] + l + 3;
                ts.push_back(t ^ ts[i]), len.push_back(len[i] + l + 3);
                que.emplace(len[i] + l + 3, t ^ ts[i]);
            }
        }
    }

    string exp;
    while(cin >> exp, exp != ".") {
        const auto t = eval(exp);
        cout << ans[t] << endl;
    }
}
