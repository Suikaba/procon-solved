#include <bits/stdc++.h>
using namespace std;

// ’Ê‚Á‚Ä‚È‚¢
// Ä‹A“I‚É‰š‚ñ‚Å‚é•”•ª‚ğ‹‚ß‚Ä‚¢‚­‚Ì‚¶‚á‚¾‚ß‚È‚Ì‚©H

using ll = unsigned long long;

int n;
int query_cnt;

ll query(vector<int> a) { // a is 0-indexed
    assert(++query_cnt <= n * (n - 1) / 2);
    cout << "? " << a.size() << endl;
    for(int i = 0; i < (int)a.size(); ++i) {
        cout << a[i] + 1 << " \n"[i + 1 == (int)a.size()];
    }
    cout << flush;

    string s; cin >> s;
    ll res = 0;
    if(find(begin(s), end(s), '.') != s.end()) {
        for(int i = 0; i < (int)s.size(); ++i) {
            if(s[i] == '.') break;
            res *= 10;
            res += s[i] - '0';
        }
        res *= 2;
        if(s.back() == '5') res += 1;
    } else {
        res = 2ULL * stoll(s);
    }
    return res;
}

void answer(ll x) {
    if(x & 1) {
        cout << "! " << x / 2 << ".5" << endl;
    } else {
        cout << "! " << x / 2 << ".0" << endl;
    }
}

ll calc_area(vector<int> vs) { // 0-indexed
    const auto tot = query(vs);

    if(vs.size() == 3) return tot;

    vector<int> in;
    for(int i = 0; i < (int)vs.size(); ++i) {
        vector<int> vs2;
        for(int j = 0; j < (int)vs.size(); ++j) {
            if(i == j) continue;
            vs2.push_back(vs[j]);
        }
        auto t = query(move(vs2));
        if(t == tot) {
            in.push_back(vs[i]);
        }
    }

    //cout << "debug in: ";
    //for(auto x : in) {
    //    cout << x << ' ';
    //}
    //cout << endl;

    sort(begin(in), end(in));
    vector<bool> used(in.size());
    auto res = tot;
    for(int i = 0; i < (int)in.size(); ++i) {
        if(used[i]) continue;
        vector<int> vs2 = {in[i]};
        used[i] = true;
        int pre = in[i];
        for(int j = 1; j < (int)in.size(); ++j) { // right
            const int ii = (i + j) % in.size();
            if(used[ii] || abs(pre - in[ii]) != 1) break;
            used[ii] = true;
            vs2.push_back(in[ii]);
            pre = in[ii];
        }
        vs2.push_back((pre + 1) % n);
        pre = in[i];
        for(int j = 1; j < (int)in.size(); ++j) { // left;
            const int ii = (i - j + in.size()) % in.size();
            if(used[ii] || abs(pre - in[ii]) != n - 1) break;
            used[ii] = true;
            vs2.push_back(in[ii]);
            pre = in[ii];
        }
        vs2.push_back((pre - 1 + n) % n);

        sort(begin(vs2), end(vs2));
        vs2.erase(unique(begin(vs2), end(vs2)), end(vs2));
        res -= calc_area(vs2);
    }
    return res;
}

int main() {
    cin >> n;
    vector<int> vs(n);
    iota(begin(vs), end(vs), 0);
    answer(calc_area(vs));
}
