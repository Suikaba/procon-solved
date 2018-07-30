#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int asum = 0, bsum = 0;
    for(int i = 0; i < n; ++i) {
        int x; cin >> x;
        asum += x;
    }
    for(int i = 0; i < n; ++i) {
        int y; cin >> y;
        bsum += y;
    }
    if(asum >= bsum) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}