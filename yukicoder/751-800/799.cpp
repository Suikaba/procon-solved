#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b, c, d; cin >> a >> b >> c >> d;
    int ans = 0;
    for(int x = a; x <= b; ++x) {
        for(int y = c; y <= d; ++y) {
            ans += x != y;
        }
    }
    cout << ans << endl;
}