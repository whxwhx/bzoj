#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
const int N = 210, M = 50010;
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define ab(a) ((a) < 0 ? -(a) : (a))
#define upd(x, a) (x == -1 ? x = (a) : x = min((a), x))
int g[N][N], f[N][N], p[N][N], s[N];

typedef pair<int, int> node;

int cmp_i;
bool cmp(const int &a, const int &b){
	return f[cmp_i][a] < f[cmp_i][b];
}


int main(){
	int n, m; scanf("%d%d",&n,&m);
	rep(i,1,n) rep(j,1,n) g[i][j] = -1;
	rep(i,1,n) g[i][i] = 0;
	rep(i,1,m){
		int a, b, c; scanf("%d%d%d",&a,&b,&c);
		upd(g[a][b], c), upd(g[b][a],c);
	}
	rep(i,1,n) rep(j,1,n) f[i][j] = g[i][j];
	//floyd
	rep(k,1,n) rep(i,1,n) rep(j,1,n) 
		if (f[i][k] != -1 && f[k][j] != -1) upd(f[i][j], f[i][k] + f[k][j]); 
	//sort
	rep(i,1,n) {
		rep(j,1,n) p[i][j] = j;
		cmp_i = i;
		sort(p[i] + 1, p[i] + n + 1, cmp);
	}
	//calc
	int ans = -1;
	rep(i,1,n) rep(j,i,n) if (g[i][j] != -1){
		s[n + 1] = 0;
		dep(k,n,1) s[k] = max(s[k + 1], f[p[i][k]][j]);
		rep(k,1,n) 
			if (ab(f[i][p[i][k]] - s[k + 1]) <= g[i][j]) //make sure the abs center isn't on this edge
				upd(ans, f[i][p[i][k]] + g[i][j] + s[k + 1]);
	}
	printf("%d\n",ans);
}