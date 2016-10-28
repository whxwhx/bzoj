#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N = 2000 + 10, M = 200000 + 10;
char mp[N][N];
typedef pair<int, int> node;
#define x first
#define y second
#define mp(a,b) make_pair(a,b)
int dx[5], dy[5];
node bd[M], q[N * N], v[N][N];
int r = 0;
void init(){
	dx[0] = 0, dy[0] = 1;
	dx[1] = 1, dy[1] = 0;
	dx[2] = 0, dy[2] = -1;
	dx[3] = -1,dy[3] = 0;
}

vector<node> edge[N * N];
#define pb(a) push_back(a)

int n, m, p, Q;
void bfs(){
	int l = 0;
	while (l < r){
		node a = q[l++];
		rep(i,0,3){
			node b = mp(a.x + dx[i], a.y + dy[i]);
			if (b.x && b.x <= n && b.y && b.y <= m && mp[b.x][b.y] != '#'){
				node &va = v[a.x][a.y], &vb = v[b.x][b.y];
				if (vb == mp(0,0)) 
					vb = mp(va.x + 1, va.y), q[r++] = b;
				else if (va.y != vb.y)
				edge[va.x + vb.x].pb(mp(va.y, vb.y));//be careful with the definition of the distance
			}
		}
	}
}

struct edg{
	int to, pre, c;
}e[M * 2];
int u[M], l = 0;
void ins(int a, int b, int c){
	e[++l] = (edg){b, u[a], c}, u[a] = l;
}
void insert(int a, int b, int c){
	ins(a,b,c), ins(b,a,c);
}
#define v e[i].to
#define ec e[i].c
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)

int f[M], fa[M], vis[M], R[M];
int find(int x){
	return f[x] == x ? x : f[x] = find(f[x]);
}
void kruskal(){
	rep(i,1,p) f[i] = i;
	rep(i,0,n * m)
		for(vector<node>::iterator it = edge[i].begin();it != edge[i].end();it++){
			int fa = find((*it).x), fb = find((*it).y);
			if (fa != fb) insert((*it).x,  (*it).y, i), f[fa] = fb;
		}
}

int dep[M];
void dfs(int x){
	vis[x] = 1;
	reg(i,x) if (!vis[v]) dep[v] = dep[x] + 1, fa[v] = x, R[v] = ec, dfs(v);
}

int g[M][20], g1[M][20];

#define max(a,b) ((a) < (b) ? (b) : (a))
int qry(int a, int b){
	if (find(a) != find(b)) return -1;
	if (dep[a] < dep[b]) swap(a,b);
	int ans = 0;
	dep(i,19,0) if (g[a][i] && dep[g[a][i]] >= dep[b]) ans = max(ans, g1[a][i]), a = g[a][i];
	dep(i,19,0) if (g[a][i] != g[b][i]) ans = max(ans, g1[a][i]), ans = max(ans, g1[b][i]), a = g[a][i], b = g[b][i];
	if (a != b) ans = max(ans, R[a]), ans = max(ans, R[b]);
	return ans;
}
#undef v

int main(){
	init();
	scanf("%d%d%d%d",&n,&m,&p,&Q);
	rep(i,1,n) scanf("%s",mp[i] + 1);
	int a, b;
	rep(i,1,p) scanf("%d%d",&a,&b), bd[i].x = a, bd[i].y = b, q[r++] = mp(a,b), v[a][b] = mp(0, i);
	bfs();
	kruskal();
	rep(i,1,p) if (vis[i] == 0) dep[i] = 1, dfs(i);
	rep(i,1,p) if (fa[i]) g[i][0] = fa[i], g1[i][0] = R[i];
	rep(j,1,19)
		rep(i,1,p)
			g[i][j] = g[g[i][j - 1]][j - 1], g1[i][j] = max(g1[g[i][j - 1]][j - 1], g1[i][j - 1]);
	rep(i,1,Q){
		scanf("%d%d",&a,&b);
		printf("%d\n",qry(a,b));
	}
}