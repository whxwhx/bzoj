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
#define Rep(i,a) for(int i = 0; i < a; i++)
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
#define ab(a) ((a) > 0 ? (a) : -(a))
#define mp(a,b) make_pair(a,b)
#define pb(a) push_back(a)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
const int N = 510, M = 510;
struct edge{
	int to, pre;
}e[M * 2];
int u[N];
int l = 0;
void ins(int a, int b){
	e[++l] = (edge){b, u[a]}, u[a] = l;
}
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define v e[i].to

int n, m;
int dfs_clock, pre[N], low[N];
bool cut[N];
void dfs(int x, int f){
	pre[x] = low[x] = ++dfs_clock; int cnt = 0;
	reg(i,x) if (v != f){
		if (!pre[v]) {
			dfs(v, x), low[x] = min(low[x], low[v]);
			if (low[v] >= pre[x]) cut[x] = 1;//for every child must go up
		}
		else low[x] = min(low[x], pre[v]);
		cnt++;
	}
	if (f == 0 && cnt == 1) cut[x] = 0;//root
}
void tarjan(){
	dfs_clock = 0;
	rep(i,1,n) cut[i] = pre[i] = 0;
	rep(i,1,n) if (!pre[i]) dfs(i,0);
}

bool vis[N];
uLL ans;
int cnt, s[N];
bool calc(int x){
	vis[x] = s[x] = 1;
	bool flag = 0;
	reg(i,x) if (!vis[v]) {
		if (calc(v)) flag = 1;
		else if (cut[x]) cnt++, ans *= s[v];
		s[x] += s[v];
	}
	if (cut[x]) flag = 1;
	return flag;
}
int cases = 0;
void work(){
	++cases;
	n = 500;
	l = 0; rep(i,1,n) u[i] = 0;
	n = 0;
	rep(i,1,m){
		int a, b; scanf("%d%d",&a,&b), ins(a, b), ins(b, a);
		n = max(n, a), n = max(n, b);
	}
	tarjan();
	cnt = 0, ans = 1;
	rep(i,1,n) vis[i] = 0;
	rep(i,1,n) if (!vis[i]) {
		if (!calc(i)) {
			if (s[i] == 1) cnt++, ans *= s[i]; else cnt += 2, ans *= 1LL * s[i] * (s[i] - 1) / 2;
		}
		
	printf("%d %lld\n",cnt,ans);
}
int main(){
	while (scanf("%d",&m)) if (m == 0) break; else work();
}