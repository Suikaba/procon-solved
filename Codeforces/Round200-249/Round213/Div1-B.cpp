#include <bits/stdc++.h>
using namespace std;

// tag: DP, 貪欲

// 問題概要
// n 個の商品とそれぞれの価格 c[i] が与えられる。各商品は1つずつしかない。
// また正整数 d が定められている。
// 最初どの商品も手元にない。
// 一日1回だけ、今持っている集合の部分集合と、以下の条件を満たす任意の商品の集合とを交換することができる。
// ・交換前の商品の価格の合計 x と、交換後の商品の価格の合計 y について、y - x <= d が成り立つ
// ・交換する2つの商品集合に、同じ商品が含まれない
// この条件下で、最終的に手にすることができる価格の最大値を求めよ。
// また、その最大値を達成するために必要な最小日数も求めよ。
// n <= 50, c[i], d <= 10^4

// 解法
// 明らかに、交換する商品集合に共通商品があっても変わらない（なんで条件にあるのか謎なんだけど誤読？）。
// 各商品集合を高々1個用いて作れる価値の合計値は簡単な dp で求まる。
// あとは 0 からはじめて、現時点から距離 d 以内にある最大値を貪欲にとっていくのが最適。
// これで到達可能な最大値が最大価値なのは明らかで、最短日数なのも明らか（行ける範囲を最も広げる方法だから当然）。
// 計算量は O(n * (sum c[i]))

int main() {
    int n, d; cin >> n >> d;
    vector<int> c(n);
    for(int i = 0; i < n; ++i) {
        cin >> c[i];
    }
    const int sum = accumulate(begin(c), end(c), 0);

    vector<bool> can_make(sum + 1);
    can_make[0] = true;
    for(int i = 0; i < n; ++i) {
        for(int j = sum - c[i]; j >= 0; --j) {
            can_make[j + c[i]] = can_make[j + c[i]] | can_make[j];
        }
    }
    int max_v = 0, day = 0;
    while(true) {
        int nmax = max_v;
        for(int i = max_v + 1; i <= sum && i <= max_v + d; ++i) {
            if(can_make[i]) {
                nmax = i;
            }
        }
        if(nmax == max_v) break;
        max_v = nmax;
        ++day;
    }

    cout << max_v << ' ' << day << endl;
}
