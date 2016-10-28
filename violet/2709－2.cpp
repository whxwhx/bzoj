#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef long long LL;
LL f[65][2], g[65], pw[65];
int t[20];
int main(){
	LL n; int b;
	cin >>b>>n;
	if (n < b){
		int r = 1, ans = 0;
		rep(i,1,n) ans += i * r, r = -r;
		printf("%d\n",ans);
		return 0;
	}
	LL m = n;
	pw[0] = 1;
	rep(i,1,64) {
		t[i] = m % b, m /= b;
		if (!m) {m = i;break;}
		pw[i] = pw[i - 1] * b;
	}
	f[0][0] = f[0][1] = 0;
	rep(i,0,b - 1) if (i & 1) f[1][1] += i; else f[1][0] -= i;
	rep(i,2,m - 1){
		int r = 1;
		rep(j,0,b - 1){
			f[i][0] += r * (-f[i - 1][0] + j * (pw[i - 1] + 1) / 2);
			int r1;
			if (i & 1) r1 = -1; else r1 = 1;
			f[i][1] += r * (f[i - 1][1] + r1 * j *pw[i - 1] / 2);
			if (i & b & 1) r *= -1;
		}
		r = 1;
		rep(j,1,b - 1){
			g[i] += r * (-f[i - 1][0] + j * (pw[i - 1] + 1) / 2);
			int r1;
			if (i & 1) r1 = -1; else r1 = 1;
			g[i] += r * (f[i - 1][1] + r1 * j * pw[i - 1] / 2);
			if (i & b & 1) r *= -1;
		}
	}

	LL ans = 0;
	int r, tot;
	if (b & 1) r = -1; else r = 1;
	bool flag = false;
	dep(i,m - 1,1)if (t[i] || flag){
		if (!flag) tot = i;
		//000000xxxxx
		if (flag){
			int r;
			if ((b & 1) && i > 1) r = -1; else r = 1;
			ans += r * g[i];
		}
		//nnnnnnjxxxx
		if (flag){
			rep(j,0,t[i] - 1){
				if ((tot - i) & 1) ans -= r * g[i - 1]; else ans += r * g[i - 1];	
				if (b & i & 1) r = -r;
				ans += n;//?
			}
		} else {
			rep(j,1,t[i] - 1){
				if ((tot - i) & 1) ans -= r * g[tot]; else ans += r * g[i - 1];
				if (b & i & 1) r = -r;
				ans += n;//?
			}
		}
		flag = 1;
	}

	ans = -ans;
	cout <<ans<<endl;
}