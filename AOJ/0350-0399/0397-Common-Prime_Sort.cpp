#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

class union_find {
public:
    union_find(int n) : par(n, -1) {}

    int root(int x) {
        return par[x] < 0 ? x : par[x] = root(par[x]);
    }

    void unite(int x, int y) {
        x = root(x), y = root(y);
        if(x == y) return;
        if(par[x] < par[y]) swap(x, y);
        par[x] += par[y];
        par[y] = x;
    }

private:
    vector<int> par;
};

int main() {
    int n; cin >> n;
    vector<int> a(n), id(1 << 17, -1);
    union_find uf(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        int tmp = a[i];
        for(int x = 2; x * x <= tmp; ++x) {
            if(tmp % x == 0) {
                while(tmp % x == 0) tmp /= x;
                if(id[x] != -1) {
                    uf.unite(i, id[x]);
                }
                id[x] = i;
            }
        }
        if(tmp > 1) {
            if(id[tmp] != -1) {
                uf.unite(i, id[tmp]);
            }
            id[tmp] = i;
        }
    }

    map<int, vector<int>> vals, idxs;
    for(int i = 0; i < n; ++i) {
        idxs[uf.root(i)].push_back(i);
        vals[uf.root(i)].push_back(a[i]);
    }
    for(auto& p : vals) {
        sort(begin(p.second), end(p.second));
        const auto& ids = idxs[p.first];
        for(int i = 0; i < (int)p.second.size(); ++i) {
            a[ids[i]] = p.second[i];
        }
    }

    cout << is_sorted(begin(a), end(a)) << endl;
}
