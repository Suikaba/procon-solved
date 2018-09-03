
// http://codeforces.com/contest/558/problem/B

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int n; cin >> n;
    map<int, vector<int>> pos;
    for(int i = 0; i < n; ++i) {
        int a; cin >> a;
        pos[a].push_back(i);
    }

    int max_sz = 0;
    int l = 0, r = 0;
    for(auto& p : pos) {
        if((int)p.second.size() == max_sz) {
            if(r - l > p.second.back() - p.second[0]) {
                l = p.second[0];
                r = p.second.back();
            }
        } else if((int)p.second.size() > max_sz) {
            max_sz = p.second.size();
            l = p.second[0];
            r = p.second.back();
        }
    }

    cout << l + 1 << ' ' << r + 1 << endl;
}
