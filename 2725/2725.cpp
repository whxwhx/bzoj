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
#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
const int N = 210000 + 10;
const LL inf = 500000000000000LL;
struct edge{
	int to, pre, c;
	bool w;
}e[N * 2];
int u[N];
int l = 0;
void ins(int a, int b, int c){
	e[++l] = (edge){b, u[a], c, 0}, u[a] = l;
}
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define v e[i].to
#define ec e[i].c
#define ew e[i].w

int n, m, a[N], b[N], c[N], S, T;
LL tag[N * 4], s[N], ans[N];
void modi(int x, int l, int r, int a, int b, LL c){
	if (a <= l && r <= b) tag[x] = min(tag[x], c); else{
		int mid = (l + r) >> 1, lc = x << 1, rc = lc + 1;
		if (a <= mid) modi(lc, l, mid, a, b, c);
		if (b >  mid) modi(rc, mid + 1, r, a, b, c);
	}
}
void push(int x, int l, int r){
	if (l == r) s[l] = tag[x]; else{
		int mid = (l + r) >> 1, lc = x << 1, rc = lc + 1;
		tag[lc] = min(tag[lc], tag[x]), tag[rc] = min(tag[rc], tag[x]);
		push(lc, l, mid), push(rc, mid + 1, r);
	}
}

int num[N], t[N], numl;

typedef pair<LL, int> node;
priority_queue<node> q;

LL dS[N], dT[N];
bool vis[N];
void dij(int S, LL *d){
	rep(i,1,n) d[i] = inf, vis[i] = false;
	q.push(mp(d[S] = 0, S));
	while (!q.empty()){
		int x = q.top().second; q.pop();
		if (vis[x]) continue;
		reg(i,x) if (d[x] + ec < d[v])
			d[v] = d[x] + ec, q.push(mp(-d[v], v));
	}
}

int f[N], r[N];
void dfs(int x, int dep){
	if (x == T) numl = dep;
	reg(i,x) if (dS[v] == dS[x] + ec && f[v] == -1) f[v] = x, r[v] = (i + 1) >> 1, ew = 1, dfs(v, dep + 1);
}
void dfs1(int x, int c){
	reg(i,x) if (ew && t[v] == -1) t[v] = c, dfs1(v, c);
}
void calc_num(){
	rep(i,1,n) f[i] = t[i] = -1;
	f[S] = 0, dfs(S, 0);
	int x = T;
	dep(i, numl, 0) num[i] = x, t[x] = i, x = f[x];
	rep(i, 0, numl) dfs1(num[i], i);
}

void calc(){
	rep(i,1,m){
		if (t[a[i]] > t[b[i]]) swap(a[i], b[i]);
		if (f[b[i]] != a[i] && t[a[i]] < t[b[i]] && t[a[i]] != -1 && t[b[i]] != -1){
			LL w = dS[a[i]] + c[i] + dT[b[i]];
			modi(1, 1, numl, t[a[i]] + 1, t[b[i]], w);
		}
	}
}

void init(){
	dij(S, dS), dij(T, dT);
	if (dS[T] == inf) return;
	calc_num();
	rep(i,1,m) ans[i] = 0;
	int tmp = n * 4;
	rep(i,1,tmp) tag[i] = inf;
	calc();
	push(1, 1, numl);
	rep(i,1,numl) ans[r[num[i]]] = s[i];
}

void print(LL x){
	if (x == inf) printf("Infinity\n"); else printf("%lld\n",x);
}
struct edg1{
	int a, b, num;
}edg[N];
bool operator < (const edg1 &a, const edg1 &b){
	return (a.a < b.a) || (a.a == b.a && a.b < b.b);
}
int find(int a, int b){
	edg1 tmp = (edg1){a, b, 0};
	int l = 0, r = m;//(l,r]
	while (l + 1 < r){
		int mid = (l + r) >> 1;
		if (edg[mid] < tmp) l = mid; else r = mid; 
	}
	if (r && edg[r].a == a && edg[r].b == b) return edg[r].num; else return 0;
}
int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,m) {
		scanf("%d%d%d",&a[i],&b[i],&c[i]);
		if (a[i] > b[i]) swap(a[i], b[i]);
		ins(a[i], b[i], c[i]), ins(b[i], a[i], c[i]), edg[i] = (edg1){a[i], b[i], i};
	}
	scanf("%d%d",&S,&T);
	init();
	int Q; scanf("%d",&Q);
	sort(edg + 1, edg + m + 1);
	rep(i,1,Q){
		int a, b; scanf("%d%d",&a,&b); if (a > b) swap(a,b);
		int t = find(a,b);
		if (t && ans[t]) print(ans[t]); else print(dS[T]);
	}
	return 0;
}