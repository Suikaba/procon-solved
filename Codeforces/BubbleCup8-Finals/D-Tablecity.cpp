// http://codeforces.com/contest/575/problem/D

#include <bits/stdc++.h>
using namespace std;

// x's parity

int main() {
    cout << 2001 << endl;
    for(int i = 1; i <= 1000; ++i) {
        cout << i << ' ' << 1 << ' ' << i << ' ' << 2 << endl;
    }
    cout << 1 << ' ' << 1 << ' ' << 2 << ' ' << 1 << endl;
    for(int i = 1; i <= 1000; ++i) {
        cout << i << ' ' << 1 << ' ' << i << ' ' << 2 << endl;
    }
}
