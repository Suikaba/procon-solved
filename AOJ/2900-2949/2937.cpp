#include <bits/stdc++.h>
using namespace std;

int main() {
    int h, w, a, b; cin >> h >> w >> a >> b;
    const int x = h % a, y = w % b;
    cout << x * w + y * h - x * y << endl;
}