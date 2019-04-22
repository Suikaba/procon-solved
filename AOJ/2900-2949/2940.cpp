#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

enum {
    No,
    Near,
    Yes
};

int query(int n) {
    cout << n << endl;
    string r; cin >> r;
    if(r == "Yes") return Yes;
    else if(r == "No") return No;
    return Near;
}

int main() {
    int n, k; cin >> n >> k;

    vector<pii> es;
    function<void(int, int)> create = [&] (int i, int w) {
        if(i >= n || w <= 1) return;
        for(int j = i + 1; j < min(i + w, n); ++j) {
            es.emplace_back(i + 1, j + 1);
        }
        int tw = w / 2;
        int ii = i + 1;
        while(tw >= 2) {
            create(ii, tw);
            ii += tw;
            tw = (tw + 1) / 2;
        }
    };
    create(0, n);
    cout << es.size() << endl;
    for(auto const& p : es) {
        cout << p.first << " " << p.second << endl;
    }

    while(k--) {
        function<int(int, int)> solve = [&] (int i, int w) {
            auto r = query(i + 1);
            if(r == Yes) return Yes;
            if(r == No) return No;
            int ii = i + 1, tw = w / 2;
            while(tw >= 1) {
                r = solve(ii, tw);
                if(r == Yes) return Yes;
                ii += tw;
                tw = (tw + 1) / 2;
            }
            assert(false);
        };
        solve(0, n);
    }
}