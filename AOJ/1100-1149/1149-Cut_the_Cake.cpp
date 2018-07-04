#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1149&lang=jp

struct cake {
    int w, d;
    bool operator<(const cake& other) const {
        return area() < other.area();
    }
    int area() const {
        return w * d;
    }
};

int main() {
    int n, w, d;
    while(cin >> n >> w >> d, n || w || d) {
        vector<cake> cs = {cake{w, d}};
        for(int i = 0; i < n; ++i) {
            int p, s;
            cin >> p >> s;
            p--;
            s %= (cs[p].w + cs[p].d);
            cake c1, c2;
            if(s < cs[p].w) {
                c1 = cake{s, cs[p].d};
                c2 = cake{cs[p].w - s, cs[p].d};
            } else {
                s -= cs[p].w;
                c1 = cake{cs[p].w, s};
                c2 = cake{cs[p].w, cs[p].d - s};
            }
            if(c1.area() > c2.area()) {
                swap(c1, c2);
            }
            cs.push_back(c1), cs.push_back(c2);
            cs.erase(begin(cs) + p);
        }
        sort(begin(cs), end(cs));
        const int m = cs.size();
        for(int i = 0; i < m; ++i) {
            cout << cs[i].area() << " \n"[i + 1 == m];
        }
    }
}
