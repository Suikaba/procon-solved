// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0368

#include <bits/stdc++.h>
using namespace std;

int main() {
    int w, h; cin >> w >> h;
    char c; cin >> c;
    vector<string> ans(h);
    ans[0] = "+" + string(w - 2, '-') + "+";
    for(int i = 1; i <= h - 2; ++i) {
        ans[i] = "|" + string(w - 2, '.') + "|";
    }
    ans.back() = ans[0];
    ans[h / 2][w / 2] = c;
    for(auto& s : ans) {
        cout << s << endl;
    }
}
