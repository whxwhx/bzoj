//斯特林数做法
#include <iostream>
#include <cstdio>
#include <cmath>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define Rep(i,a) for(int i = 0; i < a; i++)
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
#define ab(a) ((a) > 0 ? (a) : -(a))
#define mp(a,b) make_pair(a,b)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
int n, k;
const int N = 50000 + 5, K = 150 + 5, M = 10007;
int a[N], b[N];

void Uncompress()
{
	int L, i, now, A, B, Q, tmp;
	scanf("%d%d%d", &n, &k, &L);
	scanf("%d%d%d%d", &now, &A, &B, &Q);
	for (i = 1; i < N; i ++)	
	{
		now = (now * A + B) % Q;
		tmp = (i < L) ? i : L;
		a[i] = i - now % tmp, b[i] = i + 1;
	}
}


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


int ans[N], c[N][K], st[K][K];
void dfs1(int x, int f){
	c[x][0]++;
	reg(i,x) if (v != f){
		dfs1(v, x);
		c[x][0] += c[v][0], c[x][0] %= M;
		rep(j,1,k) c[x][j] += c[v][j] + c[v][j - 1];
	}
	rep(j,1,k) c[x][j] %= M;
}
int C[K], fc[K];
void dfs2(int x, int f){
	rep(i,1,k)
		ans[x] += (c[x][i] + C[i]) * fc[i] % M * st[k][i] % M;
	ans[x] %= M;
	reg(i,x) if (v != f){
		C[0] += c[x][0] - c[v][0];
		rep(j,1,k) C[j] += c[x][j] - (c[v][j] + c[v][j - 1]), C[j] %= M;
		dep(j,k,1) C[j] += C[j - 1];
		dfs2(v, x);
		rep(j,1,k) C[j] -= C[j - 1];
		rep(j,1,k) C[j] -= c[x][j] - (c[v][j] + c[v][j - 1]), C[j] %= M;
		C[0] -= c[x][0] - c[v][0];
	}
}
void init(){
	fc[0] = 1;
	rep(i,1,k) fc[i] = (fc[i - 1] * i) % M;
	rep(i,1,k){
		st[i][1] = st[i][i] = 1;
		rep(j,2,i - 1)
			st[i][j] = (st[i - 1][j - 1] + j * st[i - 1][j]) % M;
	} 
}
int main(){
	Uncompress();
	//scanf("%d%d",&n,&k);rep(i,1,n - 1) scanf("%d%d",&a[i],&b[i]);
	init();
	rep(i,1,n - 1) ins(a[i], b[i]), ins(b[i], a[i]);
	dfs1(1,0);
	rep(i,0,k) C[i] = 0;
	dfs2(1,0);
	rep(i,1,n) {
		if (ans[i] < 0) ans[i] += M;
		printf("%d\n",ans[i]);
	}
} 

//c[x][0] = \sum_{i} 1
//c[x][j] = \sum_{i} C(dis(x,i), j)
//c[x][j] + c[x][j - 1]