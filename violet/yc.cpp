#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef long long LL;
const LL inf = 1000000000000000001LL;
#define REP() rep(i1,0,cnt[1]) if (n / pw[1][i1]) rep(i2,0,cnt[2]) if (n / pw[1][i1] / pw[2][i2]) rep(i3,0,cnt[3]) if (n / pw[1][i1] / pw[2][i2] / pw[3][i3]) rep(i4,0,cnt[4]) if (n / pw[1][i1] / pw[2][i2] / pw[3][i3] / pw[4][i4])
const int N = 64; 
int cnt[5]; 
LL f[20][66062]; 
int al[64][42][27][24], l;
LL pw[5][64];
int a[11][6], p[6];
void init(){
	pw[1][0] = pw[2][0] = pw[3][0] =  pw[4][0] = 1;
	rep(i,1,4) rep(j,1,cnt[i]) pw[i][j] = pw[i][j - 1] * p[i];

	LL n = inf;
	int l = 0;
	REP() {
		al[i1][i2][i3][i4] = ++l;
	}
	f[0][al[0][0][0][0]] = 1;
	rep(i,1,18) {
		REP() rep(j,1,9){
			int t1 = i1 + a[j][1], t2 = i2 + a[j][2], t3 = i3 + a[j][3], t4 = i4 + a[j][4];
			f[i][al[t1][t2][t3][t4]] += f[i - 1][al[i1][i2][i3][i4]];
		}
	}

}
int t[20];
LL calc(LL n){
	if (n == 0) return 0; else{
		LL ans = 0;	
		REP(){
			LL tmp = n / pw[1][i1] / pw[2][i2] / pw[3][i3] / pw[4][i4] + 1;
			int m = 0;
			rep(ii,1,19) {
				t[ii] = tmp % 10, tmp /= 10;
				if (!tmp) {m = ii;break;}
			}
			dep(i,m - 1,1) ans += f[i][al[i1][i2][i3][i4]];
			
			int t1 = i1, t2 = i2, t3 = i3, t4 = i4;
			dep(i,m,1){
				if (t1 < 0 || t2 < 0 || t3 < 0 || t4 < 0) break;
				rep(j,1,t[i] - 1){
					int tt1 = t1 - a[j][1], tt2 = t2 - a[j][2], tt3 = t3 - a[j][3], tt4 = t4 - a[j][4];
					if (tt1 >= 0 && tt2 >= 0 && tt3 >= 0 && tt4 >= 0) ans += f[i - 1][al[tt1][tt2][tt3][tt4]];
				}
				t1 -= a[t[i]][1], t2 -= a[t[i]][2], t3 -= a[t[i]][3], t4 -= a[t[i]][4];
				if (!t[i]) break;//!数位dp中一定要注意i前面和n相同的那些位是否合法
			}
		}
		return ans;
	}
}
int main(){
	cnt[1] = 60, cnt[2] = 38, cnt[3] = 26, cnt[4] = 22;
	p[1] = 2, p[2] = 3, p[3] = 5, p[4] = 7;
	rep(i,1,9){
		int t = i;
		rep(j,1,4) while (t % p[j] == 0) t /= p[j], a[i][j]++;
	}
	LL A, B; scanf("%lld%lld",&A,&B);
	init();
	printf("%lld\n",calc(B) - calc(A - 1));
}