#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1172&lang=jp

// さすがにはい．

int main() {
    constexpr int max_n = 1 << 22;
    vector<bool> is_prime(max_n, true);
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i < max_n; ++i) {
        if(is_prime[i]) {
            for(int j = i + i; j < max_n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    int n;
    while(cin >> n, n) {
        cout << count(begin(is_prime) + n + 1, begin(is_prime) + 2 * n + 1, true) << endl;
    }
}
