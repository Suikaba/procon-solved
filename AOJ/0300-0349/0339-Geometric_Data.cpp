
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0339

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> ps(n, vector<int>(3));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < 3; ++j) {
            cin >> ps[i][j];
        }
        sort(begin(ps[i]), end(ps[i]));
    }
    sort(begin(ps), end(ps));
    ps.erase(unique(begin(ps), end(ps)), end(ps));
    cout << n - ps.size() << endl;
}
