#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 310, mod = 1000000000 + 7;
int a[N], b[N], f[N][N][N]; //前i个袋鼠，选了j个，k个必须选的
int main(){
	int n; scanf("%d",&n);
	rep(i,1,n) scanf("%d%d",&a[i],&b[i]);
	sort(a + 1, a + n + 1); sort(b + 1, b + n + 1);
	f[0][0][0] = 1;
	int t = 0;
	rep(i,1,n) {
		while (t + 1 <= n && a[t + 1] < b[i]) t++;
		//不选
		rep(j,0,t) rep(k,0,t) ( f[i][j][t - j] += f[i - 1][j][k] ) %= mod;
		//选必须选的
		rep(j,0,t) rep(k,0,t) ( f[i][j + 1][k - 1] += f[i - 1][j][k] * 1LL * k % mod) %= mod;
		//不选必须选的
		rep(j,0,t) rep(k,0,t) ( f[i][j + 1][k] += f[i - 1][j][k] * 1LL * (t - j - k) % mod) %= mod;
	}
	int ans = 0; 
	rep(j,0,n) ( ans += f[n][j][0] ) %= mod;
	printf("%d\n",ans);
	return 0;
}