#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    const int max_v = 1 << 20;

    vector<bool> is_prime(1 << 20, true);
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i < max_v; ++i) {
        if(!is_prime[i]) continue;
        for(int j = i + i; j < max_v; j += i) {
            is_prime[j] = false;
        }
    }

    int n, t = 0;
    while(cin >> n, n) {
        int k = 1;
        while(k * k < n) k++;
        t += 1;
        cout << "Case #" << t << ": ";
        if((n % 100) / 10 == 1) {
            cout << n << "th ";
        } else if(n % 10 == 1) {
            cout << n << "st ";
        } else if(n % 10 == 2) {
            cout << n << "nd ";
        } else if(n % 10 == 3) {
            cout << n << "rd ";
        } else {
            cout << n << "th ";
        }
        cout << "Wilson number is equal to ";
        if(is_prime[n]) {
            cout << n - 1;
        } else if(n == 4) {
            cout << 2;
        } else {
            cout << 0;
        }
        cout << ".\n";
    }
}
