#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;

const int N = 3010, M = 4000010;

namespace MST{
	int n;

	struct edge{ int to, pre; double c; }e[M]; int l = 0, u[N];
	void ins(int a, int b, double c) { if (a != b) e[++l] = (edge){b, u[a], c}, u[a] = l; }
	#define v e[i].to
	#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
	#define ec e[i].c

	double ans = 0;
	int ch[N]; double mn[N];
	int vis[N], del[N];

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
		memset(ch, 0, sizeof(ch)); memset(vis, 0, sizeof(vis)); vis[0] = -1;
		rep(x,1,n) if (!del[x]) reg(i,x) if (ch[v] == 0 || ec < mn[v]) mn[v] = ec, ch[v] = x;
		mn[rt] = ch[rt] = 0;

		bool flag = false;
		rep(i,1,n) if (!vis[i] && !del[i]) {
			int x = i; while (!vis[x]) vis[x] = i, x = ch[x];
			if (vis[x] == i) flag = true, mark(x), reduce();//在环套树上找环一定要判是不是这次走走出来的。。
		}
		return flag;
	}
	double solve(int rt){
		while (mst(rt)); 
		rep(i,1,n) if (!del[i]) ans += mn[i]; return ans;
	}
}

int b[N];
double mn[N];
int main(){
	int n; scanf("%d",&n); MST::n = n + 1;
	rep(i,1,n){ 
		double a; scanf("%lf%d",&a,&b[i]); 
		if (b[i]) { MST::ins(1, i + 1, a); mn[i] = a; } else MST::del[i + 1] = 1000000000;
	}
	int k; scanf("%d",&k);
	rep(i,1,k){ int x, y; double z; scanf("%d%d%lf",&x,&y,&z); if (b[x] && b[y] && x != y) { MST::ins(x + 1, y + 1, z); mn[y] = min(mn[y], z); } }
	double sum = 0; rep(i,1,n) if (b[i]) sum += mn[i] * (b[i] - 1);
	printf("%.2lf\n",sum + MST::solve(1));
	return 0;
}