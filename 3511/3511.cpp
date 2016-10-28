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

const int N = 10010, M = 40010 + N * 3, inf = 1000000000;

int S, T;
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

int Sx[N], xT[N];
int main(){
	int n, m; scanf("%d%d",&n,&m);
	int ans = 0;
	S = 0, T = n + 1;
	Sx[1] = inf;
	rep(i,2,n - 1) {
		int a; scanf("%d",&a); ans += a;
		Sx[i] = a * 2;
	}
	insert(n,T,inf);
	rep(i,2,n - 1){
		int a; scanf("%d",&a); ans += a;
		xT[i] = a * 2;
	}
	rep(i,1,m){
		int x, y, a, b, c; scanf("%d%d%d%d%d",&x,&y,&a,&b,&c);
		ans += a + b;
		Sx[x] += a, Sx[y] += a;
		xT[x] += b, xT[y] += b;
		ins(x, y, a + b + c * 2), ins(y, x, a + b + c * 2);
	}
	rep(i,1,n) {
		if (Sx[i]) insert(S, i, Sx[i]);
		if (xT[i]) insert(i, T, xT[i]);
	}
	ans -= dinic() / 2;
	printf("%d",ans);
	return 0;
}