#include <bits/stdc++.h>
using namespace std;

// http://codeforces.com/contest/991/problem/F

using ll = long long;

int main() {
    ll n; cin >> n;

    const ll ub = n;
    map<ll, string> pw, pw_len3or4;
    // 冪乗パート
    for(ll i = 2; i * i <= ub; ++i) {
        ll p = i;
        for(int j = 2; p * i <= ub; ++j) {
            p *= i;
            string s = to_string(i) + "^" + to_string(j);
            if(pw.count(p) == 0 || pw[p].size() > s.size()) {
                pw[p] = s;
            }
        }
    }
    for(auto& p : pw) {
        if(p.second.size() == 3 || p.second.size() == 4u) {
            pw_len3or4.insert(p);
        }
    }
    // x ^ y * p ^ q パート
    // x^y の長さで考えられるのは 3 or 4 文字のやつで十分
    // 5文字のやつは 2^100, 10^10 なので，あとは (3桁)^(1桁) を考慮すべきかを考えてみる．
    // しかし，n が10桁なので9桁にはしたい．しかし冷静に考えてみると…
    // n = 10^10 のとき，そもそも10^9が最適なので上で計算済み
    // n != 10^10 のとき，9桁でいいならそのまま出力すればいいで8桁以下にしたい．
    // じゃあ5文字のやつは使えませんね？
    for(auto& p : pw_len3or4) {
        for(auto& q : pw_len3or4) {
            if(p.first > ub / q.first) continue;
            string s = p.second + "*" + q.second;
            ll val = p.first * q.first;
            if(val <= ub && (pw.count(val) == 0 || pw[val].size() > s.size())) {
                pw[val] = s;
            }
        }
    }

    // あとは x * (上で求めた冪乗の形) + y だけ考えればいい．
    // 冪乗の形の部分はそんなに多くないので全部試して良い．
    // y として冪乗の形もありえるので注意
    // n * m (n, m はただの数字) みたいなのは不利になるだけだから考えない．
    // なぜなら (n * m で表現できる数字の桁数) >= そのまま出力 だから．
    // たとえば 99*99 は5文字だけどそのままで4桁だよね．
    string ans = to_string(n);
    for(auto& p : pw) {
        ll d = n / p.first;
        if(d == 0) break;
        string s;
        if(d > 1) s += to_string(d) + "*";
        s += p.second;
        ll r = n % p.first;
        if(r > 0) {
            s += "+";
            if(pw.count(r) && to_string(r).size() > pw[r].size()) {
                s += pw[r];
            } else {
                s += to_string(r);
            }
        }
        if(ans.size() > s.size()) {
            ans = s;
        }
    }

    cout << ans << endl;
}
