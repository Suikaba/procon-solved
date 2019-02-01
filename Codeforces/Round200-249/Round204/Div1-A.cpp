#include <bits/stdc++.h>
using namespace std;

// n <= 2000 だけど O(n) のほうが簡単では？

int main() {
    int n; cin >> n;
    int sum = 0, cnt = 0;
    for(int i = 0; i < 2 * n; ++i) {
        int a, b; scanf("%d.%d", &a, &b);
        if(b != 0) {
            sum += 1000 - b;
            cnt += 1;
        }
    }
    int zero = 2 * n - cnt, remain = n;
    while(sum >= 1000 && remain > 0 && cnt > 0) { // use not zero
        remain -= 1;
        cnt -= 1;
        sum -= 1000;
    }
    if(cnt > 0 && remain > 0 && sum > 1000 - sum) { // sum < 1000
        cnt -= 1, remain -= 1;
        sum -= 1000;
    }
    remain -= min(remain, zero);
    while(remain > 0) {
        sum -= 1000;
        remain--;
    }
    sum = abs(sum);

    printf("%d.%03d\n", sum / 1000, sum % 1000); // 小数点以下3桁表示を完全に失念してた
}
