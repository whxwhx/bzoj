#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 810;
int n, d[N][N];

struct relate{ int a, b, d; }a[N * N]; int al = 0;

bool operator < (const relate &a, const relate &b) { return a.d > b.d; }

int f[N], r[N], ans;
void find( int x ) {
	if (f[x] != x) {
		find(f[x]);
		r[x] = r[x] ^ r[f[x]];
		f[x] = f[f[x]];
	}
}

int u[N << 1];
struct edge{ int to, pre; } e[N * N * 4]; int l = 0;
#define v e[i].to
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
void ins(int a, int b) { e[++l] = (edge){b, u[a]}, u[a] = l; }

#define id(x, d) (((x) << 1) | (d))
void insert(int a, int b) { ins(a, b), ins(b ^ 1, a ^ 1); }

int dfn, pre[N << 1], low[N << 1], scc[N << 1], st[N << 1], top, cnt;
void dfs(int x) {
	pre[x] = low[x] = ++dfn; st[top++] = x;
	reg(i,x) if (!pre[v]) dfs(v), low[x] = min(low[x], low[v]); else if (!scc[v]) low[x] = min(low[x], pre[v]);
	if (pre[x] == low[x]) {
		st[top] = 0; cnt++;
		while (st[top] != x) scc[st[--top]] = cnt;
	}
}

bool check(int la, int lb) {
	rep(i,id(1,0),id(n,1)) u[i] = pre[i] = scc[i] = 0; l = 0;
	rep(i,1,la - 1) insert(id(a[i].a, 0), id(a[i].b, 1)), insert(id(a[i].a, 1), id(a[i].b, 0));
	rep(i,la,lb - 1) insert(id(a[i].a, 0), id(a[i].b, 1));
	dfn = 0, top = 0, cnt = 0;
	rep(i,id(1,0),id(n,1)) if (!pre[i]) dfs(i);
	rep(i,1,n) if (scc[id(i,0)] == scc[id(i,1)]) return false;
	return true;
}

void solve( int L ) {
	int l = L + 1, r = al + 2; a[al + 1].d = 0;
	while (l + 1 < r) {
		int mid = (l + r) >> 1;
		if ( check( L, mid ) ) l = mid; else r = mid;
	}
	if ( check( L, l ) ) ans = min(ans, a[L].d + a[l].d);
}

void work() {
	al = 0;
	rep(i,1,n - 1) rep(j,i + 1,n) scanf("%d",&d[i][j]), d[j][i] = d[i][j], a[++al] = (relate){i, j, d[i][j]};
	sort(a + 1, a + al + 1);
	rep(i,1,n) f[i] = i, r[i] = 0;
	ans = a[1].d * 2;
	rep(i,1,al) {
		find(a[i].a), find(a[i].b);
		int fa = f[a[i].a], fb = f[a[i].b];
		if (fa == fb) {
			if ((r[a[i].a] ^ r[a[i].b]) != 1) { solve(i); break; }
		} else {
			f[fa] = fb, r[fa] = r[a[i].a] ^ r[a[i].b] ^ 1;
			solve(i);
		}
	}
	solve(al); solve(al + 1);
	printf("%d\n",ans);
}

int main() {
	while (scanf("%d",&n) == 1) work();
	return 0;
}