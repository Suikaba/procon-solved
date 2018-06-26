#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0321

class union_find {
public:
    union_find(int n) : par(n, -1) {}
    int root(int x) { return par[x] < 0 ? x : par[x] = root(par[x]); }
    bool same(int x, int y) {
        return root(x) == root(y);
    }
    void unite(int x, int y) {
        x = root(x), y = root(y);
        if(x == y) return;
        if(par[x] > par[y]) swap(x, y);
        par[x] += par[y];
        par[y] = x;
    }
private:
    vector<int> par;
};

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    union_find uf(n);
    vector<int> club(n, -1); // leader -> club id
    int ans = 0;
    for(int i = 0; i < k; ++i) {
        int type; cin >> type;
        if(type == 1) { // same club
            int a, b;
            cin >> a >> b;
            a--; b--;
            int ra = uf.root(a), rb = uf.root(b);
            if(club[ra] == -1 || club[rb] == -1 || club[ra] == club[rb]) {
                uf.unite(a, b);
                club[uf.root(a)] = max(club[ra], club[rb]);
            } else {
                ans = i + 1;
                break;
            }
        } else {
            int c, x;
            cin >> c >> x;
            c--; x--;
            if(club[uf.root(c)] == -1 || club[uf.root(c)] == x) {
                club[uf.root(c)] = x;
            } else {
                ans = i + 1;
                break;
            }
        }
    }
    cout << ans << endl;
}
