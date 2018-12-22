#include <bits/stdc++.h>
using namespace std;

int main() {
    string s; cin >> s;
    const int n = s.size();
    vector<vector<int>> sum(n + 1, vector<int>(26));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < 26; ++j) {
            sum[i + 1][j] += sum[i][j] + (s[i] == ('a' + j));
        }
    }

    auto check = [&] (int len) {
        for(int j = 0; j < 26; ++j) {
            bool ok = true;
            for(int i = 0; i + len <= n; ++i) {
                ok &= sum[i + len][j] - sum[i][j] > 0;
            }
            if(ok) return true;
        }
        return false;
    };
    int lb = 0, ub = n + 1;
    while(ub - lb > 1) {
        const int mid = (ub + lb) / 2;
        (check(mid) ? ub : lb) = mid;
    }

    cout << ub << endl;
}
