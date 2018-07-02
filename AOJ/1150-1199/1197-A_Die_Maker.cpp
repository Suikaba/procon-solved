#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1197

// 反省点
// チームで解いたので考察はノーコメント．
// 実装はうまくいったと思う．

const string dir = "ENSW";
const string rdir = "WSNE";
constexpr int rot[4][6] = { {2, 1, 5, 3, 0, 4}, {3, 0, 2, 5, 4, 1},
                            {1, 5, 2, 0, 4, 3}, {4, 1, 0, 3, 5, 2}};

vector<int> roll(vector<int> const& v, char d) {
    const int p = find(begin(dir), end(dir), d) - begin(dir);
    vector<int> res(6);
    for(int i = 0; i < 6; ++i) {
        res[i] = v[rot[p][i]];
    }
    return res;
}

bool check(vector<int> const& dice) {
    int v1 = dice[0] + dice[5], v2 = dice[2] + dice[4], v3 = dice[1] + dice[3];
    int cnt = 0;
    if(dice[0] < 0) return false;
    if(v1 >= v2 + v3 + 1) return false;
    if(v2 > v1 + v3 + 1) return false;
    if(v2 == v1 + v3 + 1) cnt++;
    if(v3 > v1 + v2 + 1) return false;
    if(v3 == v1 + v2 + 1) cnt++;
    return cnt <= 1;
};

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    vector<int> v(6);
    while(true) {
        for(int i = 0; i < 6; ++i) cin >> v[i];
        const int n = accumulate(begin(v), end(v), 0);
        if(n == 0) break;
        sort(begin(v), end(v));
        int p, q;
        cin >> p >> q;

        string ans(n, 'Z');
        do {
            auto dice = v;
            if(!check(dice)) continue;
            string t;
            bool lt = false;
            for(int i = 0; i < n; ++i) {
                bool ok = false;
                for(int j = 0; j < 4; ++j) {
                    dice = roll(dice, dir[j]);
                    dice[0]--;
                    if(check(dice) && (lt || ans[i] >= dir[j])) {
                        t += dir[j];
                        lt |= ans[i] > dir[j];
                        ok = true;
                        break;
                    }
                    dice[0]++;
                    dice = roll(dice, rdir[j]);
                }
                if(!ok) {
                    t.clear();
                    break;
                }
            }
            if(t.empty()) continue;
            if(ans.empty()) ans = move(t);
            else ans = min(ans, t);
        } while(next_permutation(begin(v), end(v)));

        if(ans[0] == 'Z') {
            cout << "impossible" << endl;
        } else {
            cout << ans.substr(p - 1, q - p + 1) << endl;
        }
    }
}
