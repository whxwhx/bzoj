#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 55;
int a[N][N], b[N][N], c[N][N];
const int inf = 500000000;
const double eps = 0.000001;

int sum = 0;

struct edge{
	int to, pre;
	double w;
}e[N * N * 20];
#define v e[i].to
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define ew e[i].w
int u[N * N], S, T, l = 1;

void ins(int a, int b, double w){
	e[++l] = (edge){b, u[a], w}, u[a] = l;
}
void insert(int a, int b, double w){
	ins(a, b, w), ins(b, a, 0);
}

#define min(a,b) ((a) < (b) ? (a) : (b))
int h[N * N], q[N * N], cur[N * N];
bool bfs(){
	rep(i,S,T) h[i] = -1;
	int l = 0, r = 1; q[h[S] = 0] = S;
	while (l < r){
		int x = q[l++];
		reg(i,x) if (ew && h[v] == -1) h[v] = h[x] + 1, q[r++] = v;
	}
	return h[T] != -1;
}

double dfs(int x, double f){
	if (x == T) return f;
	double w, used = 0;
	for(int i = cur[x]; i; i = e[i].pre) if (ew > eps && h[v] == h[x] + 1){
		w = min(ew, f - used), w = dfs(v, w);
		ew -= w; if (ew) cur[x] = i;
		e[i ^ 1].w += w;
		used += w; if (used == f) break;
	}
	if (!used) h[x] = -1;
	return used;
}

double dinic(){
	double ans = 0;
	while (bfs()){
		rep(i,S,T) cur[i] = u[i];
		ans += dfs(S, inf);
	}
	return ans;
}

int n, m; 

int id(int x, int y){
	y++;
	return x * (m + 2) + y;
}

bool check(double t){
	//init
	l = 1;
	rep(i,S,T) u[i] = 0;
	//build
	rep(i,0,n + 1)
		rep(j,0,m + 1)
			if (a[i][j] > 0) insert(S, id(i,j), a[i][j]); else if (a[i][j] < 0) insert(id(i,j), T, -a[i][j]);
	rep(i,1,n + 1) rep(j,1,m) insert(id(i - 1,j), id(i,j), b[i][j] * t), insert(id(i,j), id(i - 1,j), b[i][j] * t);
	rep(i,1,n) rep(j,1,m + 1) insert(id(i,j - 1), id(i,j), c[i][j] * t), insert(id(i,j), id(i,j - 1), c[i][j] * t); 
	//check
	return dinic() < sum;
}

void solve(){
	int t = 0;
	double l = 0, r = 100 * n * m;
	while (l + eps < r){
		t++; if (t > 1000) break;
		double mid = (l + r) / 2;
		if (check(mid)) l = mid; else r = mid;
	}
	printf("%.3lf\n",(l + r) / 2);
}

int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,n) rep(j,1,m) scanf("%d",&a[i][j]), sum += a[i][j];
	rep(i,0,n + 1) a[i][0] = a[i][m + 1] = -inf;
	rep(i,0,m + 1) a[0][i] = a[n + 1][i] = -inf;
	rep(i,1,n + 1) rep(j,1,m) scanf("%d",&b[i][j]);
	rep(i,1,n) rep(j,1,m + 1) scanf("%d",&c[i][j]);
	S = 0, T = id(n + 1, m + 1) + 1;
	solve();
	return 0;
}
