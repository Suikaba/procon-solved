#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> x(n);
    set<int> s;
    for(int i = 0; i < n; ++i) {
        cin >> x[i];
    }
    for(int i = 0; i < m; ++i) {
        int y;
        cin >> y;
        s.insert(y);
    }
    vector<int> ans;
    for(int i = 0; i < n; ++i) {
        if(s.count(x[i])) ans.push_back(x[i]);
    }

    for(int i = 0; i < (int)ans.size(); ++i) {
        cout << ans[i] << " \n"[i + 1 == (int)ans.size()];
    }
}
