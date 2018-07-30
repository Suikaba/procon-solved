
// http://codeforces.com/contest/546/problem/D

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    constexpr int max_n = 5000001;
    vector<bool> is_prime(max_n, true);
    vector<int> prime;
    for(int i = 2; i < max_n; ++i) {
        if(is_prime[i]) {
            prime.push_back(i);
            for(int j = i + i; j < max_n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    vector<ll> sum(max_n, 0);
    for(int i = 2; i < max_n; ++i) {
        int x = i;
        for(auto p : prime) {
            if(p * p > x) break;
            while(x % p == 0) {
                sum[i] += 1;
                x /= p;
            }
        }
        if(x > 1) sum[i] += 1;
    }
    for(int i = 0; i + 1 < max_n; ++i) {
        sum[i + 1] += sum[i];
    }

    int t; cin >> t;
    while(t--) {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d\n", sum[a] - sum[b]);
    }
}
