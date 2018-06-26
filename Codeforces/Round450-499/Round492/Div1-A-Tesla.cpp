#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> v(4, vector<int>(n));
    for(int i = 0; i < 4;++i) {
        for(int j = 0; j < n; ++j) {
            cin >> v[i][j];
        }
    }
    bool ok = false;
    for(int i = 0; i < n; ++i) {
        ok |= v[1][i] == 0;
        ok |= v[2][i] == 0;
        ok |= v[0][i] == v[1][i];
        ok |= v[3][i] == v[2][i];
    }
    if(!ok) {
        cout << -1 << endl;
        return 0;
    }
    vector<int> ans_i, ans_r, ans_c;
    int cnt = k;
    while(cnt > 0) {
        //cout << cnt << endl;
        for(int i = 0; i < n; ++i) { // parking
            if(v[0][i] != 0 && v[0][i] == v[1][i]) {
                ans_i.push_back(v[1][i]);
                ans_r.push_back(1);
                ans_c.push_back(i + 1);
                //cout << "park: " << ans_i.back() << ' ' << ans_r.back() << ' ' << ans_c.back() << endl;
                v[1][i] = 0;
                cnt--;
            }
            if(v[2][i] != 0 && v[2][i] == v[3][i]) {
                ans_i.push_back(v[2][i]);
                ans_r.push_back(4);
                ans_c.push_back(i + 1);
                //cout << "park: " << ans_i.back() << ' ' << ans_r.back() << ' ' << ans_c.back() << endl;
                v[2][i] = 0;
                cnt--;
            }
        }
        // rotate
        vector<bool> moved(k + 1);
        int move_cnt = 0;
        for(int i = 0; i < n; ++i) {
            move_cnt += v[1][i] != 0;
            move_cnt += v[2][i] != 0;
        }
        moved[0] = true;
        while(move_cnt > 0) {
            for(int i = 0; i < n; ++i) {
                if(i == 0) {
                    if(v[2][0] == 0 && !moved[v[1][0]]) {
                        ans_i.push_back(v[1][0]);
                        ans_r.push_back(3); ans_c.push_back(1);
                        moved[v[1][0]] = true;
                        v[2][0] = v[1][0];
                        v[1][0] = 0;
                        move_cnt--;
                    }
                }
                if(i != 0) {
                    if(v[1][i - 1] == 0 && !moved[v[1][i]]) {
                        moved[v[1][i]] = true;
                        ans_i.push_back(v[1][i]);
                        ans_r.push_back(2), ans_c.push_back(i);
                        v[1][i - 1] = v[1][i];
                        v[1][i] = 0;
                        move_cnt--;
                    }
                }
                if(i != n - 1) {
                    if(v[2][i + 1] == 0 && !moved[v[2][i]]) {
                        moved[v[2][i]] = true;
                        ans_i.push_back(v[2][i]);
                        ans_r.push_back(3), ans_c.push_back(i + 2);
                        v[2][i + 1] = v[2][i];
                        v[2][i] = 0;
                        move_cnt--;
                    }
                }
                if(i == n - 1) {
                    if(!moved[v[2][i]] && v[1][i] == 0) {
                        ans_i.push_back(v[2][i]);
                        ans_r.push_back(2); ans_c.push_back(n);
                        moved[v[2][i]] = true;
                        v[1][i] = v[2][i];
                        v[2][i] = 0;
                        move_cnt--;
                    }
                }
            }
        }
    }

    const int m = ans_i.size();
    cout << m << endl;
    for(int i = 0; i < m; ++i) {
        cout << ans_i[i] << ' ' << ans_r[i] << ' ' << ans_c[i] << endl;
    }
}
