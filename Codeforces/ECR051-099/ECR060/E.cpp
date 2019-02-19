#include <bits/stdc++.h>
using namespace std;

string query(string s) {
    cout << "? " << s << endl;
    cin >> s;
    return s;
}

void answer(string s) {
    cout << "! " << s << endl;
}

int main() {
    string s; cin >> s;
    const int n = s.size();

    vector<string> t(3, string(n, ' ')), qs(3);
    for(int i = 0; i < n; ++i) {
        t[0][i] = 'a' + (i % 26);
    }
    qs[0] = query(t[0]);
    for(int i = 0; i < 26 && i < n; ++i) {
        for(int j = i; j < n; j += 26) {
            t[1][j] = 'a' + ((j / 26) % 26);
        }
    }
    qs[1] = query(t[1]);
    for(int i = 0; i < 26 * 26 && i < n; ++i) {
        for(int j = i; j < n; j += 26 * 26) {
            t[2][j] = 'a' + ((j / (26 * 26)) % 26);
        }
    }
    qs[2] = query(t[2]);

    vector<int> to(n);
    for(int i = 0; i < n; ++i) {
        vector<int> cur(n);
        iota(begin(cur), end(cur), 0);
        for(int j = 0; j < 3; ++j) {
            vector<int> nxt;
            for(auto p : cur) {
                if(t[j][i] == qs[j][p]) nxt.push_back(p);
            }
            cur = move(nxt);
        }
        assert(cur.size() == 1u);
        to[i] = cur[0];
    }

    string ans(n, ' ');
    for(int i = 0; i < n; ++i) {
        ans[i] = s[to[i]];
    }
    answer(ans);
}
