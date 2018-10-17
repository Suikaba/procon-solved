#include<bits/stdc++.h>
using namespace std;

int main() {
    cout << fixed << setprecision(10);
    int a, b; cin >> a >> b;
    if(b > a) {
        cout << -1 << endl;
    } else {
        const int k = (a + b) / (2 * b);
        const int pre_x = (2 * k - 1) * b;
        cout << b + (double)(a - pre_x) / ((pre_x + b - 1) / b + 1) << endl;
    }
}
