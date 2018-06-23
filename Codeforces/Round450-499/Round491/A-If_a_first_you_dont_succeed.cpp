#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

int main() {
    int a, b, c, n;
    cin >> a >> b >> c >> n;
    if(min(a, b) < c || n - (a + b - c) <= 0) {
        cout << -1 << endl;
    } else {
        cout << n - (a + b - c) << endl;
    }
}
