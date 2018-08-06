
// http://codeforces.com/contest/551/problem/B

#include <bits/stdc++.h>
using namespace std;

int main() {
    string s, a, b;
    cin >> s >> a >> b;
    vector<int> scnt(26), acnt(26), bcnt(26);
    for(int i = 0; i < (int)s.size(); ++i) {
        scnt[s[i] - 'a'] += 1;
    }
    for(int i = 0; i < (int)a.size(); ++i) {
        acnt[a[i] - 'a'] += 1;
    }
    for(int i = 0; i < (int)b.size(); ++i) {
        bcnt[b[i] - 'a'] += 1;
    }

    int cnt1 = 0, cnt2 = 0;
    for(int i = 0; i < (int)s.size(); ++i) {
        auto c = scnt;
        for(int j = 0; j < 26; ++j) {
            c[j] -= acnt[j] * i;
        }
        if(*min_element(begin(c), end(c)) < 0) break;
        int tcnt2 = s.size() + 1;
        for(int j = 0; j < 26; ++j) {
            if(bcnt[j] == 0) continue;
            tcnt2 = min(tcnt2, c[j] / bcnt[j]);
        }
        if(i + tcnt2 > cnt1 + cnt2) {
            cnt1 = i;
            cnt2 = tcnt2;
        }
    }

    for(int i = 0; i < cnt1; ++i) {
        cout << a;
    }
    for(int i = 0; i < cnt2; ++i) {
        cout << b;
    }
    for(int i = 0; i < 26; ++i) {
        for(int j = 0; j < scnt[i] - cnt1 * acnt[i] - cnt2 * bcnt[i]; ++j) {
            cout << (char)('a' + i);
        }
    }
    cout << endl;
}
