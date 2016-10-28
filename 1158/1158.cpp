#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 210, M = 100000;
int l[N], r[N], d[N];
int id1[N], id2[N], S, T, S0, T0;

const int inf = 1000000000;
struct edge{
    int to, pre, w;
}e[M * 3];
int cur[N], u[N], el = 1;//l = 1!
#define ew e[i].w
#define v e[i].to
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define ceg(i,a) for(int i = cur[a]; i; i = e[i].pre)
void ins(int a, int b, int w){
    e[++el] = (edge){b, u[a], w}, u[a] = el;
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

int sum;	
void insert(int a, int b, int l, int r){
	//cout <<a<<' '<<b<<' '<<l<<' '<<r<<endl;
	sum += l;
	insert(S, b, l), insert(a, b, r - l), insert(a, T, l);
}

int n, m;
void build(){
	el = 1;
	sum = 0;
	rep(i,S,T) u[i] = 0;
	rep(i,1,n) {
		if (id1[i] && id2[i]) insert(id1[i], id2[i], l[i], r[i]);
		else if (id1[i]) insert(id1[i], T0, l[i], r[i]);
		else if (id2[i]) insert(S0, id2[i], l[i], r[i]);
		else insert(S0, T0, l[i], r[i]);
	}
	rep(i,1,m){
		if (d[i] > 0) insert(S0, i, d[i], d[i]);
		if (d[i] < 0) insert(i, T0, -d[i], -d[i]);
	}
	insert(T0, S0, inf);//建图的时候不要忘记是可行流（循环），要连T到S的无穷大边！
}

bool check(){
	return dinic() == sum;
}
void work(int i, bool f){
	if (!f){
		int t = r[i];
		int L = l[i] - 1, R = r[i];
		while (L + 1 < R){
			int mid = (L + R) >> 1;
			r[i] = mid;
			build();
			if (check()) R = mid; else L = mid;
		}
		r[i] = t;
		printf("%d ",R);
	}else{
		int t = l[i];
		int L = l[i], R = r[i] + 1;
		while (L + 1 < R){
			int mid = (L + R) >> 1;
			l[i] = mid;
			build();
			if (check()) L = mid; else R = mid;
		}
		l[i] = t;
		printf("%d", L);
		if (i < n) printf(" ");
	}
}

int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,n) scanf("%d%d",&l[i],&r[i]);
	rep(i,1,m){
		int l0, r0;
		scanf("%d%d%d",&l0, &r0, &d[i]);
		rep(j,1,l0) {
			int x; scanf("%d",&x);
			id1[x] = i;
		}
		rep(j,1,r0) {
			int x; scanf("%d",&x);
			id2[x] = i;
		}	
	}
	S = 0, T = m + 3;
	S0 = m + 1, T0 = m + 2;
	build();
	if (!check()) printf("-1");
	else rep(i,1,n) work(i, 0), work(i, 1);
	return 0;
}