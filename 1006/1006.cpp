#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++) 
using namespace std;
const int N = 100010, M = 1000010;

struct edge{ int to, pre; } e[M * 2]; int l = 0, u[N];
void ins(int a, int b) { e[++l] = (edge){b, u[a]}, u[a] = l; }
#define v e[i].to
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)

int d[N]; bool vis[N];
vector<int> nd[N];
#define pb(a) push_back(a)
int mx = 0;

int main(){
	int n, m; scanf("%d%d",&n,&m);
	rep(i,1,m){ int a, b; scanf("%d%d",&a,&b); ins(a,b); ins(b,a); } 
	rep(i,1,n) nd[0].pb(i);
	int ans = 0;
	rep(i,1,n){
		int x = 0;
		while (!x){
			int l = nd[mx].size();
			while (l > 0 && vis[ nd[mx][l - 1] ] ) nd[mx].pop_back(), l--;
			if (l > 0) x = nd[mx][l - 1], nd[mx].pop_back(); else mx--;
		}
		int cnt = 0; vis[x] = true;
		reg(i,x) if (vis[v]) cnt++; else { d[v]++; nd[d[v]].pb(v); mx = max(mx, d[v]); }
		ans = max(ans, cnt + 1);
	}
	printf("%d\n",ans);
	return 0; 
}