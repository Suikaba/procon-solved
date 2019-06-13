#include <bits/stdc++.h>
using namespace std;

int main() {
    int h, a, b; cin >> h >> a >> b;
    int ans = 0;
    for(int x = a; x <= b; ++x) {
        ans += h % x == 0;
    }
    cout << ans << endl;
}
