#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 510, mod = 1000000000 + 7;
int a[N], f[N][N], mxa[N][N], s0[N][N], s1[N][N], s[N];
int main(){
	int n, k; scanf("%d%d",&n,&k); rep(i,1,n) scanf("%d",&a[i]);
	rep(l,1,n){
		mxa[l][l] = l;
		rep(r,l+1,n) if (a[r] > a[ mxa[l][r - 1] ]) mxa[l][r] = r; else mxa[l][r] = mxa[l][r - 1];
	}
	int ans = 1; s1[1][1] = 1;
	rep(cnt,1,k){
		rep(i,1,n) s[i] = (s[i] + s[i - 1]) % mod;
		rep(l,1,n) rep(r,1,n) s1[l][r] += s1[l][r - 1], s1[l][r] %= mod;
		rep(l,1,n) rep(r,1,n) s1[l][r] += s1[l - 1][r], s1[l][r] %= mod;
		rep(l,1,n) rep(r,l+1,n) f[l][r] = (s1[l][mxa[l][r]] + s[l - 1]) % mod;
		memset(s1, 0, sizeof(s1)); memset(s, 0, sizeof(s));
		rep(l,1,n) rep(r,l+1,n){
			int mx = mxa[l][r];
			if (l == mx) 
				f[l][r] += (s0[l - 1][r - 1] - s0[l - 1][mx - 1]) % mod, f[l][r] %= mod;
			if (r == mx){
				s1[l + 1][r + 1] += f[l][r], s1[l + 1][r + 1] %= mod;
				s1[mx + 1][r + 1] -= f[l][r], s1[mx + 1][r + 1] %= mod;
			}
			s[r] += f[l][r], s[r] %= mod;
			ans = (ans + f[l][r]) % mod;
		}
		memset(s0, 0, sizeof(s0));
		rep(l,1,n) rep(r,l+1,n) s0[mxa[l][r]][r] += f[l][r], s0[mxa[l][r]][r] %= mod;
		rep(l,1,n) rep(r,1,n) s0[l][r] += s0[l][r - 1], s0[l][r] %= mod;
		rep(l,1,n) rep(r,1,n) s0[l][r] += s0[l - 1][r], s0[l][r] %= mod;
	}
	if (ans < 0) ans += mod;
	printf("%d\n",ans);
	return 0;
}