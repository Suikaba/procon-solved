
// http://codeforces.com/contest/547/problem/C

// 普通に解けなかった
// 確かに包除っぽくやるだけでいけるなあ．
// 実装は，多分直接答えを求めるほうが簡潔だけど，若干ややこしいのでわかりやすいこれでいいかも．

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    constexpr int max_val = 1 << 19;
    vector<bool> is_prime(max_val, true);
    vector<int> prime;
    for(int i = 2; i < max_val; ++i) {
        if(is_prime[i]) {
            prime.push_back(i);
            for(int j = i * 2; j < max_val; j += i) {
                is_prime[j] = false;
            }
        }
    }

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<vector<int>> ps(n);
    auto insert_val = [&] (vector<int>& v, int val) {
        vector<int> added = {val};
        for(auto y : v) {
            added.push_back(-y * val);
        }
        v.insert(end(v), begin(added), end(added));
    };
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        int x = a[i];
        for(auto p : prime) {
            if(p * p > x) break;
            if(x % p == 0) {
                insert_val(ps[i], p);
                while(x % p == 0) x /= p;
            }
        }
        if(x > 1) insert_val(ps[i], x);
    }

    ll used_num = 0, tans = 0;
    vector<bool> used(n);
    vector<int> vs(max_val);
    while(q--) {
        int idx; cin >> idx;
        idx--;
        if(used[idx]) {
            used_num -= 1;
            for(auto x : ps[idx]) {
                const int sign = x < 0 ? 1 : -1;
                vs[abs(x)]--;
                tans += sign * vs[abs(x)];
            }
        } else {
            used_num += 1;
            for(auto x : ps[idx]) {
                const int sign = x < 0 ? -1 : 1;
                tans += sign * vs[abs(x)];
                vs[abs(x)]++;
            }
        }
        used[idx] = !used[idx];
        cout << used_num * (used_num - 1) / 2 - tans << endl;
    }
}
