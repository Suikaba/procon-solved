#include <bits/stdc++.h>
using namespace std;

int main() {
    int k, d; cin >> k >> d;

    function<int(int)> dr = [&dr] (int n) {
        if(n < 10) return n;
        int sn = 0;
        while(n > 0) {
            sn += n % 10;
            n /= 10;
        }
        return dr(sn);
    };

    const int max_s = 10000;
    int sum = (k == 1 ? 0 : 1);
    while(dr(sum) != d && sum < max_s) {
        sum += 1;
    }

    if(sum >= max_s) {
        cout << "No solution" << endl;
        return 0;
    }

    for(int i = 0; i < k; ++i) {
        cout << min(sum, 9);
        sum -= min(sum, 9);
    }
    cout << endl;
}
