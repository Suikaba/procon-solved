#include <bits/stdc++.h>
using namespace std;

int main() {
    int c, d;
    while(cin >> c >> d, c != 0 && d != 0) {
        cout << min({c * 30 + 40 * d, 35 * c + 30 * d, 40 * c + 20 * d}) << endl;
    }
}