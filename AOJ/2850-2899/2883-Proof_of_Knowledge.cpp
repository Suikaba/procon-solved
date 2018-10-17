// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2883

#include <bits/stdc++.h>
using namespace std;

int hash_(string const& s, int& p, vector<int> const& vs) {
    if(isalpha(s[p])) {
        return vs[s[p++] - 'a'];
    }
    if(s[p] == '[') {
        const auto op = s[++p];
        const auto h1 = hash_(s, ++p, vs);
        const auto h2 = hash_(s, p, vs);
        p++; // ']'
        if(op == '+') {
            return h1 | h2;
        } else if(op == '*') {
            return h1 & h2;
        } else {
            return h1 ^ h2;
        }
    }
    assert(false);
    return -1;
}
int parse(string const& s, vector<int> const& vs) {
    int p = 0;
    return hash_(s, p, vs);
}

int main() {
    string exp;
    while(cin >> exp, exp != ".") {
        vector<int> you(4);
        {
            string s; cin >> s;
            for(int i = 0; i < 4; ++i) {
                you[i] = s[i] - '0';
            }
        }
        const auto your_hs = parse(exp, you);
        int ans = 0;
        for(int a = 0; a <= 9; ++a) {
            for(int b = 0; b <= 9; ++b) {
                for(int c = 0; c <= 9; ++c) {
                    for(int d = 0; d <= 9; ++d) {
                        ans += parse(exp, {a, b, c, d}) == your_hs;
                    }
                }
            }
        }

        cout << your_hs << ' ' << ans << endl;
    }
}
