#include <bits/stdc++.h>
using namespace std;

int main() {
    int x, y, z;
    while(cin >> x >> y >> z) {
        const int a = y * x;
        const int b = z - y;
        const int g = __gcd(y * x, z - y);
        cout << (a / g) << '/' << (b / g) << endl;
    }
}
