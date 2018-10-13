#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while(t--) {
        int n, m1, m2, m3; cin >> n >> m1 >> m2 >> m3;
        vector<bool> b(n);
        queue<int> que;
        for(int i = 0; i < m1; ++i) {
            int s; cin >> s;
            que.push(s - 1);
            b[s - 1] = true;
        }
        vector<vector<bool>> c2(m2, vector<bool>(n));
        vector<int> cnt2(m2);
        for(int i = 0; i < m2; ++i) {
            int k; cin >> k;
            c2[i].resize(k);
            for(int j = 0; j < k; ++j) {
                int s; cin >> s;
                c2[i][s - 1] = true;
            }
            cnt2[i] = k;
        }
        vector<vector<bool>> ls(m3);
        vector<int> r(m3), cnt3(m3);
        for(int i = 0; i < m3; ++i) {
            int k; cin >> k;
            ls[i].resize(k);
            for(int j = 0; j < k; ++j) {
                int s; cin >> s;
                ls[i][s - 1] = true;
            }
            cin >> r[i]; r[i]--;
            cnt3[i] = k;
        }

        bool ng = false;
        while(!que.empty() && !ng) {
            const int s = que.front(); que.pop();
            for(int i = 0; i < m2; ++i) {
                if(c2[i][s]) {
                    cnt2[i]--;
                    if(cnt2[i] == 0) ng = true;
                }
            }
            for(int i = 0; i < m3; ++i) {
                if(ls[i][s]) {
                    cnt3[i]--;
                    if(cnt3[i] == 0 && !b[r[i]]) {
                        b[r[i]] = true;
                        que.push(r[i]);
                    }
                }
            }
        }

        cout << (ng ? "NO" : "YES") << endl;
    }
}
