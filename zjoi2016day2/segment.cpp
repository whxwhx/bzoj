#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
const int N = 410, mod = 1000000007;
int a[N], q;
int f[2][N][N], s1[2][N][N], s2[2][N][N], p[N], ans[N], tot[N], n, invtot;
void solve(int l, int r){
	if (l > r) return; int mx = l; rep(i,l,r) if (a[mx] < a[i]) mx = i;
	solve(l, mx - 1); solve(mx + 1, r);
	rep(i,l,r) rep(j,i,r) f[0][i][j] = s1[0][i][j] = s2[0][i][j] = 0; 
	f[0][l][r] = 1; 
	rep(i,l,r) s1[0][i][r] = l - 1; 
	rep(i,l,r) s2[0][l][i] = n - r;
	rep(t,1,q){
		int x = t & 1;
		rep(i,l,r) rep(j,i,r) {
			f[x][i][j] = 0;
			if (i - 1 <= j) f[x][i][j] += s1[x^1][i - 1][j] % mod, f[x][i][j] %= mod;
			if (i <= j + 1) f[x][i][j] += s2[x^1][i][j + 1]  % mod, f[x][i][j] %= mod;
			f[x][i][j] += 1LL * f[x^1][i][j] * ((i * (i - 1)) + (n - j) * (n - j + 1) + (j - i + 1) * (j - i + 2)) / 2 % mod;
			f[x][i][j] = 1LL * f[x][i][j] * invtot % mod;
		}
		rep(i,l,r) rep(j,i,r) s1[x][i][j] = 1LL * f[x][i][j] * (i - 1) % mod;
		rep(i,l,r) rep(j,i,r) s2[x][i][j] = 1LL * f[x][i][j] * (n - j) % mod;
		rep(j,l,r) rep(i,l + 1,j) s1[x][i][j] += s1[x][i - 1][j], s1[x][i][j] %= mod;
		rep(i,l,r) dep(j,r - 1,i) s2[x][i][j] += s2[x][i][j + 1], s2[x][i][j] %= mod;
	}
	rep(i,l,r) tot[i] = 0; tot[l] = 1;
	rep(i,l,r) rep(j,i,r) {
		tot[i] -= f[q&1][i][j], tot[i] %= mod;
		tot[j + 1] += f[q&1][i][j], tot[j + 1] %= mod;
	}
	rep(i,l + 1,r) tot[i] = (tot[i] + tot[i - 1]) % mod;
	rep(i,l,r) ans[i] += 1LL * (p[i] - tot[i]) * a[mx] % mod, ans[i] %= mod, p[i] = tot[i];
}
int pw(int a, int b) {int w = 1; for(;b;b>>=1,a=1LL*a*a%mod)if(b&1)w=1LL*w*a%mod;return w;}
int main(){
	scanf("%d%d",&n,&q); rep(i,1,n) scanf("%d",&a[i]), p[i] = 1;
	invtot = pw(n * (n + 1) / 2, mod - 2); solve(1, n);  int tmp = pw(n * (n + 1) / 2, q);
	rep(i,1,n) ans[i]=1LL*ans[i]*tmp % mod, ans[i] = (ans[i] + mod) % mod;
	rep(i,1,n) printf("%d%s",ans[i],(i==n)?"\n":" "); return 0;
}