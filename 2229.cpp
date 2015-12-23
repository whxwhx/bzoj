#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 160, M = 3010;
struct edge{
	int to, pre, w;
}e[M * 2];
int l = 1, u[N], cur[N];
void ins(int a, int b, int c){
	e[++l] = (edge){b, u[a], c}, u[a] = l;
}
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define v e[i].to
#define ew e[i].w
int ans[N][N], n, m;
const int inf = 0x7fffffff;
#define min(a,b) ((a) < (b) ? (a) : (b))
void init(){
	l = 1; rep(i,1,n) u[i] = 0;
	rep(i,1,n) rep(j,1,n) ans[i][j] = inf;
}
int a[N], mark[N];
void reset(){
	rep(i,1,n) mark[i] = 0;
	for(int i = 2; i < l; i += 2) e[i].w = e[i ^ 1].w = (e[i].w + e[i ^ 1].w) >> 1;
}

int h[N], q[N], S, T;
bool bfs(){
	rep(i,1,n) h[i] = -1;
	int l = 0, r = 1; h[q[0] = S] = 0;
	while (l < r){
		int x = q[l++];
		reg(i,x) if (ew && h[v] == -1) h[v] = h[x] + 1, q[r++] = v;
	}
	return h[T] != -1;
}
int dfs(int x, int f){
	if (x == T) return f;
	int w, used = 0;
	for(int i = cur[x]; i; i = e[i].pre)if (ew && h[v] == h[x] + 1){
		w = min(ew, f- used), w = dfs(v, w);
		ew -= w; if (ew) cur[x] = i;
		e[i ^ 1].w += w;
		used += w; if (used == f) break;
	}
	if (!used) h[x] = -1;
	return used;
}
int dinic(){
	int ans = 0;
	while (bfs()){
		rep(i,1,n) cur[i] = u[i];
		ans += dfs(S, inf);
	}
	return ans;
}

void dfs(int x){
	mark[x] = 1;
	reg(i,x) if (ew && !mark[v]) dfs(v);
}
int t1[N], l1, l2;
void solve(int l, int r){
	if (l == r) return;
	S = a[l], T = a[r];
	reset();int t = dinic();
	dfs(S);
	rep(i,1,n) if (mark[i])
		rep(j,1,n) if (!mark[j]) ans[i][j] = ans[j][i] = min(ans[i][j], t);
	l1 = l - 1, l2 = r + 1;
	rep(i,l,r) if (mark[a[i]]) t1[++l1] = a[i]; else t1[--l2] = a[i];
	rep(i,l,r) a[i] = t1[i];
	solve(l, l1), solve(l2, r);
}

void work(){
	scanf("%d%d",&n,&m);
	init();
	rep(i,1,m){
		int a, b, c; scanf("%d%d%d",&a,&b,&c);
		ins(a, b, c), ins(b, a, c);
	}
	rep(i,1,n) a[i] = i;
	rep(i,1,n) swap(a[i], a[rand() % i + 1]);
	solve(1, n);
	int q; scanf("%d",&q);
	while (q--){
		int x;scanf("%d",&x);
		int t1 = 0;
		rep(i,1,n) rep(j,i + 1,n) if (ans[i][j] <= x) t1++;
		printf("%d\n",t1);
	}
}

int main(){
	srand(233);
	int T; scanf("%d",&T);
	while (T--) {
		work();
		if (T) printf("\n");
	}
}
