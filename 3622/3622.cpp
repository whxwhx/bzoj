#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
const int N = 2000 + 10, M = 1000000000 + 9;
using namespace std;

int a[N], b[N], f[N][N], frac[N], c[N][N], g[N];
int main(){
	int n, k; scanf("%d%d",&n,&k);
	k = (n + k) >> 1;
	rep(i,1,n) scanf("%d",&a[i]);
	rep(i,1,n) scanf("%d",&b[i]);
	sort(a + 1, a + n + 1);
	sort(b + 1, b + n + 1);
	c[0][0] = 1;
	rep(i,1,n){
		c[i][0] = c[i][i] = 1;
		rep(j,1,i-1) c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % M;
	}
	int t = 0;
	f[0][0] = 1;
	rep(i,1,n){
		while (t < n && b[t + 1] < a[i]) t++;
		int ed = min(t, i);
		f[i][0] = f[i - 1][0];
		rep(j,1,ed)
			f[i][j] = (f[i - 1][j] + 1LL * f[i - 1][j - 1] * (t - (j - 1)) % M) % M;
	}
	frac[0] = 1;
	rep(i,1,n) frac[i] = 1LL * frac[i - 1] * i % M;
	rep(i,0,n) f[n][i] = 1LL * f[n][i] * frac[n - i] % M;
	int ans = 0;
	if (0 <= k && k <= n) 
		rep(i, k, n)
			ans = (ans + 1LL * (((i - k) & 1 == 1) ? -1 : 1) * c[i][k] * f[n][i] % M + M) % M;//小心负数
	printf("%d\n",ans);
}