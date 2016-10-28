#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
int T[100000], a[1000][1000], c[1000][1000], AC[1000], FT[1000];
int main(){
	int n, d, k; cin >>n>>d>>k;
	rep(i,1,n) cin >>T[i];
	rep(i,1,n) rep(j,1,d) cin >>a[i][j];
	if (k == 2){
		rep(i,1,n)
			rep(j,1,n){
				c[i][j] = 0;
				rep(k,1,d)
					c[i][j] = c[i][j] + a[i][k] * a[j][k], c[i][j] %= 2;
			}
		rep(i,1,n){
			AC[i] = 0;
			rep(j,1,n) AC[i] += c[i][j] * T[j], AC[i] %= 2;
		}

		rep(i,1,n) rep(j,1,n) if (i != j) c[i][j] = 1;
		rep(i,1,n){
			FT[i] = 0;
			rep(j,1,n) FT[i] += c[i][j] * T[j], FT[i] %= 2;
		}

		rep(i,1,n) cout <<FT[i]<<' '<<AC[i]<<endl;
	}else{
		rep(i,1,n){
			rep(j,1,n){
				c[i][j] = 0;
				rep(k,1,d)
					c[i][j] = c[i][j] + a[i][k] * a[j][k], c[i][j] %= 3;
				c[i][j] = c[i][j] * c[i][j] % 3;
			}
		}

		rep(i,1,n){
			AC[i] = 0;
			rep(j,1,n) AC[i] += c[i][j] * T[j], AC[i] %= 3;
		}

		rep(i,1,n) rep(j,1,n) if (i != j) c[i][j] = 1;
		rep(i,1,n){
			FT[i] = 0;
			rep(j,1,n) FT[i] += c[i][j] * T[j], FT[i] %= 3;
		}

		rep(i,1,n) cout <<FT[i]<<' '<<AC[i]<<endl;
	}
}