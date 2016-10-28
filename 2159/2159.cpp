//树分治做法
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define max(a,b) ((a) > (b) ? (a) : (b))
#define rep(i,a,b) for(int i = a; i <= b; i++)
int n, k;
const int N = 50000 + 5, K = 150 + 5, M = 10007;
int a[N], b[N];
void Uncompress()
{
	int L, i, now, A, B, Q, tmp;
	scanf("%d%d%d", &n, &k, &L);
	scanf("%d%d%d%d", &now, &A, &B, &Q);
	for (i = 1; i < N; i ++)	
	{
		now = (now * A + B) % Q;
		tmp = (i < L) ? i : L;
		a[i] = i - now % tmp, b[i] = i + 1;
	}
}

struct edge
{
	int to, pre;
}e[N * 2];
int u[N];
int l = 0;
void ins(int a, int b)
{
	e[++l] = (edge){b, u[a]}, u[a] = l;
}
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define v e[i].to

int c[K][K], pw[N][K];
void init()
{
	rep(i,0,k){
		c[i][0] = c[i][i] = 1;
		rep(j,1,i - 1) c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % M;
	}
	rep(i,0,n){
		pw[i][0] = 1;
		rep(j,1,k) pw[i][j] = 1LL * pw[i][j - 1] * i % M;
	}
}


int rt, sz[N], s[N], sum, vis[N], ans[N];
int cnt1[K], cnt0[K];
void dfs1(int x, int f, int dep){
	rep(i,0,k) cnt1[i] = (cnt1[i] + pw[dep][i]) % M;
	reg(i,x) if (!vis[v] && v != f) dfs1(v, x, dep + 1);
}
void dfs2(int x, int f, int dep){
	rep(i,0,k) 
		ans[x] += 1LL * c[k][i] * pw[dep][k - i] % M * (cnt0[i] - cnt1[i]) % M,
		ans[x] %= M;
	reg(i,x) if (!vis[v] && v != f) dfs2(v, x, dep + 1);
}
void calc(int x)
{
	rep(i,0,k) cnt1[i] = 0;
	reg(i,x) if (!vis[v]) dfs1(v, x, 1);
	rep(i,0,k) cnt0[i] = cnt1[i];
	
	//don't forget x itself!
	ans[x] += cnt0[k], ans[x] %= M;
	cnt0[0]++;

	reg(i,x) if (!vis[v]) {
		rep(j,0,k) cnt1[j] = 0; 
		dfs1(v, x, 1);
		dfs2(v, x, 1);
	}
}
void getrt(int x, int f)
{
	sz[x] = 1, s[x] = 0;
	reg(i,x) if (v != f && !vis[v])
	{
		getrt(v, x);
		sz[x] += sz[v];
		s[x] = max(s[x], sz[v]);
	}
	s[x] = max(s[x], sum - sz[x]);
	if (s[x] < s[rt]) rt = x;
}
void work(int x)
{
	vis[x] = 1, calc(x);
	reg(i,x) if (!vis[v])
	{
		sum = sz[v], rt = 0, getrt(v, x);
		work(rt);//rt!
	}
}
int main()
{
	Uncompress();
	//scanf("%d%d",&n,&k);rep(i,1,n - 1) scanf("%d%d",&a[i],&b[i]);
	rep(i,1,n - 1) ins(a[i], b[i]), ins(b[i], a[i]);
	init();
	s[rt = 0] = sum = n, getrt(1, 0);
	work(rt);
	rep(i,1,n) {
		if (ans[i] < 0) ans[i] += M;
		printf("%d\n",ans[i]);
	}
}