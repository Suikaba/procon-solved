#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    auto s = to_string(n);
    reverse(begin(s), end(s));
    const int m = s.size();
    for(int i = 0; i < m; ++i) {
        int d = s[i] - '0';
        if(d >= 5) {
            cout << "-O|";
            d -= 5;
        } else {
            cout << "O-|";
        }
        for(int j = 0; j < d; ++j) cout << "O";
        cout << "-";
        for(int j = 0; j < 4 - d; ++j) {
            cout << "O";
        }
        cout << endl;
    }
}
