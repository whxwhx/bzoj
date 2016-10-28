#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef long long LL;
const int N = 20, M = 1 << 18;
int a[N][N], cnt[M], bin[M];

struct edge{ int to, pre; }e[N * 2];
int l = 0, u[N];
void ins(int a, int b){ e[++l] = (edge){b, u[a]}, u[a] = l; }
#define v e[i].to
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)

int n, L, b[N];
LL f[N][N];
void dfs(int x, int fa, int s){
	reg(i,x) if (v != fa) dfs(v, x, s);
	rep(k,1,L) {
		int j = b[k]; f[x][j] = 1;
		reg(i,x) if (v != fa){
			LL tmp = 0;
			rep(k1,1,L) { int j1 = b[k1]; if (a[j][j1]) tmp += f[v][j1]; }
			f[x][j] *= tmp; if (!f[x][j]) break;
		}
	}
}

LL calc(int s){ 		
	L = 0;
	rep(i,1,n) if (s >> (i - 1) & 1) b[++L] = i;
	
	LL ans = 0; dfs(1, 0, s);
	rep(i,1,n) if (s >> (i - 1) & 1) ans += f[1][i];
	return ans;
}

int main(){
	int m; scanf("%d%d",&n,&m);
	rep(i,1,m) { int x, y; scanf("%d%d",&x,&y); a[x][y] = a[y][x] = 1; }

	rep(i,1,n - 1){ int a, b; scanf("%d%d",&a,&b); ins(a, b), ins(b, a);}

	rep(i,1,n) bin[1 << (i - 1)] = i;
	int S = (1 << n) - 1; LL ans = 0;
	for(int i = 0; i < S; i++){
		if (i) cnt[i] = -cnt[i ^ ((-i) & i)]; else cnt[0] = 1;
		ans += cnt[i] * calc(S ^ i);
	}
	printf("%lld\n",ans);
	return 0;
}