#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    int f = 0, z = 0;
    for(int i = 0; i < n; ++i) {
        int a; cin >> a;
        if(a == 5) f += 1;
        else       z += 1;
    }
    f = f / 9 * 9;
    if(z == 0) {
        cout << -1 << endl;
        return 0;
    }
    cout << string(f, '5') << (f == 0 ? "0" : string(z, '0')) << endl;
}
