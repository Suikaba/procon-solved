#include <bits/stdc++.h>
using namespace std;

// コーナーケース: r - l < 2 のとき、そもそも substring が取れないので YES になる

int main() {
    string s; cin >> s;
    const int n = s.size();

    const string zyx = "zyx";
    vector<vector<int>> sum(n + 1, vector<int>(3));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < 3; ++j) {
            sum[i + 1][j] = sum[i][j] + (s[i] == zyx[j]);
        }
    }

    int q; cin >> q;
    while(q--) {
        int l, r; cin >> l >> r;
        l--;
        const int len = r - l;
        vector<int> lv = {len / 3 + (len % 3 >= 1), len / 3 + (len % 3 >= 2), len / 3};
        bool ok = len < 3;
        for(int i = 0; i < 3; ++i) {
            bool tok = true;
            for(int j = 0; j < 3; ++j) {
                tok &= sum[r][(j + i) % 3] - sum[l][(j + i) % 3] == lv[j];
            }
            ok |= tok;
        }

        cout << (ok ? "YES" : "NO") << endl;
    }
}
