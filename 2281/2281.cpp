#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
const int N = 30100, mod = 1000000000 + 7;
int f[16][N], fac[N], inv[N];
int pw(int a, int b){ int w = 1; for(;b;b >>= 1, a = 1LL * a * a % mod) if (b & 1) w = 1LL * w * a % mod; return w; }
int C(int n, int m) { return 1LL * fac[n] * inv[n - m] % mod * 1LL * inv[m] % mod; }
int main(){
	int n, k, d; scanf("%d%d%d",&n,&k,&d);
	fac[0] = 1; rep(i,1,N - 10) fac[i] = fac[i - 1] * 1LL * i % mod;
	inv[N - 10] = pw(fac[N - 10], mod - 2); dep(i,N - 11,0) inv[i] = inv[i + 1] * 1LL * (i + 1) % mod;

	n -= k, k >>= 1;
	f[0][0] = 1;
	rep(i,1,15){
		rep(j,0,n) if (f[i - 1][j])
			for(int t = 0; t <= k; t += d + 1) {
				int x = j + (1 << (i - 1)) * t;
				if (x <= n)  
					f[i][x] += f[i - 1][j] * 1LL * C(k, t) % mod, f[i][x] %= mod;
			}
	}

	int ans = C(n + (k << 1), (k << 1));
	rep(i,0,n) ans -= 1LL * C(n - i + k, k) * f[15][i] % mod, ans %= mod;
	if (ans < 0) ans += mod;
	printf("%d\n",ans);
	return 0;
}