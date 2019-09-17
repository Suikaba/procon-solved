#include <bits/stdc++.h>
using namespace std;

class union_find {
public:
    union_find(int n) : par(n, -1) {}

    int root(int x) {
        return par[x] < 0 ? x : par[x] = root(par[x]);
    }

    bool unite(int x, int y) {
        x = root(x), y = root(y);
        if(x == y) return false;
        if(par[x] < par[y]) swap(x, y);
        par[x] += par[y];
        par[y] = x;
        return true;
    }

private:
    vector<int> par;
};

int main() {
    int n;
    while(cin >> n) {
        vector<vector<int>> cnt(n, vector<int>(10));
        for(int i = 0; i < n; ++i) {
            string s; cin >> s;
            for(auto c : s) {
                cnt[i][c - '0'] += 1;
            }
        }

        union_find uf(n);
        int ans = n;
        for(int i = 0; i < n; ++i) {
            for(int j = i + 1; j < n; ++j) {
                bool check = true;
                for(int k = 0; k < 10; ++k) {
                    check &= (cnt[i][k] == 0 && cnt[j][k] == 0) || (cnt[i][k] > 0 && cnt[j][k] > 0);
                }
                if(check) {
                    ans -= uf.unite(i, j);
                }
            }
        }
        cout << ans << endl;
    }
}
