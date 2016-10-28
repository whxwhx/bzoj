#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;

const int N = 3010, M = 4000010;

namespace MST{
	int n;

	struct edge{ int to, pre; double c; }e[M]; int l = 0, u[N];
	void ins(int a, int b, double c) { if (a != b) { e[++l] = (edge){b, u[a], c}; u[a] = l;} }
	#define v e[i].to
	#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
	#define ec e[i].c

	double ans = 0;
	int ch[N]; double mn[N];
	bool vis[N];
	int del[N];

	void mark(int i){
		int x = i; n++;
		while (!del[x]) del[x] = n, ans += mn[x], x = ch[x];
	}

	void reduce(){
		rep(x,1,n) if (del[x] == n) {
			reg(i,x) if (!del[v]) ins(n, v, ec);
		}else if (!del[x]){
			reg(i,x) if (del[v] == n) ins(x, n, ec - mn[v]);
		}
	}

	bool mst(int rt){
		memset(ch, 0, sizeof(ch)); memset(vis, false, sizeof(vis)); vis[0] = true;
		rep(x,1,n) if (!del[x]) reg(i,x) if (!ch[v] || ec < mn[v]) mn[v] = ec, ch[v] = x;
		mn[rt] = ch[rt] = 0;	

		bool flag = false;
		rep(i,1,n) if (!vis[i] && !del[i]) {
			int x = i; while (!vis[x]) vis[x] = true, x = ch[x];
			if (x == i) flag = true, mark(x), reduce();
		}
		return flag;
	}
	double solve(int rt){
		while (mst(rt)); 
		rep(i,1,n) if (!del[i]) ans += mn[i]; return ans;
	}

	void dfs(int x){
		vis[x] = true; reg(i,x) if (!vis[v]) dfs(v);
	}
	bool check(int rt){
		dfs(rt); rep(i,1,n) if (!vis[i]) return false;
		return true;
	}
	void clear(){
		ans = 0;
		memset(u, 0, sizeof(u)); memset(vis, false, sizeof(vis)); l = 0; memset(del, 0, sizeof(del));
	}
}

double x[N], y[N];
int main(){
	int n, m;
	while (scanf("%d%d",&n,&m) == 2){
		MST::n = n; MST::clear();
		rep(i,1,n) scanf("%lf%lf",&x[i],&y[i]);
		rep(i,1,m){
			int a, b; scanf("%d%d",&a,&b);
			double c = sqrt((x[b] - x[a]) * (x[b] - x[a]) + (y[b] - y[a]) * (y[b] - y[a]));
			MST::ins(a, b, c);
		}
		if (!MST::check(1)) printf("poor snoopy\n"); else printf("%.2lf\n",MST::solve(1));
	}
	return 0;
}