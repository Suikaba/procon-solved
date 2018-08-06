#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    const int n = s.size();
    int mini_a = 1e6, maxi_a = -1, mini_b = 1e6, maxi_b = -1;
    for(int i = 0; i + 1 < n; ++i) {
        if(s[i] == 'A' && s[i + 1] == 'B') {
            mini_a = min(mini_a, i);
            maxi_a = i;
        }
        if(s[i] == 'B' && s[i + 1] == 'A') {
            mini_b = min(mini_b, i);
            maxi_b = i;
        }
    }
    if(maxi_a == -1 || maxi_b == -1) {
        cout << "NO" << endl;
    } else {
        if(abs(maxi_a - mini_b) >= 2 || abs(maxi_b - mini_a) >= 2) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}
