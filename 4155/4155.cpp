#include <iostream>
#include <cstdio>
#include <algorithm>
#include <bitset>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 40100, M = 40100, inf = 1000000000;

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
void insert(int a, int b, int w){
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

int d[N];
int ab(int x){
	return x < 0 ? -x : x;
}
bitset<N> f;
#define min(a,b) ((a) < (b) ? (a) : (b))
void work(){
	int n, m; scanf("%d%d",&n,&m);
	S = 0, T = n + 1;

	l = 1; rep(i,S,T) u[i] = d[i] = 0;
	insert(S, 1, 1000000);
	insert(2, T, 1000000);
	rep(i,1,m){
		int a, b; scanf("%d%d",&a,&b);
		d[a]++, d[b]++;
		ins(a, b, 1), ins(b, a, 1);
	}
	printf("%d ",m - dinic());

	f = 0, f[d[1]] = 1;
	rep(i,3,n) f |= f << d[i];
	int sum = 0;rep(i,1,n) sum += d[i];
	int ans = 1000000000;
	rep(i,0,m * 2) if (f[i])
		ans = min(ans, ab(i - (sum - i)) / 2);
	printf("%d\n",ans);
}
int main(){
	int T; scanf("%d",&T);
	while (T--) work();
}