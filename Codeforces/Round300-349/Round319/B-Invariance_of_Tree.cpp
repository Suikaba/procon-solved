// http://codeforces.com/contest/576/problem/B

#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    int n; cin >> n;
    vector<int> p(n);
    for(int i = 0; i < n; ++i) {
        cin >> p[i];
        p[i]--;
    }

    vector<bool> visited(n);
    function<void(int, vector<int>& vs)> dfs = [&] (int v, vector<int>& vs) {
        if(visited[v]) return;
        visited[v] = true;
        vs.push_back(v);
        dfs(p[v], vs);
    };
    vector<vector<int>> cmp;
    int sz1_v = -1;
    int sz2_cmp = -1, odd = 0;
    for(int i = 0; i < n; ++i) {
        if(visited[i]) continue;
        vector<int> vs;
        dfs(i, vs);
        if(vs.size() == 1u) {
            sz1_v = i;
        }
        if(vs.size() == 2u) {
            sz2_cmp = cmp.size();
        }
        odd += vs.size() & 1;
        cmp.push_back(move(vs));
    }
    if(sz1_v != -1) {
        cout << "YES" << endl;
        for(int i = 0; i < n; ++i) {
            if(i == sz1_v) continue;
            cout << sz1_v + 1 << ' ' << i + 1 << endl;
        }
    } else if(sz2_cmp != -1 && odd == 0) {
        cout << "YES" << endl;
        cout << cmp[sz2_cmp][0] + 1 << ' ' << cmp[sz2_cmp][1] + 1 << endl;
        for(int i = 0; i < (int)cmp.size(); ++i) {
            if(sz2_cmp == i) continue;
            for(int j = 0; j < (int)cmp[i].size(); j += 2) {
                cout << cmp[sz2_cmp][0] + 1 << ' ' << cmp[i][j] + 1 << endl;
                cout << cmp[sz2_cmp][1] + 1 << ' ' << cmp[i][j + 1] + 1 << endl;
            }
        }
    } else {
        cout << "NO" << endl;
    }
}

