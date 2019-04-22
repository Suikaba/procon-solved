//#include <bits/stdc++.h>
//using namespace std;

//int main() {
//    int n; cin >> n;
//    vector<vector<int>> sum(2, vector<int>(n + 1));
//    for(int i = 0; i < n; ++i) {
//        int a; cin >> a;
//        for(int j = 0; j < 2; ++j) {
//            sum[j][i + 1] = sum[j][i];
//        }
//        sum[i & 1][i + 1] += a;
//    }
//
//    int ans = 0;
//    for(int i = 0; i < n; ++i) {
//        const int odd = sum[1][i] + (sum[0][n] - sum[0][i + 1]);
//        const int even = sum[0][i] + (sum[1][n] - sum[1][i + 1]);
//        ans += odd == even;
//    }
//
//    cout << ans << endl;
//}


#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define ld long double
#define  P pair<ll,ll>
#define FOR(i,n,m) for(ll i=n; i<(ll)m;i++)
#define FORr(i,m,n) for(ll i=n; i>=(ll)m; i--)
#define FORm(i,m) for(auto i=m.begin();i!=m.end();i++)
#define VEC2(x,a,b) vector<vector<ll>> x = vector<vector<ll>>(a,vector<ll>(b,0))
#define sortAl(v) sort(v.begin(),v.end())
#define sortAlr(v) sort(v.begin(),v.end()); reverse(v.begin(),v.end())
#define cinv(v,n,m) FOR(i,n,m) cin>>v.at(i)
#define coutv(v,n,m) FOR(i,n,m) cout<<v.at(i) <<" "; cout<<endl
#define cout(n) cout<<fixed<<setprecision(n)

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll n;
    cin>>n;
    vector<ll> v(n);
    cinv(v,0,n);

    ll a=0,b=0; // b:even
    FOR(i,1,n){
      if(i%2==0) a += v[i];
      else b += v[i];
    }
    ll res =0;
    if(a == b) res++;
    FOR(i,1,n){
        if(i%2==1){ // even
        b -= v[i];
        b += v[i-1];
      }
      else{
        a -= v[i];
        a += v[i-1];
      }
      if(a==b) res++;
    }
    cout<<res<<endl;
}
