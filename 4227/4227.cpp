#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
const int N = 100010, M = 200010;
typedef long long LL;
const LL INF = 1LL << 61;

#define v e[i].to
#define ec e[i].c
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)

int n, S;
LL ans[N];
namespace dominator{
	struct edge{ int to, pre; } e[M]; int u[N], l = 0;
	int f[N][17], q[N], d[N], tmp[N], dep[N];
	void ins(int a, int b) { e[++l] = (edge){b, u[a]}, u[a] = l, d[b]++; }

	int lca(int a, int b) {
		if (dep[a] < dep[b]) swap(a, b); int l = dep[a] - dep[b];
		dep(i,16,0) if (l >> i & 1) a = f[a][i];
		dep(i,16,0) if (f[a][i] != f[b][i]) a = f[a][i], b = f[b][i];
		return a == b ? a : f[a][0];
	}

	int r;
	void build(){
		rep(i,1,n) tmp[i] = d[i];
		int l = 0; r = 1; q[0] = S;
		while (l < r){
			int x = q[l++];
			reg(i,x) { d[v]--; if (!d[v]) q[r++] = v; }
		}
		rep(i,1,n) d[i] = tmp[i];

		rep(i,1,n) f[i][0] = 0;
		rep(t,0,r - 1){
			int x = q[t]; dep[x] = dep[f[x][0]] + 1;
			//build x
			rep(i,1,16) f[x][i] = f[f[x][i - 1]][i - 1];
			//upd v
			reg(i,x) if (!f[v][0]) f[v][0] = x; else f[v][0] = lca(f[v][0], x);
		}
	}

	int sz[N];
	void calc(){
		dep(t,r - 1,0){
			int x = q[t]; sz[x]++;
			sz[f[x][0]] += sz[x];
		}
		rep(x,1,n) reg(i,x) if (d[v] == 1) ans[x] += sz[v], ans[v] += sz[v];
	}
}

struct edge{ int to, pre, c; } e[M << 1]; int u[N], l = 0;
void ins(int a, int b, int c) { e[++l] = (edge){b, u[a], c}, u[a] = l; }


typedef pair<LL, int> node;
priority_queue<node> q;
#define mp(a,b) make_pair(a,b)

LL dis[N]; bool vis[N];
void SSP(){
	rep(i,1,n) dis[i] = INF; dis[S] = 0; q.push(mp(-dis[S], S));
	while (!q.empty()){
		int x = q.top().second; q.pop();
		if (vis[x]) continue; vis[x] = true;
		reg(i,x) if (dis[v] > dis[x] + ec) dis[v] = dis[x] + ec, q.push(mp(-dis[v], v));
	}
	rep(x,1,n) if (dis[x] < INF) reg(i,x) if (dis[x] + ec == dis[v]) dominator::ins(x, v);
}

int main(){
	int m; scanf("%d%d",&n,&m);
	rep(i,1,m) { int a, b, l; scanf("%d%d%d",&a,&b,&l); ins(a, b, l), ins(b, a, l); }
	scanf("%d",&S); SSP();
	dominator::build(); dominator::calc();
	rep(i,1,n) printf("%lld\n",ans[i]);
	return 0;
}