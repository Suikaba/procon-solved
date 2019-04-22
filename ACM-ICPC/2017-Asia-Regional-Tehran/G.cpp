#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

void binary_basis_insert(vector<ull>& w, ull a) {
    for(auto v : w) {
        if(v & (-v) & a) {
            a ^= v;
        }
    }
    if(a == 0) {
        return;
    }
    for(auto& v : w) {
        if(a & (-a) & v) {
            v ^= a;
        }
    }
    w.push_back(a);
}

ull bit_reverse(ull x) {
    vector<ull> bs(64);
    for(int i = 0; i < 64; ++i) {
        bs[63 - i] = (x & (1ULL << i)) > 0;
    }
    ull res = 0;
    for(int i = 0; i < 64; ++i) {
        res |= bs[i] << i;
    }
    return res;
}

int main() {
    int n, m;
    while(cin >> n >> m, n) {
        vector<ull> v(n);
        for(int i = 0; i < m; ++i) {
            ull a, b, r; cin >> a >> b >> r;
            v[a - 1] ^= r;
            v[b - 1] ^= r;
        }

        vector<ull> es, test;
        for(int i = 1; i < n - 1; ++i) {
            binary_basis_insert(es, bit_reverse(v[i]));
        }
        for(auto& e : es) {
            e = bit_reverse(e);
        }
        sort(begin(es), end(es));
        reverse(begin(es), end(es));
        ull ans = v[0];
        for(auto e : es) {
            int b = 60;
            while(!(e & (1ULL << b))) --b;
            if(ans & (1ULL << b)) continue;
            ans ^= e;
        }

        cout << ans << endl;
    }
}