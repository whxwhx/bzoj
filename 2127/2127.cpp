/*
	划分两个集合
	选择文/理有个喜悦值
	两个点同时选了文/理有个喜悦值
	简单列个方程即可。。
	由于这里关系是对称的。。
	所以不妨设a = a_1 = a_2
	假设
	W是同时选文喜悦（也就是选理代价）
	L是同时选理喜悦（也就是选文代价）
	那么选不同的代价就是W+L
	2a = W
	2b = L
	a + b + e = W + L
	从而
	a = W/2
	b = L/2
	e = (W+L)/2
	方便起见权值直接全部*2变成整数
	(注意单独一个点的W和L也要*2)
	不需要反转源和汇
*/
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
int S, T;
const int N = 110 * 110, M = N * 7, inf = 1000000000;
struct edge{
    int to, pre, w;
}e[M * 2];
int cur[N], u[N], l = 1;//l = 1!
#define ew e[i].w
#define v e[i].to
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define ceg(i,a) for(int i = cur[a]; i; i = e[i].pre)
void ins(int a, int b, int w){
    e[++l] = (edge){b, u[a], w}, u[a] = l;
}
void insert(int a, int b, int w){//used insert to add an edge instead of using ins!
    ins(a, b, w), ins(b, a, 0);
}
int q[N], h[N];
bool bfs(){
    rep(i,S,T) h[i] = -1;
    int l = 0, r = 1; q[h[S] = 0] = S;
    while (l < r){
        int x = q[l++];
        reg(i,x) if (ew && h[v] == -1) h[v] = h[x] + 1, q[r++] = v;
    }
    return h[T] != -1;
}
int dfs(int x, int f){
    if (x == T || f == 0) return f;
    int used = 0, w;
    ceg(i,x)if (ew && h[v] == h[x] + 1){
        w = min(ew, f - used), w = dfs(v, w);
        ew -= w; if (ew) cur[x] = i;
        e[i^1].w += w;
        used += w; if (used == f) break;
    }
    if (!used) h[x] = -1;
    return used;
}
int dinic(){
    int ans = 0;
    while (bfs()){
        rep(i,S,T) cur[i] = u[i];
        ans += dfs(S, inf);
    }
    return ans;
}
#define id(i,j) ((i - 1) * m + j)
int Sx[N], xT[N], ans;
int main(){
	int n, m; scanf("%d%d",&n,&m);
	//S集表示选文，T集表示选理
	rep(i,1,n) rep(j,1,m){
		int a;
		scanf("%d",&a);ans += a;
		Sx[id(i,j)] = a * 2;
	}
	rep(i,1,n) rep(j,1,m){
		int a;
		scanf("%d",&a);ans += a;
		xT[id(i,j)] = a * 2;
	}
	rep(i,1,n - 1) rep(j,1,m){
		int a;
		scanf("%d",&a);ans += a;
		Sx[id(i,j)] += a;
		Sx[id(i + 1, j)] += a;
		ins(id(i, j), id(i + 1,j), a);
		ins(id(i + 1, j), id(i,j), a);
	}
	rep(i,1,n - 1) rep(j,1,m){
		int a;
		scanf("%d",&a);ans += a;
		xT[id(i,j)] += a;
		xT[id(i + 1, j)] += a;
		ins(id(i,j), id(i + 1, j), a);
		ins(id(i + 1, j), id(i,j), a);
	}
	rep(i,1,n) rep(j,1,m - 1){
		int a;
		scanf("%d",&a);ans += a;
		Sx[id(i,j)] += a;
		Sx[id(i,j + 1)] += a;
		ins(id(i, j), id(i,j + 1), a);
		ins(id(i, j + 1), id(i,j), a);
	}
	rep(i,1,n) rep(j,1,m - 1){
		int a;
		scanf("%d",&a);ans += a;
		xT[id(i,j)] += a;
		xT[id(i,j + 1)] += a;
		ins(id(i, j), id(i,j + 1), a);
		ins(id(i, j + 1), id(i,j), a);
	}
	S = 0, T = id(n,m) + 1;
	rep(i,1,n) rep(j,1,m){
		int x = id(i,j);
		insert(S, x, Sx[x]);
		insert(x, T, xT[x]);
	}
	ans -= dinic() / 2;
	printf("%d",ans);
	return 0;
}