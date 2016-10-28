#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 510, M = 4010;
int f[N][M], g[N][M], ans, n, m, w[N], c[N], d[N];

int u[N];
struct edge{
	int to, pre;
}e[N * 2];
int l = 0;
void ins(int a, int b){
	e[++l] = (edge){b, u[a]}, u[a] = l;
}
#define v e[i].to
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)

bool vis[N];
void init(){
	ans = 0;
	scanf("%d%d",&n,&m);
	rep(i,1,n) scanf("%d",&w[i]);
	rep(i,1,n) scanf("%d",&c[i]);
	rep(i,1,n) scanf("%d",&d[i]);
	l = 0; rep(i,1,n) u[i] = 0, vis[i] = false;
	rep(i,1,n - 1){
		int a, b; scanf("%d%d",&a,&b);
		ins(a, b), ins(b, a);
	}
}

#define max(a,b) ((a) > (b) ? (a) : (b))
int sz[N], s[N], sum, rt;
void getrt(int x, int f){
	sz[x] = 1, s[x] = 0;
	reg(i,x) if (v != f && !vis[v])
		getrt(v, x), sz[x] += sz[v], s[x] = max(s[x], sz[v]);
	s[x] = max(s[x], sum - sz[x]);
	if (s[x] < s[rt]) rt = x;
}

int pre[N], ed[N], dfs_clock = 0, id[N];
void dfs(int x, int f){
	id[ pre[x] = ++dfs_clock ] = x;
	reg(i,x) if (v != f && !vis[v]) dfs(v, x);
	ed[x] = dfs_clock;
}

const int inf = 1000000000;

typedef pair<int, int> node;
node q[M];
#define x first
#define y second
#define mp(a,b) make_pair(a,b)

void add(int x, int w, int c, int d){
	rep(i,0,c - 1){
		int l = 0, r = 0, t = 0;
		for(int j = i; j <= m; j += c, t++){
			while (l < r && (t - q[l].y) > d) l++;
			if (l < r) f[x][j] = q[l].x + w * t; else f[x][j] = -inf;
			if (g[x][j] > -inf){
				int F = g[x][j] - w * t;
				while (l < r && q[r - 1].x <= F) r--;
				q[r++] = mp(F, t);
			}
		}
	}
	ans = max(ans, f[x][m]);
}

void upd(int *a, int *b){
	rep(i,0,m) if (a[i] < b[i]) a[i] = b[i];
}

void calc(int x){
	dfs_clock = 0;
	dfs(x, 0);
	rep(i,0,m) f[0][i] = 0;
	rep(i,1,dfs_clock) rep(j,0,m) g[i][j] = -inf;
	rep(i,1,dfs_clock){
		int x = id[i];
		upd(g[i], f[i - 1]);
		add(i, w[x], c[x], d[x]);
		if (ed[x] + 1 <= dfs_clock) upd(g[ed[x] + 1], g[i]);
	}
}

void work(int x){
	vis[x] = 1;
	calc(x);
	int tmp = sum - sz[x];
	reg(i,x) if (!vis[v]){
		sum = sz[v] < sz[x] ? sz[v] : tmp; 
		rt = 0, getrt(v, x);
		work(rt);
	}
}
void work(){
	s[rt = 0] = sum = n; getrt(1,0);
	work(rt);
	printf("%d\n",ans);
}
int main(){
	int T; scanf("%d",&T);
	while (T--) init(), work();
	return 0;
}