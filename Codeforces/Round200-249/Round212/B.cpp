#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m; cin >> n >> m;
    vector<int> d(m);
    for(int i = 0; i < m; ++i) {
        cin >> d[i];
    }
    sort(begin(d), end(d));
    if(m == 0) {
        cout << "YES" << endl;
        return 0;
    }

    bool ng = d[0] == 1 || d.back() == n;
    for(int i = 0; i + 2 < m; ++i) {
        ng |= d[i] + 1 == d[i + 1] && d[i + 1] + 1 == d[i + 2];
    }

    cout << (ng ? "NO" : "YES") << endl;
}
