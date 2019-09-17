#include <bits/stdc++.h>
using namespace std;

tuple<int, int, int> ans[10000][12][31];

constexpr int day[13] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool isuruu1(int y) {
    return y % 400 == 0 || (y % 100 != 0 && y % 4 == 0);
}
bool kuso(int y) {
    return y % 4 == 0;
}

tuple<int, int, int> next(int y, int m, int d, bool f) {
    int ub = day[m];
    if(m == 2 && ((f && isuruu1(y)) || (!f && kuso(y)))) {
        ++ub;
    }
    d += 1;
    if(d == ub + 1) {
        m += 1;
        d = 1;
    }
    if(m == 13) {
        y += 1;
        m = 1;
    }
    return make_tuple(y, m, d);
}

int main() {
    {
        int y1 = 1582, m1 = 10, d1 = 4, y2 = y1, m2 = m1, d2 = 15;
        ans[y1][m1][d1] = make_tuple(y2, m2, d2);
        while(true) {
            tie(y1, m1, d1) = next(y1, m1, d1, false);
            tie(y2, m2, d2) = next(y2, m2, d2, true);
            if(y1 == 10000) break;
            ans[y1][m1][d1] = make_tuple(y2, m2, d2);
        }
    }
    int y, m, d;
    while(~scanf("%d-%d-%d", &y, &m, &d)) {
        int yy, mm, dd; tie(yy, mm, dd) = ans[y][m][d];
        printf("%04d-%02d-%02d\n", yy, mm, dd);
    }
}
