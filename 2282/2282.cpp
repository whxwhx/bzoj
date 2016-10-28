#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
int n, s;

const int N = 300100;
struct edge{
	int to, pre, c;
}e[N * 2];
int u[N];
int l = 0;
void ins(int a, int b, int c){
	e[++l] = (edge){b, u[a], c}, u[a] = l;
}
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define v e[i].to
#define ec e[i].c

int dis[N], fa[N], dep[N];
void dfs(int x, int f){
	reg(i,x) if (v != f) dep[v] = dep[x] + 1, fa[v] = x, dis[v] = dis[x] + ec, dfs(v, x);
}

int q[N], Dn, h, a, b;

void geth(int x, int f, int dis){
	h = max(dis, h);
	reg(i,x) if (v != f) geth(v, x, dis + ec);
}

void getD(){
	dis[1] = 0, dfs(1,0);
	a = 1;
	rep(i,2,n) if (dis[i] > dis[a]) a = i;
	dis[a] = 0, dep[a] = 1, dfs(a, 0);
	b = 1;
	rep(i,2,n) if (dis[i] > dis[b]) b = i;
	
	Dn = dep[b];
	int t = b;
	dep(i,Dn,1) q[i] = b, b = fa[b];
	b = t;

	rep(j,1,Dn){
		int x = q[j];
		reg(i,x) if (v != q[j - 1] && v != q[j + 1]) geth(v, x, ec);
	}
}

#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))
int ans = 0x7fffffff;
void calc(){
	int j = 1;
	rep(i,1,Dn){
		int x = q[i];
		while (dis[x] - dis[q[j]] > s) j++;
		ans = min(ans, max(h, max( dis[q[j]], dis[b] - dis[x] ) ) );
	}
}

int main(){
	scanf("%d%d",&n,&s);
	rep(i,1,n - 1) {
		int a, b, c; scanf("%d%d%d",&a,&b,&c);
		ins(a, b, c), ins(b, a, c);
	}
	getD();
	calc();
	printf("%d\n",ans);
	return 0;
}