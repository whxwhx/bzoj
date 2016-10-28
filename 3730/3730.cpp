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
#define Rep(i,a) for(int i = 0; i < a; i++)
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
#define ab(a) ((a) > 0 ? (a) : -(a))
#define mp(a,b) make_pair(a,b)
#define pb(a) push_back(a)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;

const int N = 200100;

struct edge{
	int to, pre, c;
}e[N * 2];
int u[N], n;
int l = 0;
void ins(int a, int b, int c){
	e[++l] = (edge){b, u[a], c}, u[a] = l;
}
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define v e[i].to
#define ec e[i].c

int c[N][2], tl;
void dfs(int x, int f){
	int t = x;
	reg(i,x)if (v != f){
		c[t][0] = ++tl, c[t][1] = v;
		t = c[t][0];
	}
	reg(i,x) if (v != f) dfs(v, x);
}

int a[N];

int ch[N][4], cnt[N], dep[N], dis[N][20], par[N], pch[N];

bool vis[N];
int sz[N], s[N], rt, sum;
int tot[N], maxdep;

void getdis(int x, int f, int dis){
	maxdep = max(maxdep, dis);
	tot[dis] += a[x];
	reg(i,x) if (v != f && !vis[v]) getdis(v, x, dis + ec);
}

int S[N * 20], Sl = 0;
int cl[N][4], cr[N][4];//(l,r]
void add(int x, int c, int a, int d){
	a++;//avoid 0
	int size = cr[x][c] - cl[x][c];
	for(;a && a <= size; a += (-a) & a) S[cl[x][c] + a] += d;
}
int Sum(int x, int c, int a){
	a++;//avoid 0
	if (a > cr[x][c] - cl[x][c]) a = cr[x][c] - cl[x][c];
	int ans = 0;
	for(;a; a -= (-a) & a) ans += S[cl[x][c] + a];
	return ans;
}

void cal(int x, int c, int ch, int dis){
	maxdep = 0, getdis(ch, x, dis);
	cl[x][c] = Sl;
	rep(i,0,maxdep) Sl++;
	cr[x][c] = Sl;
	rep(i,0,maxdep) add(x, c, i, tot[i]);
	rep(i,0,maxdep) tot[i] = 0;
}

void dfs(int x, int f, int d){
	dis[x][++dep[x]] = d;
	reg(i,x) if (v != f && !vis[v]) dfs(v, x, d + ec);
}

void getrt(int x, int f){
	s[x] = 0, sz[x] = 1;
	reg(i,x) 
		if (v != f && !vis[v]) getrt(v, x), s[x] = max(s[x], sz[v]), sz[x] += sz[v];
	s[x] = max(s[x], sum - sz[x]);
	if (s[x] < s[rt]) rt = x;
}

void work(int x){
	vis[x] = 1; cnt[x] = 0;
	dfs(x,0,0);
	reg(i,x) if (!vis[v]){
		sum = sz[v], rt = 0, getrt(v, x);
		ch[x][++cnt[x]] = rt, par[rt] = x, pch[rt] = cnt[x];
		cal(x, cnt[x], v, ec);
		work(rt);
	}
}

void build(){
	s[rt = 0] = sum = n, getrt(1,0);
	work(rt);
}

int qry(int x, int k){
	int c = 0, ans = 0;
	for(int w = x; w; w = par[w])if (dis[x][dep[w]] <= k){
		ans += a[w];
		rep(j,1,cnt[w]) if (j != c) ans += Sum(w, j, k - dis[x][dep[w]]);
		c = pch[w];
	}else c = pch[w];
	//else break;-->worng! dis[x][y] is not increasing with y
	return ans;
}

void modi(int x, int a1){
	for(int w = x; w && par[w]; w = par[w]){
		int f = par[w];
		add(f, pch[w], dis[x][dep[f]], a1 - a[x]); //dis[x][dep[f]]! not dis[w][dep[f]]!
	}
	a[x] = a1;
}

int main(){
	int m; scanf("%d%d",&n,&m);
	rep(i,1,n) scanf("%d",&a[i]);
	rep(i,1,n - 1) {
		int a, b; scanf("%d%d",&a,&b);
		ins(a, b, 0), ins(b, a, 0);
	}

	//virtual node
	tl = n, dfs(1, 0), n = tl;
	l = 0; rep(i,1,n) u[i] = 0;
	rep(i,1,n) {
		if (c[i][0]) ins(i, c[i][0], 0), ins(c[i][0], i, 0);
		if (c[i][1]) ins(i, c[i][1], 1), ins(c[i][1], i, 1);
	}

	build();
	int lastans = 0;
	rep(i,1,m){
		int op, a, b; scanf("%d%d%d",&op,&a,&b);
		a ^= lastans, b ^= lastans;
		if (op == 0) printf("%d\n",lastans = qry(a, b));
		else modi(a, b);
	}
	return 0;
}