#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;

const int mod = 10007, N = 210;
struct edge{
	int to, pre;
}e[N * 2];
int u[N];
int l = 0;
void ins(int a, int b){
	e[++l] = (edge){b, u[a]}, u[a] = l;
}
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define v e[i].to

#define max(a,b) ((a) > (b) ? (a) : (b))

int n, sz[N], s[N], rtcnt, rt2, rt; 
void getrt(int x, int f){
	sz[x] = 1, s[x] = 0;
	reg(i,x) if (v != f) getrt(v, x), sz[x] += sz[v], s[x] = max(s[x], sz[v]);
	s[x] = max(s[x], n - sz[x]);
	if (s[x] < s[rt]) rt = x;
}
int f[N][N], t[N];
void calc(int x, int fa){
	sz[x] = 1;
	f[x][0] = 1, f[x][1] = 1;
	rep(i,2,n) f[x][i] = 0;
	reg(i,x) if (v != fa){
		calc(v, x);
		rep(j,0,sz[v] + sz[x]) t[j] = 0;
		rep(j,0,sz[v]) rep(k,1,sz[x]) t[j + k] += f[v][j] * f[x][k] % mod, t[j + k] %= mod;
		rep(j,1,sz[v] + sz[x]) f[x][j] = t[j];
		sz[x] += sz[v];
	}
}
int g[N], cases = 0;
void work(){
	cases++;
	scanf("%d",&n);
	l = 0; rep(i,1,n) u[i] = 0;
	rep(i,1,n - 1){
		int a, b; scanf("%d%d",&a,&b);
		ins(a, b), ins(b, a);
	}
	s[rt = 0] = n; getrt(1, 0);
	rtcnt = 1;
	rep(i,1,n) if (s[i] == s[rt] && i != rt) rtcnt = 2, rt2 = i;
	int ans = 0;
	if (rtcnt == 1) {
		calc(rt, 0);
		//reg(i,rt) rep(j,0,sz[v]) cout <<v<<' '<<j<<' '<<f[v][j]<<endl;
		int x = rt;

		rep(tot,1,n){
			rep(i,0,n) g[i] = 0;
			g[1] = 1;
			sz[x] = 1;
			reg(i,x){
				rep(j,0,sz[v] + sz[x]) t[j] = 0;
				rep(j,0,sz[v]) if ((j << 1) >= tot) break; else
					rep(k,1,sz[x]) t[j + k] += f[v][j] * g[k] % mod, t[j + k] %= mod;

				rep(j,0,sz[v] + sz[x]) g[j] = t[j];
				sz[x] += sz[v];

			}
			ans += g[tot], ans %= mod;
		}

	}else{
		calc(rt, rt2), calc(rt2, rt);
		rep(i,1,n)	ans += f[rt][i] * f[rt2][i] % mod, ans %= mod;
	}
	if (ans < 0) ans += mod;
	printf("Case %d: %d\n",cases,ans);
}
int main(){
	int Q; scanf("%d",&Q);
	while (Q--) work();
}