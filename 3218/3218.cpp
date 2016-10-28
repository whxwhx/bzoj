#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N = 5000 + 10, M = N * 51;
int n,a[N], b[N], w[N], l[N], r[N], p[N];

int cl;
int find(int x){
	int l = 0, r = cl;
	while (l + 1 < r){
		int mid = (l + r) >> 1;
		if (c[mid] < x) l = mid; else r = mid;
	}
	return r;
}
void init(){
	cl = 0;
	rep(i,1,n) c[++cl] = a[i], c[++cl] = l[i], c[++cl] = r[i];
	sort(c + 1, c + cl + 1); 
	cl = (int)(unique(c + 1, c + cl + 1) - c) - 1;
	rep(i,1,n) a[i] = find(a[i]), l[i] = find(l[i]), r[i] = find(r[i]);
}


struct edge{
	int to, pre, w;
}e[M * 2];
int l = 0, u[M];
void ins(int a, int b, int c){
	e[++l] = (edge){b, u[a], c}, u[a] = l;
}
void insert(int a, int b, int c){
	ins(a, b, c), ins(b, a, 0);
}
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)
#define ew e[i].w
#define v e[i].to

struct node{
	node *ch[2];
}T[M], *null = &T[0];
int tl = 0;
node *nn(){
	return T[++tl];
}
void ins(node *o, int l, int r, int a, int id){
	node *k = nn();
	if (l == r){
		
	}else{
		int mid = (l + r) >> 1;
		
	}
}

int S = 0, T;
void build(){
	null->ch[0] = null->ch[1] = null;
	rep(i,1,n) insert(S, i, w[i]);
	
}



int ans, cur[M], h[M], q[M];
bool bfs(){
	int l = 0, r = 1;
	rep(i,S,T) h[i] = -1;
	q[h[S] = 0] = S;
	while (l < r){
		int x = q[l++];
		reg(i,x) if (ew && h[v] == -1) h[v] = h[x] + 1, q[r++] = v;
	}
	return h[T] != -1;
}
int dfs(int x, int f){
	if (x == T) return f;
	int w, used = 0;
	for(int i = cur[x]; i; i = e[i].pre) if (ew && h[v] == h[x] + 1){
		w = min(ew, f - used), w = dfs(v, w);
		ew -= w; if (ew) cur[x] = i;
		e[i ^ 1] += w;
		used += w; if (used == f) break;
	}
	if (!used) h[x] = -1;
	return used;
}
void dinic(){
	int ans = 0;
	while (bfs()) {rep(i,S,T) cur[i] = u[i]; ans += dfs(S, inf);}
}


int main(){
	scanf("%d",&n):
	rep(i,1,n) scanf("%d%d%d%d%d%d", &a[i], &b[i], &w[i], &l[i], &r[i], &p[i]);
	init();
	build();
	dinic();
	printf("%d\n",ans);
}