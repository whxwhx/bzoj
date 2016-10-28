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
const int N = 2010, M = 2010, mod = 1000000007;
int s[N], r[N], g[N], b[N], C[M][M];

pair<int, int> a[N * 2];

int f[2][110][110], cnt = 0, t;

int vis[N];

void dp(int a, int b, int x){
	rep(i,a,b){
		t ^= 1; rep(j,0,100) rep(k,0,100) f[t][j][k] = 0; 
		rep(j,0,r[x]) rep(k,0,g[x]){
			f[t][j][k] = f[t^1][j][k];
			if (k > 0) f[t][j][k] = (f[t][j][k] + f[t^1][j][k - 1]) % mod;
			if (j > 0) f[t][j][k] = (f[t][j][k] + f[t^1][j - 1][k]) % mod;
		}
	}
}

int main(){
	C[0][0] = 1;
	rep(i,1,M - 10) {
		C[i][0] = C[i][i] = 1;
		rep(j,1,i - 1) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
	}

	int n; scanf("%d",&n);
	rep(i,1,n) scanf("%d",&s[i]);
	rep(i,1,n) scanf("%d",&r[i]);
	rep(i,1,n) scanf("%d",&g[i]);
	rep(i,1,n) scanf("%d",&b[i]);

	int l = 0;	
	rep(i,1,n) {
		a[++l] = mp((s[i] << 1) | 1,i);
		a[++l] = mp((s[i] + r[i] + g[i] + b[i]) << 1, i);
	}
	sort(a + 1, a + l + 1);
	rep(i,1,l) a[i].first >>= 1;

	t = 0; int x = 0; f[0][0][0] = 1;
	rep(i,1,l) if (!x){
		x = a[i].second; vis[x] = a[i].first;
	} else if (a[i].second == x) {
		dp(vis[x], a[i].first - 1, x);
		int tmp = f[t][r[x]][g[x]]; rep(j,0,100) rep(k,0,100) f[t][j][k] = 0; 
		f[t][0][0] = tmp; x = 0;
	} else {
		dp(vis[x], a[i].first - 1, x);
		if (a[i + 1].second == x){
			int len = a[i + 1].first - a[i].first, x1 = a[i].second;
			
			t ^= 1; rep(j,0,100) rep(k,0,100) f[t][j][k] = 0; 
			
			rep(j,0,r[x]) rep(k,0,g[x]) if (j <= r[x1] && k <= g[x1] && j + k <= len)
				f[t][j][k] = C[len][j] * 1LL * C[len - j][k] % mod * 1LL * f[t^1][r[x] - j][g[x] - k] % mod;
			
			vis[ x = x1 ] = a[i + 1].first; i++;
		} else {
			t ^= 1; rep(j,0,100) rep(k,0,100) f[t][j][k] = 0; 
			int len = a[i + 1].first - a[i].first, x1 = a[i].second;
			rep(j,r[x1],r[x]) rep(k,g[x1],g[x])
				f[t][j][k] = f[t^1][j - r[x1]][k - g[x1]] * 1LL * C[len][r[x1]] % mod * 1LL * C[len - r[x1]][g[x1]] % mod;
			
			vis[x] = a[i + 1].first; i++;
		}
	}
	printf("%d\n\n",f[t][0][0]);
	return 0;
}