#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
typedef long long LL;
using namespace std;
const int N = 100010;
struct edge{ int to, pre, c; }e[N * 2]; int u[N], l = 0;
void ins(int a, int b, int c) { e[++l] = (edge){b, u[a], c}, u[a] = l; }
#define v e[i].to
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define ec e[i].c

int r[N], sz[N], son[N], n, dep[N];

LL dis[N];
void dfs(int x, int f){
	sz[x] = 1; son[x] = 0;
	reg(i,x) if (v != f) { r[v] = ec, dep[v] = dep[x] + 1, dis[v] = dis[x] + ec, dfs(v, x), sz[x] += sz[v]; if (sz[v] > sz[son[x]]) son[x] = v; }
}

int top[N], pre[N], dfn = 0, id[N], fa[N];
void build(int x, int f){
	fa[x] = f; id[ pre[x] = ++dfn ] = x;
	if (son[x]) top[son[x]] = top[x], build(son[x], x);
	reg(i,x) if (v != f && v != son[x]) top[v] = v, build(v, x);
}

LL t[N]; const LL inf = 123456789123456789LL;
#define lc (x << 1)
#define rc (lc | 1)
#define mid ((l + r) >> 1)
#define lcq lc, l, mid
#define rcq rc, mid + 1, r
struct line {
	LL k, b; 
	LL f(int x) { return 1LL * k * t[x] + b; } 
};

struct seg{

	LL mn[N * 4]; line s[N * 4], c;
	int a, b;
	
	void build(int x, int l, int r) { mn[x] = inf; s[x] = (line){0, inf}; if (l < r) build(lcq), build(rcq); }
	void modi(int x, int l, int r, line c){
		//if (x == 1) cout <<"add: "<<" [ "<<t[a]<<" , "<<t[b]<<" ] "<<c.k<<"x+"<<c.b<<endl;
		if (a <= l && r <= b) {
			mn[x] = min(mn[x], c.f(l)); mn[x] = min(mn[x], c.f(r)); 
			bool fl = c.f(l) < s[x].f(l), fr = c.f(r) < s[x].f(r);  
			
			if (fl && fr) s[x] = c;
			else if (fl || fr){
				bool fm = c.f(mid) < s[x].f(mid);
				if (fl == fm){  if (fl) swap(c, s[x]); modi(rcq, c); }
				else{  if (fr) swap(c, s[x]); modi(lcq, c); }
			}
		}else { if (a <= mid) modi(lcq, c); if (b > mid) modi(rcq, c); mn[x] = min(mn[x], mn[lc]); mn[x] = min(mn[x], mn[rc]); }
	}
	LL qry(int x, int l, int r){
		LL ans = inf; int la = max(l, a), rb = min(r, b);
		if (la <= rb) ans = min(ans, min(s[x].f(la), s[x].f(rb)));
		if (a <= l && r <= b) ans = min(ans, mn[x]);
		else { if (a <= mid) ans = min(ans, qry(lcq)); if (b > mid) ans = min(ans, qry(rcq)); }
		//if (x == 1) cout <<"qry: "<<t[a]<<' '<<t[b]<<' '<<ans<<endl;
		return ans;
	}
}seg;

int lca(int a, int b){
	int ta = top[a], tb = top[b];
	while (ta != tb) { if (dep[ta] < dep[tb]) swap(ta, tb), swap(a, b); a = fa[ta]; ta = top[a]; }
	if (dep[a] > dep[b]) swap(a, b);
	return a;
}

//#include <cassert>

void modi(int a, int b, LL t1, LL t2){
	int ta = top[a], tb = top[b], s = a;
	while (ta != tb){
		if (dep[ta] < dep[tb]) swap(ta, tb), swap(a, b);
		LL da = dis[a] + dis[s] - 2 * dis[lca(a, s)], dta = dis[ta] + dis[s] - 2 * dis[lca(ta, s)];
		/*cout <<dta<<' '<<da<<endl; cout <<a<<' '<<ta<<endl;
		cout <<t[pre[ta]]<<' '<<t[pre[a]]<<endl;
		cout <<pre[ta]<<endl;*/
		//assert(t[pre[ta]] - t[pre[a]] == dta - da || t[pre[ta]] - t[pre[a]] == da - dta);
		//cout <<a<<' '<<ta<<endl;
		seg.a = pre[ta], seg.b = pre[a], seg.c.k = (da == dta) ? t1 : t1 * ((t[pre[ta]] - t[pre[a]]) / (dta - da)), seg.c.b = t1 * da + t2 - seg.c.k * t[pre[a]]; seg.modi(1, 1, n, seg.c);
		a = fa[ta]; ta = top[a];
	}
	if (dep[a] > dep[b]) swap(a, b);
	LL da = dis[a] + dis[s] - 2 * dis[lca(a, s)], db = dis[b] + dis[s] - 2 * dis[lca(b, s)];
	//cout <<da<<' '<<db<<endl; cout <<a<<' '<<b<<endl;
	//cout <<a<<' '<<dis[a]<<endl;
	seg.a = pre[a], seg.b = pre[b], seg.c.k = (da == db) ? t1 : t1 * ((t[pre[b]] - t[pre[a]]) / (db - da)), seg.c.b = t1 * da + t2 - seg.c.k * t[pre[a]]; seg.modi(1, 1, n, seg.c);
}

LL qry(int a, int b){
	int ta = top[a], tb = top[b];
	LL ans = inf;
	while (ta != tb){
		if (dep[ta] < dep[tb]) swap(ta, tb), swap(a, b);
		seg.a = pre[ta], seg.b = pre[a]; ans = min(ans, seg.qry(1, 1, n));
		a = fa[ta]; ta = top[a];
	}
	if (dep[a] > dep[b]) swap(a, b);
	seg.a = pre[a], seg.b = pre[b]; ans = min(ans, seg.qry(1, 1, n));
	return ans;
}

int main(){
	int m; scanf("%d%d",&n,&m);
	rep(i,1,n - 1) { int a, b, c; scanf("%d%d%d",&a,&b,&c); ins(a, b, c), ins(b, a, c); }
	seg.build(1, 1, n);
	dfs(1, 0);
	top[1] = 1; build(1, 0);
	rep(i,1,n) t[i] = t[i - 1] + r[id[i]];
	rep(i,1,m){
		int tp; scanf("%d",&tp);
		if (tp == 1){ int s, t; LL a, b; scanf("%d%d%lld%lld",&s,&t,&a,&b); modi(s, t, a, b); }	
		else{ int s, t; scanf("%d%d",&s,&t); printf("%lld\n",qry(s, t)); }
	}
	return 0;
}