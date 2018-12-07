#include <bits/stdc++.h>
using namespace std;

using matrix = vector<vector<int>>;

matrix mat_op(matrix a, matrix b) {
    const int n = a.size();
    matrix res(n, vector<int>(n, -1));
    for(int k = 0; k < n; ++k) {
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                if(a[i][k] == -1 || b[k][j] == -1) continue;
                res[i][j] = max(res[i][j], a[i][k] + b[k][j]);
            }
        }
    }
    return res;
}

matrix matpow(matrix a, int n) {
    const int V = a.size();
    matrix res(V, vector<int>(V, -1));
    for(int i = 0; i < V; ++i) {
        res[i][i] = 0;
    }
    while(n > 0) {
        if(n & 1) res = mat_op(move(res), a);
        a = mat_op(a, a);
        n >>= 1;
    }
    return res;
}


int main() {
    int V, E, K; cin >> V >> E >> K;
    matrix a(V, vector<int>(V, -1));
    for(int i = 0; i < V; ++i) {
        a[i][i] = 0;
    }
    for(int i = 0; i < E; ++i) {
        int u, v, c; cin >> u >> v >> c;
        a[u][v] = max(a[u][v], c);
    }

    auto check = [&] (int cnt) {
        const auto res = matpow(a, cnt);
        for(int i = 0; i < V; ++i) {
            for(int j = 0; j < V; ++j) {
                if(res[i][j] >= K) return true;
            }
        }
        return false;
    };
    int lb = 0, ub = K + 1;
    while(ub - lb > 1) {
        const auto mid = (lb + ub) >> 1;
        (check(mid) ? ub : lb) = mid;
    }

    if(ub == K + 1) {
        cout << -1 << endl;
        return 0;
    }

    cout << ub << endl;
    if(ub <= 100) {
        vector<int> dp(V);
        vector<vector<int>> path(V);
        for(int i = 0; i < V; ++i) {
            path[i] = {i};
        }
        for(int i = 0; i < ub; ++i) {
            vector<int> ndp(V, -1), nfrom(V, -1);
            vector<vector<int>> npath(V);
            for(int from = 0; from < V; ++from) {
                if(dp[from] == -1) continue;
                for(int to = 0; to < V; ++to) {
                    if(from == to || a[from][to] == -1) continue;
                    if(ndp[to] < dp[from] + a[from][to]) {
                        ndp[to] = dp[from] + a[from][to];
                        nfrom[to] = from;
                    }
                }
            }
            for(int j = 0; j < V; ++j) {
                if(nfrom[j] == -1) continue;
                npath[j] = path[nfrom[j]];
                npath[j].push_back(j);
            }
            dp = move(ndp);
            path = move(npath);
        }
        vector<int> ans_path;
        int maxi = -1;
        for(int i = 0; i < V; ++i) {
            if(dp[i] > maxi) {
                maxi = dp[i];
                ans_path = path[i];
            }
        }
        for(int i = 0; i <= ub; ++i) {
            cout << ans_path[i] << " \n"[i == ub];
        }
    }
}
