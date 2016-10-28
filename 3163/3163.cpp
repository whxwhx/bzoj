#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
const int N = 1010;
int a[N], b[N], c[N];
struct LT{
	struct edge{
		int to, pre, c;
	}e[400000];
	int u[N * 4], l;
	LT(){
		l = 0;
	}
	void ins(int a, int b, int c){
		 e[++l] = (edge){b, u[a], c}, u[a] = l;
	}
}tag, q;

void add(int x, int l, int r, int a, int b, int d){
	if (a > b) return;
	if (a <= l && r <= b) tag.ins(x, d, 0);
	else {
		int mid = (l + r) >> 1, lc = x << 1, rc = (x << 1) + 1;
		if (a <= mid) add(lc, l, mid, a, b, d);
		if (b >  mid) add(rc, mid + 1, r, a, b, d);
	}
}

int ans[300010], top = 0, f[N][N], g[N];
void add_g(int a, int b){
	dep(i,N - 1,a) g[i] = max(g[i - a] + b, g[i]);
}
void Add(int x){
	int n = c[x];
	rep(i,0,N - 1) g[i] = f[top][i];
	for(int i = 1; i <= n; i <<= 1) add_g(a[x] * i, b[x] * i), n -= i;
	if (n) add_g(a[x] * n, b[x] * n);
	top++;
	rep(i,0,N - 1) f[top][i] = g[i];
}
void dfs(int x, int l, int r){
	int t = top, mid = (l + r) >> 1, lc = x << 1, rc = (x << 1) + 1;
	for(int i = tag.u[x]; i; i = tag.e[i].pre) Add(tag.e[i].to);
	if (l == r) {
		for(int i = q.u[l]; i; i = q.e[i].pre) 
			ans[q.e[i].c] = f[top][q.e[i].to];
	}else dfs(lc, l, mid), dfs(rc, mid + 1, r);
	top = t;
}


int main(){
	int n; scanf("%d",&n);
	rep(i,1,n) scanf("%d%d%d",&a[i],&b[i],&c[i]);
	rep(i,1,n) add(1, 1, n, 1, i - 1, i), add(1, 1, n, i + 1, n, i);
	int m; scanf("%d",&m);
	rep(i,1,m){
		int x, e; scanf("%d%d",&x,&e); x++;
		q.ins(x, e, i);
	}
	dfs(1, 1, n);
	rep(i,1,m) printf("%d\n",ans[i]);
	return 0;
}