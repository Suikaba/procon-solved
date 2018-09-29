// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0327

#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> v(9);
    for(int i = 0; i < 9; ++i) {
        cin >> v[i];
    }

    function<int(int)> solve = [&] (int i) {
        int res = 0;
        if(i == 6) {
            int r = v[0] + 10 * v[1] + v[2] + 100 * v[3] + 10 * v[4] + v[5];
            bool b = true;
            vector<int> cnt(10);
            for(int j = 0; j < 6; ++j) {
                cnt[v[j]] += 1;
            }
            for(int j = 0; j < 3; ++j) {
                int d = r % 10;
                r /= 10;
                b &= (d == v[8 - j] || v[8 - j] == -1) && d != 0;
                cnt[d] += 1;
            }
            res = b & (r == 0) & (*max_element(begin(cnt), end(cnt)) <= 1);
        } else {
            if(v[i] == -1) {
                for(int d = 1; d <= 9; ++d) {
                    v[i] = d;
                    res += solve(i + 1);
                    v[i] = -1;
                }
            } else {
                res = solve(i + 1);
            }
        }
        return res;
    };

    cout << solve(0) << endl;
}
