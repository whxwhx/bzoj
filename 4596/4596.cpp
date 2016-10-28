#include <iostream>
#include <cstdio>
#include <cmath>
#include <set>
#include <map>
#include <queue>
#include <bitset>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define Rep(i,a) for(int i = 0; i < (a); i++)
#define rep(i,a,b) for(int i = (a); i <= (b); i++)//(a)!
#define dep(i,a,b) for(int i = (a); i >= (b); i--)
#define ab(a) ((a) > 0 ? (a) : -(a))
#define mp(a,b) make_pair((a),(b))
#define pb(a) push_back(a)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
const int N = 18, M = N * N * N, mod = 1000000000 + 7;
int a[M], b[M], c[M], l = 0;
int m1(int a) { return (a & 1) ? -1 : 1; }
int f[N][N], n;
int pw(int a, int b) { int w = 1; for(;b;b >>= 1, a = 1LL * a * a % mod) if (b & 1) w = 1LL * w * a % mod; return w; }
int calc(int S){
	memset(f, 0, sizeof(f));
	rep(i,1,l) if (S >> (c[i] - 1) & 1) f[a[i]][b[i]]--, f[b[i]][a[i]]--, f[b[i]][b[i]]++, f[a[i]][a[i]]++;
	int w = 1;
	rep(i,1,n - 1){
		int t = i; rep(j,i+1,n - 1) if (f[j][i]) t = j; if (!f[t][i]) return 0;//这时候不能continue，而是线性相关了，应该return 0;
		if (t != i) { w = -w; rep(j,1,n - 1) swap(f[i][j], f[t][j]); }
		int inv = pw(f[i][i], mod - 2); w = 1LL * w * f[i][i] % mod;
		rep(j,i,n - 1) f[i][j] = 1LL * f[i][j] * inv % mod;
		rep(j,i+1,n-1){
			int F = f[j][i];
			rep(k,i,n) f[j][k] -= 1LL * f[i][k] * F % mod, f[j][k] %= mod;
		}
	}
	return w;
}
int main(){
	scanf("%d",&n); 
	rep(i,1,n - 1){
		int m; scanf("%d",&m);
		rep(j,1,m) { int x, y; scanf("%d%d",&x,&y); l++, a[l] = x, b[l] = y, c[l] = i; }
	}
	int m = 1 << (n - 1), ans = 0;
	rep(i,0,m - 1) {
		int cnt = 0; rep(j,0,n-2) if (i >> j & 1) cnt++;
		ans += m1(n - 1 - cnt) * calc(i); ans %= mod;
	}
	if (ans < 0) ans += mod; printf("%d\n",ans);
	return 0;
}