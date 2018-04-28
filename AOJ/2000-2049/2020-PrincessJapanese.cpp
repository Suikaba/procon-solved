#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2020

// 時間かかりすぎ
// 敗因：問題文が難しすぎる ICPC に強くなりたいなら読解力も必要

int main() {
    string s;
    while(cin >> s, s != "#") {
        const int n = s.size();
        auto museisi = [](char c) {
            return c == 'k' || c == 's' || c == 't' || c == 'h' || c == 'p';
        };
        auto boin = [](char c) {
            return c == 'a' || c == 'i' || c == 'u' || c == 'e' || c == 'o';
        };
        auto read_one = [&](int& p) {
            if(p >= n) throw std::runtime_error("");
            if(s[p] == '\'') {
                p += 1;
                return 0;
            }
            int mu = museisi(s[p]);
            if(s[p] == 'n' && p + 1 < n && (s[p + 1] == '\'' || s[p + 1] == 'n' || !boin(s[p + 1]))) {
                p++;
                return 0;
            }
            bool sokuon = false;
            while(p < n && !boin(s[p]) && (s[p] != 'n' || p - 1 < n && s[p - 1] != 'n') && s[p] != '\'') {
                sokuon |= p != 0 && s[p - 1] == s[p];
                p++;
            };
            p += 1;
            return (sokuon << 1) | mu;
        };
        auto is_aiu = [](char c) { return c == 'a' || c == 'i' || c == 'u'; };

        vector<int> flags, pos;
        vector<bool> f(n);
        int p = 0;
        while(p < n) {
            flags.push_back(read_one(p));
            pos.push_back(p - 1);
        };
        const int m = flags.size();
        for(int i = 0; i < m; ++i) {
            int p = pos[i];
            if(s[p] == 'n' || s[p] == '\'') continue;
            int np = i + 1 < m ? pos[i + 1] : -1;
            bool tyo = (i + 1 != m && p + 1 == np && is_aiu(s[np]));

            if(s[p] == 'a' || s[p] == 'o') {
                if(i + 1 != m && s[np] == s[p] && flags[i + 1] == 1 && (flags[i] & 1) && !tyo) {
                    f[pos[i]] = i == 0 || !f[pos[i - 1]];
                }
            } else if(s[p] == 'i' || s[p] == 'u') {
                if(flags[i] & 1 && (i + 1 == m || flags[i + 1] & 1)) {
                    f[pos[i]] = i == 0 || !f[pos[i - 1]];
                }
            }
            i += tyo;
        }

        for(int i = 0; i < n; ++i) {
            if(f[i]) {
                cout << '(' << s[i] << ')';
            } else {
                cout << s[i];
            }
        }
        cout << endl;
    }
}
