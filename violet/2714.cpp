#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
typedef long long LL;
LL f[65][2], g[65], g1[65][10], ;
int t[20];
int main(){
	LL n; int b;
	cin >>n>>b;
	LL m = n;
	rep(i,1,64) t[i] = m % b, m /= b;
	
	f[0][0] = f[0][1] = 0;
	rep(i,1,64){
		int r = 1;
		rep(j,0,b - 1){
			f[i][0] += r * (-f[i - 1][0] + j * (b + 1) / 2);
			int r1;
			if (i & 1) r1 = -1; else r1 = 1;
			f[i][1] += r * (f[i - 1][1] + r1 * j * b / 2);
			if (i & b & 1) r *= -1;
		}
		r = 1;，
		rep(j,1,b - 1){
			g[i] += r * (-f[i - 1][0] + j * (b + 1) / 2);
			int r1;
			if (i & 1) r1 = -1; else r1 = 1;
			g[i] += r * (f[i - 1][1] + r1 * j * b / 2);
			if (i & b & 1) r *= -1;
		}
		rep(j,0,b - 1){
			g1[i][j] = (-f[i - 1][0] + j * (b + 1) / 2);
			int r1;
			if (i & 1) r1 = -1; else r1 = 1;
			g1[i][j] += (f[i - 1][1] + r1 * j * b / 2);
		}

	}

	LL ans = 0;
	int t;
	dep(i,64,1)if (t[i] || flag){
		//000000xxxxx
		if (flag){
			int r;
			if ((b & 1) && i > 1) r = -1; else r = 1;
			ans += r * g[i];
		}
		//nnnnnnxxxxx
		if (flag){
			int r;
			if (b & 1) r = -1; else r = 1;
			rep(j,0,t[i] - 1){ 
				
			}
		} else {
			rep(j,1,t[i] - 1){

			}
		}
		flag = 1;
	}

	ans = -ans;
	cout <<ans<<endl;
}