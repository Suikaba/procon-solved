#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b, c; cin >> a >> b >> c;
    const int x = (a + b - c) / 2, y = (-a + b + c) / 2, z = (a - b + c) / 2;
    if(x + y == b && y + z == c && z + x == a && x >= 0 && y >= 0 && z >= 0) {
        cout << x << ' ' << y << ' ' << z << endl;
    } else {
        cout << "Impossible" << endl;
    }
}
