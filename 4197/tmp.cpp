#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b )for(int i = a; i >= b; i--)
using namespace std;
int a[210][512], b[512], p[8], P;
int pow(int a, int b){
	int w = 1;
	for(; b; b >>= 1, a = 1LL * a * a % P) if (b & 1) w = 1LL * w * a % P;
	return w;
}
int pri[200], pl = 0, n;
void prim(){
	rep(i,7,n){
		bool flag = 1;
		rep(j,2,i - 1) if (i % j == 0) {flag = 0; break;}
		if (flag) pri[++pl] = i;
	}
}
int main(){
	scanf("%d%d",&n,&P);
	p[0] = 2, p[1] = 3, p[2] = 5, p[3] = 7, p[4] = 11, p[5] = 13, p[6] = 17, p[7] = 19;
	rep(i,2,n){
		int t = i, t1 = 0;
		rep(j,0,7) if (t % p[j] == 0){
			t1 += 1 << j;
			while (t % p[j] == 0) t /= p[j];
		}
		if (t == 1) a[i][t1]++;
	}
	//a[i][j]：等于i的 质因数集合为j 的数个数
	rep(t,1,n)
		rep(i,0,7)
			rep(j,0,255) 
				if (j >> i & 1) a[t][j] += a[t][j ^ (1 << i)];
	//a[i][j]：等于i的 质因数集合属于j 的数个数
	rep(i,1,n) 
		rep(j,0,255) a[i][j] += a[i - 1][j];
	//a[i][j]: 小于等于i的 质因数集合属于j 的数个数
	rep(i,1,n)
		rep(j,0,255)
			a[i][j] = pow(2, a[i][j]);
	//a[i][j]: 选出若干小于等于i的 质因数集合属于j的 方案数
	rep(j,0,255) b[j] = a[n][j];
	rep(i,0,7)
		rep(j,0,255)
			if (j >> i & 1) b[j] -= b[j ^ (1 << i)], b[j] %= P;
	prim();
	int ans = 0;
	//计算大质数
	rep(i,0,255){
		//左边的小质数组选的是i
		int sum = 1LL * b[i] * a[n][255 ^ i] % P;
		rep(t,1,pl){
			int j = pri[t], k = n / j, ways = (2 * a[k][i] + 2 * a[k][255 ^ i] - 1) % P;
			sum = 1LL * ways * sum % P;
		}
		ans = ans + sum, ans %= P;
	}
	if (ans < 0) ans += P;
	printf("%d\n",ans);
}