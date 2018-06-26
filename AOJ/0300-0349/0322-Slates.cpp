#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0322

using ll = long long;

int main() {
    int n, m;
    cin >> n >> m;
    vector<string> ws(n);
    set<string> origin;
    for(int i = 0; i < n; ++i) {
        cin >> ws[i];
        origin.insert(ws[i]);
    }
    auto rws = ws;
    for(auto& s : rws) reverse(begin(s), end(s));
    sort(begin(ws), end(ws));
    sort(begin(rws), end(rws));

    while(m--) {
        string ss;
        cin >> ss;
        bool left = ss[0] == '*', right = ss.back() == '*';
        string s;
        for(auto c : ss) {
            if(c != '*') s += c;
        }

        ll ans = 0;
        auto get_cnt = [](vector<string> const& ws, string& s) {
            auto l = lower_bound(begin(ws), end(ws), s);
            s.back() += 1;
            auto r = lower_bound(begin(ws), end(ws), s);
            s.back() -= 1;
            return r - l;
        };
        if(left) {
            reverse(begin(s), end(s));
            ans += get_cnt(rws, s);
        } else if(right) {
            ans += get_cnt(ws, s);
        } else {
            ans += origin.count(s);
        }

        for(int i = 0; i < (int)s.size(); ++i) {
            if(s[i] == '?') {
                for(char c = 'a'; c <= 'z'; ++c) {
                    s[i] = c;
                    if(left) {
                        ans += get_cnt(rws, s);
                    } else if(right) {
                        ans += get_cnt(ws, s);
                    } else {
                        ans += origin.count(s);
                    }
                }
                break;
            }
        }

        cout << ans << endl;
    }
}
