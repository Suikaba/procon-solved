#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> x(n), y(n);
    int xsum = 0, ysum = 0;
    for(int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
        xsum += x[i];
        ysum += y[i];
    }

    if(xsum % 2 == 0 && ysum % 2 == 0) {
        cout << 0 << endl;
    } else {
        for(int i = 0; i < n; ++i) {
            xsum -= x[i], ysum -= y[i];
            xsum += y[i], ysum += x[i];
            if(xsum % 2 == 0 && ysum % 2 == 0) {
                cout << 1 << endl;
                return 0;
            }
            xsum -= y[i], ysum -= x[i];
            xsum += x[i], ysum += y[i];
        }
        cout << -1 << endl;
    }
}
