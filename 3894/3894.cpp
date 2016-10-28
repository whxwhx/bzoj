/*
	我们考虑贡献2和3怎么处理
	假设
	S集表示选文
	T集表示选理
	贡献2我们就建一个点
	表示和i，j和相邻的点都选了文
	然后它往这些点连inf边，
	表示只要其中一个点选了理科（T集合）
	那么它就在T集合中。。
	然后就会割去S到它的代价为same_art的边
	然后贡献3类似处理即可
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
const int N = 3 * 110 * 110, dx[5] = {0,0,0,1,-1}, dy[5] = {0,1,-1,0,0}, inf = 1000000000, M = N * 10;

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

#define id(i,j) ((i - 1) * m + j)
int main(){
	int n, m, ans = 0; scanf("%d%d",&n,&m);
	S = 0, T = id(n,m) * 3 + 1;
	rep(i,1,n) rep(j,1,m) {
		int a;scanf("%d",&a);
		ans += a;
		insert(S, id(i,j), a);
	}
	rep(i,1,n) rep(j,1,m){
		int a; scanf("%d",&a);
		ans += a;
		insert(id(i,j), T, a);
	}
	int l = id(n, m);
	rep(i,1,n) rep(j,1,m){
		int a; scanf("%d",&a);
		l++;ans += a;
		insert(S, l, a);
		rep(k,0,4){
			int x = i + dx[k], y = j + dy[k];
			if (0 < x && x <= n && 0 < y && y <= m)
				insert(l, id(x,y), inf);
		}
	}
	rep(i,1,n) rep(j,1,m){
		int a; scanf("%d",&a);
		l++;ans += a;
		insert(l, T, a);
		rep(k,0,4){
			int x = i + dx[k], y = j + dy[k];
			if (0 < x && x <= n && 0 < y && y <= m)
				insert(id(x,y), l, inf);
		}
	}
	ans -= dinic();
	printf("%d\n",ans);
}