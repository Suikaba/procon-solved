#include <bits/stdc++.h>
using namespace std;

int main(){
	int t; cin >> t;
	while(t--){
		int m, n, p;
		cin >> m >> n >> p;
		if(p == 3){
            if(m % 2 == 1) {
                cout << -1 << endl;
                continue;
            }
            cout << 1 << endl;
			for(int i = 0; i < m; i += 2){
				for(int j = 0; j < n; j++) cout << "(" << i << "," << j << ")\n";
				for(int j = n - 1; j >= 0; j--) cout << "(" << i + 1 << "," << j << ")\n";
			}
		}
		else{
            if(m % 2 == 1 || n % 2 == 1) {
                cout << -1 << endl;
                continue;
            }
            cout << 1 << endl;
			for(int i = 0; i < n; i += 2){
				for(int j = m - 1; j >= 0; j--) cout << "(" << j << "," << i << ")\n";
				for(int j = 0; j < m; j++) cout << "(" << j << "," << i + 1 << ")\n";
			}
		}
	}
}
