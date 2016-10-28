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
const int N = 65536, M = 1000010;

struct edge{
	int to, pre;
}e[M];
#define v e[i].to
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
int l = 0, u[N];

void ins(int a, int b){
	e[++l] = (edge){b, u[a]}, u[a] = l;
}

int d[N], n, q[N];
void sortg(){
	int l = 1, r = 1;
	rep(i,1,n) if (!d[i]) q[r++] = i;
	while (l < r){
		int x = q[l++];
		reg(i,x) {
			d[v]--;
			if (!d[v]) q[r++] = v;
		}
	}
}

int el = 0, a[M], b[M];
void rebuild(){
	l = 0; memset(u, 0, sizeof(u));
	rep(i,1,el) ins(a[i], b[i]);
}

int fa[N], g[N][16], dep[N];

int lca(int a, int b){
	if (dep[a] < dep[b]) swap(a,b);
	int l = dep[a] - dep[b];
	if (l) rep(i,0,15) if (l >> i & 1) a = g[a][i];
	dep(i,15,0) if (g[a][i] != g[b][i]) a = g[a][i], b = g[b][i];
	//cout <<a<<' '<<b<<endl;
	if (a == b) return a; else return fa[a];
}

void calc_g(int x){
	g[x][0] = fa[x];
	rep(i,1,15) {
		g[x][i] = g[g[x][i - 1]][i - 1];
		if (!g[x][i]) break;
	}
}

void build(){
	rep(i,1,n) {
		int x = q[i]; fa[x] = -1;
		reg(i,x) if (fa[x] == -1) fa[x] = v; else fa[x] = lca(fa[x], v);
		if (fa[x] == -1) fa[x] = 0;
		//这里一定不能用f[x]==0判，因为f[x]可能在取lca的时候变成0!
		dep[x] = dep[fa[x]] + 1;
		calc_g(x);
	}
}

int sz[N];
void calc(){
	dep(i,n,1){
		int x = q[i];
		sz[fa[x]] += sz[x] + 1;
	}
	rep(i,1,n) printf("%d\n",sz[i]);
}

int main(){
	memset(d, 0, sizeof(d));
	scanf("%d",&n);
	rep(i,1,n){
		int t; scanf("%d",&t);
		while (t){
			el++;
			a[el] = i, b[el] = t;
			ins(t, i); d[i]++;
			scanf("%d",&t);
		}
	}
	sortg();
	rebuild();
	build();
	calc();
	return 0;
}