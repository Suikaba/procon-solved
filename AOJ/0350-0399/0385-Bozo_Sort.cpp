// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0385

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    auto b = a;
    sort(begin(b), end(b));
    int wrong = 0;
    for(int i = 0; i < n; ++i) {
        wrong += a[i] != b[i];
    }
    int q; cin >> q;
    int ans = (a == b ? 0 : -1);
    for(int i = 0; i < q; ++i) {
        int x, y; cin >> x >> y;
        x--; y--;
        int px = a[x], py = a[y];
        swap(a[x], a[y]);
        if(px != b[x] && a[x] == b[x]) wrong--;
        if(px == b[x] && a[x] != b[x]) wrong++;
        if(py != b[y] && a[y] == b[y]) wrong--;
        if(py == b[y] && a[y] != b[y]) wrong++;
        if(wrong == 0 && ans == -1) {
            ans = i + 1;
        }
    }
    cout << ans << endl;
}
