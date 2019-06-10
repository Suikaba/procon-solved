#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while(T--) {
        int a, b; cin >> a >> b;
        if(a + b == 1) {
            cout << 2 << endl;
        } else {
            cout << 1 << endl;
        }
    }
}