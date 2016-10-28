#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
const int N = 200010, M = 500100;
int n, m, q; 

struct edg{
	int a, b, c;
}E[M];
bool operator < (const edg &a, const edg &b){
	return a.c < b.c;
}
int f[N];
int find(int x){
	return f[x] == x ? x : f[x] = find(f[x]);
}
int l, V[N], fa[N], h[N];
struct edge{
	int to, pre;
}e[N];
int u[N];
int el = 0;
void ins(int a, int b){
	e[++el] = (edge){b, u[a]}, u[a] = el;
}
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define v e[i].to

struct node{
	node *ch[2];
	int s;
}T[100001 * 51], *null = &T[0], *rt[N];
int tl = 0;
node *nn(){return &T[++tl];}
void seg_init(){
	null->ch[0] = null->ch[1] = null;
	null->s = 0;
	rt[0] = null;
}
#define mid ((l + r) >> 1)
node *add(node *o, int l, int r, int x){
	node *k = nn(); *k = *o, (k->s)++;
	if (l == r) return k;
	if (x <= mid) k->ch[0] = add(o->ch[0], l, mid, x); else k->ch[1] = add(o->ch[1], mid + 1, r, x);
	return k;
}

#define s(a,d) a->ch[d]->s
#define c(a,d) a->ch[d]
int kth(node *a, node *b, int l, int r, int k){
	if (k > (b->s) - (a->s) || !k) return -1;
	if (l == r) return l;
	if (k <= s(b,1) - s(a,1)) return kth(c(a, 1), c(b, 1), mid + 1, r, k); else return kth(c(a, 0), c(b, 0), l, mid, k - (s(b, 1) - s(a, 1)));
}

int pre[N], suc[N], dfs_clock = 0;
void dfs(int x){
	pre[x] = ++dfs_clock;
	if (x <= n) rt[dfs_clock] = add(rt[dfs_clock - 1], 1, n, h[x]); else rt[dfs_clock] = rt[dfs_clock - 1];
	reg(i,x) dfs(v);
	suc[x] = dfs_clock;
}
#define max(a,b) ((a) > (b) ? (a) : (b))
int g[N][20], F[N][20];
void build_g(){
	V[0] = 0;
	rep(i,1,l) g[i][0] = fa[i], F[i][0] = max(V[i], V[fa[i]]);
	rep(j,1,16)
		rep(i,1,l) g[i][j] = g[g[i][j - 1]][j - 1], F[i][j] = max(F[i][j - 1], F[g[i][j - 1]][j - 1]);
}

void build(){
	l = n;
	rep(i,1,(n << 1)) V[i] = 0, f[i] = i;
	rep(i,1,m){
		int fa1 = find(E[i].a), fb = find(E[i].b);
		if (fa1 != fb){
			V[++l] = E[i].c;
			f[fa1] = f[fb] = fa[fa1] = fa[fb] = l;
		}
	}
	rep(i,1,l) if (fa[i]) ins(fa[i], i);
	build_g();
	seg_init();
	rep(i,1,l) if (!fa[i]) dfs(i);
}

int lc(int x, int c){
	dep(i,16,0) if (g[x][i] && F[x][i] <= c) x = g[x][i];
	return x;
}
int b[N];
int qry(int c, int x, int k){
	x = lc(x, c);
	int t = kth(rt[pre[x] - 1], rt[suc[x]], 1, n, k);
	if (t != -1) t = b[t];
	return t;
}

void work(){
	int lastans = 0;
	rep(i,1,q){
		int c, x, k; scanf("%d%d%d",&x,&c,&k);
		c ^= lastans, x ^= lastans, k ^= lastans;
		printf("%d\n",lastans = qry(c, x, k));
		if (lastans == -1) lastans = 0;
	}
}

#undef mid
int Find(int x){
	int l = 1, r = n + 1;
	while (l + 1 < r){
		int mid = (l + r) >> 1;
		if (b[mid] <= x) l = mid; else r = mid;
	}
	return l;
}
int main(){
	scanf("%d%d%d",&n,&m,&q);
	rep(i,1,n) scanf("%d",&h[i]), b[i] = h[i];
	sort(b + 1, b + n + 1);
	rep(i,1,n) h[i] = Find(h[i]);

	rep(i,1,m) scanf("%d%d%d",&E[i].a,&E[i].b,&E[i].c);
	sort(E + 1, E + m + 1);
	build();
	work();
	return 0;
}
