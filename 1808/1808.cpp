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

const int N = 1010, M = 5010;
struct edge{
	int to, pre;
}e[N * 2];
int u[N];
int l = 0;
void ins(int a, int b){
	e[++l] = (edge){b, u[a]}, u[a] = l;
}
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define v e[i].to

int dep[N], g[N][10], r[N], d[N], pre[N], id[N], dfs_clock = 0;
void dfs(int x, int f){
	id[pre[x] = ++dfs_clock] = x;
	d[x] = 0;
	reg(i,x) if (v != f) r[v] = d[x]++, g[v][0] = x, dep[v] = dep[x] + 1, dfs(v, x);
}

struct edg{
	int a, b, c, lca;
}E[M];
int el = 0;

int lca(int a, int b){
	if (dep[a] > dep[b]) swap(a,b);
	dep(j,9,0) if (g[b][j] && dep[g[b][j]] >= dep[a]) b = g[b][j];
	dep(j,9,0) if (g[a][j] != g[b][j]) a = g[a][j], b = g[b][j];
	if (a != b) return g[a][0]; else return a;
}

bool operator < (const edg &a, const edg &b){
	return pre[a.lca] > pre[b.lca];
}

int f[N][1024], ans = 0;
int main(){
	int n, m; scanf("%d%d",&n,&m);
	rep(i,1,m){
		int a, b, c; scanf("%d%d%d",&a,&b,&c);
		if (c == 0) ins(a, b), ins(b, a);
		else E[++el] = (edg){a, b, c, 0};
	}
	dfs(1,0);
	rep(j,1,9) rep(i,1,n) g[i][j] = g[g[i][j - 1]][j - 1];
	rep(i,1,el) E[i].lca = lca(E[i].a, E[i].b);
	sort(E + 1, E + el + 1);
	int ans = 0;
	int j = dfs_clock;
	rep(i,1,el){
		int a = E[i].a, b = E[i].b, c = E[i].c, lc = E[i].lca;
		while (j && j >= pre[lc]){
			int x = id[j], c = 0;
			reg(i,x) if (v != g[x][0]) {
				int ed = (1 << d[x]) - 1;
				rep(j,0,ed) if (j >> c & 1)
					f[x][j] = max(f[x][j], f[v][(1 << d[v]) - 1] + f[x][j ^ (1 << c)]);
				c++;
			}
			j--;
		}
		ans += c;
		if ((dep[a] ^ dep[b]) & 1) continue;
		if (dep[a] < dep[b]) swap(a, b);
		int F = f[a][(1 << d[a]) - 1], R;
		dep(j,dep[a] - 1, dep[lc] + 1) {
			R = r[a], a = g[a][0];
			F += f[a][(1 << d[a]) - 1 - (1 << R)];
		}

		if (b != lc){
			F += f[b][(1 << d[b]) - 1];
			dep(j,dep[b] - 1, dep[lc] + 1){
				R = r[b], b = g[b][0];
				F += f[b][(1 << d[b]) - 1 - (1 << R)];
			}
		}

		F += c;
		if (b == lc){
			int ed = (1 << d[b]) - 1;
			rep(i,0,ed) if (!(i >> r[a] & 1))
				f[lc][i^(1 << r[a])] = max(f[lc][i ^ (1 << r[a])], f[lc][i] + F);
		}else {
			int ed = (1 << d[lc]) - 1;
			rep(i,0,ed) if ((!(i >> r[a] & 1)) && (!(i >> r[b] & 1)))
				f[lc][i^(1 << r[a])^(1 << r[b])] = max(f[lc][i^(1 << r[a])^(1 << r[b])], f[lc][i] + F);
		}
	}
	int mx = 0;
	rep(i,1,n) mx = max(mx, f[i][(1 << d[i]) - 1]);
	ans -= mx;
	printf("%d\n",ans);
	return 0;
}