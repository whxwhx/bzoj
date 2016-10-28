#include <map>
#include <cstdio>
#include <iostream>
#include <algorithm>
#define dep(i,a,b) for(int i = a; i >= b; i--)
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 50010, M = 11 * N;
struct point{
	int x, y, pos;
}a[N];
int prel[N], prer[N], pre[N], f[N], row[N], rl = 0;
map<int, int> L, R, up;
typedef map<int, int> :: iterator vit;
bool cmp(const point &a, const point &b){
	return a.y > b.y || (a.y == b.y && a.x < b.x);
}

int n; 
void init(){
	L.clear(), up.clear(), R.clear();
	rep(i,1,n) pre[i] = prel[i] = prer[i] = 0;
	
	rep(i,1,n){
		vit t;
		if ( (t = up.find(a[i].x)) != up.end() ) pre[i] = t->second, t->second = i; 
		else up[a[i].x] = i;
		if ( (t = L.find(a[i].x + a[i].y)) != L.end() ) prel[i] = t->second, t->second = i; 
		else L[a[i].x + a[i].y] = i; 
		if ( (t = R.find(a[i].x - a[i].y)) != R.end() ) prer[i] = t->second, t->second = i;
		else R[a[i].x - a[i].y] = i;
	}

	row[rl = 1] = a[1].y; rep(i,2,n) if (a[i].y != a[i - 1].y) row[++rl] = a[i].y;
}
int s1[N], s2[N], ans, g[N], T1[N], T2[N];
void calc_f(){
	rep(i,1,n) f[i] = 1;
	int j = 1;
	rep(i,1,rl){
		int t1 = j;
		for(;j <= n && a[j].y == row[i];j++){
			if (pre[j]) f[j] = max(f[j], f[pre[j]] + 1);
			if (prel[j]) f[j] = max(f[j], f[prel[j]] + 1);
			if (prer[j]) f[j] = max(f[j], f[prer[j]] + 1);
		}
		int t2 = j - 1;
		s1[t1 - 1] = s2[t2 + 1] = -n;
		rep(t,t1,t2) g[t] = f[t], T1[t] = t1, T2[t] = t2;
		rep(t,t1,t2) s1[t] = max(g[t] - t, s1[t - 1]);
		dep(t,t2,t1) s2[t] = max(g[t] + t, s2[t + 1]);
		rep(t,t1,t2) f[t] = max(f[t], s2[t + 1] - t1), f[t] = max(f[t], t2 + s1[t - 1]);
	}
}
int cnt = 0;
void print(int x){
	if (a[x].pos) printf("%d ",a[x].pos);
}
void print1(){
	printf("%d\n", f[n] - 1);
	for(int x = n; x;){
		int from = 0;
		rep(t,T1[x],x - 1) if (g[t] + T2[x] - t == f[x]) {from = t; break;} 
		if (from){
			rep(t,x,T2[x]) print(t);
			dep(t,x - 1,from) print(t);
		}else{
			rep(t,x + 1,T2[x]) if (g[t] + t - T1[x] == f[x]) {from = t; break;}
			if (from){
				dep(t,x,T1[x]) print(t);
				rep(t,x + 1,from) print(t);
			} else print(x), from = x;
		}

		int j = from;
		if (pre[j] && g[j] == f[pre[j]] + 1)
			x = pre[j];
		else if (prel[j] && g[j] == f[prel[j]] + 1)
			x = prel[j];
		else if (prer[j] && g[j] == f[prer[j]] + 1)
			x = prer[j];
		else 
			x = 0;
	}
	printf("\n");
}

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
int q[N], h[N], SS, TT;
bool bfs(){
    rep(i,0,TT) h[i] = -1;
    int l = 0, r = 1; q[h[SS] = 0] = SS;
    while (l < r){
        int x = q[l++];
        reg(i,x) if (ew && h[v] == -1) h[v] = h[x] + 1, q[r++] = v;
    }
    return h[TT] != -1;
}
int dfs(int x, int f){
    if (x == TT || f == 0) return f;
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

const int inf = 0x7fffffff;
int dinic(){
    int ans = 0;
    while (bfs()){
        rep(i,0,TT) cur[i] = u[i];
        ans += dfs(SS, inf);
    }
    return ans;
}

void add_edge(int a1, int b1){
	insert(SS, b1, 1), insert(a1, TT, 1), insert(a1, b1, inf);
}

int q1[N];
bool inq[N], t[N], vis[N];
void extend(int j, int &r){
	if (pre[j] && g[j] == f[pre[j]] + 1){
		add_edge(j, pre[j]); if (!inq[pre[j]]) q1[r++] = pre[j], inq[pre[j]] = 1;
	}
	if (prel[j] && g[j] == f[prel[j]] + 1){
		add_edge(j, prel[j]); if (!inq[prel[j]]) q1[r++] = prel[j], inq[prel[j]] = 1;
	}
	if (prer[j] && g[j] == f[prer[j]] + 1){
		add_edge(j, prer[j]); if (!inq[prer[j]]) q1[r++] = prer[j], inq[prer[j]] = 1;
	}

}
void bfs1(){
	rep(i,1,n) inq[i] = false;
	int l = 0, r = 1; q1[l] = n; inq[n] = true;
	while (l < r){
		int x = q1[l++];
		rep(t,T1[x],x - 1) if (g[t] + T2[x] - t == f[x]) {
			if (!vis[t]) extend(t, r), vis[t] = 1;
		}
		if (g[x] == f[x]) if (!vis[x]) extend(x, r), vis[x] = 1;//vis[x]=1! 不要出现重复！
		rep(t,x + 1,T2[x]) if (g[t] + t - T1[x] == f[x]) {
			if (!vis[t]) extend(t, r), vis[t] = 1;
		}
	}
	rep(i,1,n - 1) insert(S, i, inf), insert(i, T, inf);
}

void build(){
	S = n, T = 0;
	SS = n + 1, TT = n + 2;
	bfs1();
}

void calc2(){
	build();
	dinic();
	insert(T, S, inf);
	dinic();
	printf("%d\n",e[l].w);
}
int main(){
	scanf("%d",&n);
	rep(i,1,n) scanf("%d%d",&a[i].x,&a[i].y), a[i].pos = i;
	a[++n] = (point){0, 0, 0};
	sort(a + 1, a + n + 1, cmp);
	init();
	calc_f();
	print1();
	calc2();
	return 0;
}