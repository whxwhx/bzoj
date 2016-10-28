#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
const int N = 35, inf = 1000000000;
#define min(a,b) ((a) < (b) ? (a) : (b))
double ans;
int v[N], p[N], c[N], d[N];
int n, m, M, f[N][N];

struct md{
	int d, c;
	double p;
}e[(1 << 18) + 100];
bool operator < (const md &a, const md &b){
	return a.d < b.d || (a.d == b.d && a.c < b.c);
}
int l;
double s[(1 << 18) + 100];
int L[N], R[N];

void dfs(int x, int d, int c, double P){
	if (x > M){
		e[++l] = (md){d, c, P};
	}else {
		dfs(x + 1, d, c + v[x], P * p[x] / 100);
		dfs(x + 1, d + 1, c, P * (100 - p[x]) / 100);
	}
}

double calc(int d, int c){
	int l = L[d], r = R[d]; //(l,r]
	while (l + 1 < r){
		int mid = (l + r) >> 1;
		if (e[mid].c < c) l = mid; else r = mid;
	}
	return s[R[d]] - s[r - 1];
}

void dfs2(int x, int d, int c, double P){
	if (x > n) {
		rep(d1, 0, M){
			rep(j, 0, m){
				int i = d + d1, c1 = f[i][j] - c, c2 = f[i][j + 1] - c;
				ans += j * P * (calc(d1, c1) - calc(d1, c2));
			}
		}
	}else {
		dfs2(x + 1, d, c + v[x], P * p[x] / 100);
		dfs2(x + 1, d + 1, c, P * (100 - p[x]) / 100);		
	}
}

void work(){
	ans = 0;
	scanf("%d%d",&n,&m);
	rep(i,1,n) scanf("%d%d",&v[i],&p[i]);
	rep(i,1,m) scanf("%d%d",&c[i],&d[i]);
	
	//dp
	rep(i,0,n) rep(j,0,m + 1) f[i][j] = inf;
	rep(i,0,n) f[i][0] = 0;
	rep(k,1,m){
		dep(j,k,1)
			rep(i,d[k],n)
				f[i][j] = min(f[i][j], f[i - d[k]][j - 1] + c[k]);
	}
	//dfs1
	M = (int)min(18, (n * 2 / 3.0));
	l = 0;
	dfs(1,0,0,1);
	rep(i,0,M) e[++l] = (md){i, -inf, 0}, e[++l] = (md){i, inf, 0};
	sort(e + 1, e + l + 1);
	rep(i,1,l){
		if (e[i].c == -inf) L[e[i].d] = i;
		if (e[i].c ==  inf) R[e[i].d] = i; 
	}
	s[0] = 0;
	rep(i,1,l) s[i] = s[i - 1] + e[i].p;
	//dfs2
	dfs2(M + 1, 0, 0, 1);
	printf("%.4lf\n",ans);
}
int main(){
	int T; scanf("%d",&T);
	while (T--) work();
}
