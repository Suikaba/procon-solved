#include <bits/stdc++.h>
using namespace std;

//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1134

pair<string, string> split(string s) {
    const int sp = s.find('-');
    return {s.substr(0, sp), s.substr(sp + 1)};
}

int main() {
    int N;
    while(cin >> N, N) {
        map<string, int> idx;
        vector<int> s1(N), s2(N);
        for(int i = 0; i < N; ++i) {
            string s;
            cin >> s;
            string a, b;
            tie(a, b) = split(s);
            if(idx.count(a) == 0) {
                const int nid = idx.size();
                idx[a] = nid;
            }
            if(idx.count(b) == 0) {
                const int nid = idx.size();
                idx[b] = nid;
            }
            s1[i] = idx[a];
            s2[i] = idx[b];
        }

        const int M = idx.size();
        cout << M << endl;

        vector<vector<bool>> g(M, vector<bool>(M));
        vector<vector<int>> g2(M); // undirected
        for(int i = 0; i < N; ++i) {
            g[s1[i]][s2[i]] = true;
            g2[s1[i]].push_back(s2[i]);
            g2[s2[i]].push_back(s1[i]);
        }
        for(int i = 0; i < M; ++i) {
            g[i][i] = true;
        }
        for(int i = 0; i < M; ++i) {
            for(int j = i + 1; j < M; ++j) {
                bool cond1 = false, cond2 = true, cond3 = true;
                for(int k = 0; k < M; ++k) {
                    if(i == k || j == k) continue;
                    cond1 |= (g[i][k] || g[k][i]) && (g[j][k] || g[k][j]);
                    cond2 &= !(g[k][i] && g[j][k]);
                    cond3 &= !(g[i][k] && g[k][j]);
                }
                if(cond1 && cond2 && cond3) {
                    g[i][j] = g[j][i] = true;
                }
            }
        }
        for(int k = 0; k < M; ++k) {
            for(int i = 0; i < M; ++i) {
                for(int j = 0; j < M; ++j) {
                    g[i][j] = g[i][j] | (g[i][k] && g[k][j]);
                }
            }
        }

        vector<int> color(M, -1);
        function<void(int, int, int)> dfs = [&](int v, int p, int col) {
            if(color[v] != -1) return;
            color[v] = col;
            for(auto to : g2[v]) {
                if(to == p) continue;
                dfs(to, v, col ^ 1);
            }
        };
        for(int i = 0; i < M; ++i) {
            dfs(i, -1, 0);
        }

        int Q;
        cin >> Q;
        while(Q--) {
            string s;
            cin >> s;
            string a, b;
            tie(a, b) = split(s);
            if(idx.count(a) == 0 || idx.count(b) == 0) {
                cout << "NO" << endl;
            } else {
                const int ai = idx[a], bi = idx[b];
                if(g[ai][bi] && color[ai] != color[bi]) {
                    cout << "YES" << endl;
                } else {
                    cout << "NO" << endl;
                }
            }
        }
    }
}