#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

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
    int k;
    while(cin >> k) {
        map<tuple<int, int, int>, int> idx1;
        map<pii, int> idx2;
        vector<pii> es1, es2;
        for(int i = 0; i < k; ++i) {
            int x1, y1, z1, x2, y2, z2;
            cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            if(idx1.count(make_tuple(x1, y1, z1)) == 0) {
                const int id = idx1.size();
                idx1[make_tuple(x1, y1, z1)] = id;
            }
            if(idx1.count(make_tuple(x2, y2, z2)) == 0) {
                const int id = idx1.size();
                idx1[make_tuple(x2, y2, z2)] = id;
            }
            if(idx2.count(make_pair(x1, y1)) == 0) {
                const int id = idx2.size();
                idx2[make_pair(x1, y1)] = id;
            }
            if(idx2.count(make_pair(x2, y2)) == 0) {
                const int id = idx2.size();
                idx2[make_pair(x2, y2)] = id;
            }
            const int id11 = idx1[make_tuple(x1, y1, z1)], id12 = idx1[make_tuple(x2, y2, z2)];
            const int id21 = idx2[make_pair(x1, y1)], id22 = idx2[make_pair(x2, y2)];
            if(id11 != id12) {
                es1.emplace_back(min(id11, id12), max(id11, id12));
            }
            if(id21 != id22) {
                es2.emplace_back(min(id21, id22), max(id21, id22));
            }
        }
        sort(begin(es1), end(es1));
        es1.erase(unique(begin(es1), end(es1)), end(es1));
        sort(begin(es2), end(es2));
        es2.erase(unique(begin(es2), end(es2)), end(es2));

        bool ans1 = false, ans2 = false;
        union_find uf1(idx1.size()), uf2(idx2.size());
        for(auto& e : es1) {
            ans1 |= !uf1.unite(e.first, e.second);
        }
        for(auto& e : es2) {
            ans2 |= !uf2.unite(e.first, e.second);
        }

        if(ans1) {
            cout << "True closed chains" << endl;
        } else {
            cout << "No true closed chains" << endl;
        }
        if(ans2) {
            cout << "Floor closed chains" << endl;
        } else {
            cout << "No floor closed chains" << endl;
        }
    }
}