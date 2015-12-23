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
int l, v[N], fa[N];
struct edge{
	int to, pre;
}e[N];
int el = 0;
void ins(int a, int b){
	e[++el] = (edge){b, u[a]}, u[a] = el;
}
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define v e[i].to

struct node{
	node *ch[2];
	int s;
}T[N * 51];
int tl = 0;
node *nn(){return &T[++tl];}
node *add(node *o, int l, int r, 

int pre[N], suc[N], dfs_clock = 0;
void dfs(int x){
	pre[x] = ++dfs_clock;
	rt[dfs_clock] = add(rt[dfs_clock - 1], 1, n, h[x]);
	reg(i,x) dfs(v);
	suc[x] = dfs_clock;
}
#define max(a,b) ((a) > (b) ? (a) : (b))
int g[N][20], f[N][20];
void build_g(){
	rep(i,1,n) g[i][0] = fa[i], f[i][0] = v[i];
	rep(i,0,19)
		rep(j,1,n) g[i][j] = g[g[i][j - 1]][j - 1], f[i][j] = max(f[i][j - 1], f[g[i][j - 1]][j - 1]);
}

void build(){
	l = n;
	rep(i,1,(n << 1)) v[i] = 0, f[i] = i;
	rep(i,1,n){
		int fa1 = find(E[i].a), fb = find(E[i].b);
		if (fa1 != fb){
			v[++l] = E[i].c;
			f[fa1] = f[fb] = fa[fa1] = fa[fb] = l;
		}
	}
	n = l;
	rep(i,1,l) if (fa[i]) ins(fa[i], i);
	build_g();
	rep(i,1,l) if (!fa[i]) dfs(i);
}


int qry(){
	
}

void work(){

}

int b[N];
int find(int x){
	int l = 1, r = n + 1;
	while (i + 1 < r){
		int mid = (l + r) >> 1;
		if (b[mid] <= x) l = mid; else r = mid;
	}
	return l;
}
int main(){
	scanf("%d%d%d",&n,&m,&q);
	rep(i,1,n) scanf("%d",&h[i]), b[i] = h[i];
	sort(b + 1, b + n + 1);
	rep(i,1,n) h[i] = find(h[i]);

	rep(i,1,m) scanf("%d%d%d",&E[i].a,&E[i].b,&E[i].c);
	sort(E + 1, E + m + 1);
	build();
	work();
	return 0;
}
