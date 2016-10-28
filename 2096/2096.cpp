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

const int M = 50010;
int key[M], d[M], d1[M], kl = 0, ans = 0x7fffffff;
#define min(a,b) ((a) < (b) ? (a) : (b))

struct edge{
	int to, pre, c;
}e[M * 2];
int u[M];
int l = 0;
void ins(int a, int b, int c){
	e[++l] = (edge){b, u[a], c}, u[a] = l;
}
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define v e[i].to
#define ec e[i].c

int dis[M];
bool vis[M];
typedef pair<int, int> dijnode;
priority_queue<dijnode> q;

int n, m;
void solve(int j){
	rep(i,1,n) dis[i] = 0x7fffffff, vis[i] = 0;
	rep(i,1,kl) if (i >> j & 1) dis[key[i]] = d[i], q.push(mp(-dis[key[i]], key[i]));
	while (!q.empty()){
		int x = q.top().second; q.pop();
		if (vis[x]) continue;
		vis[x] = 1;
		reg(i,x) if (dis[x] + ec < dis[v])
			dis[v] = dis[x] + ec, q.push(mp(-dis[v], v));
	}
	rep(i,1,kl) if (!(i >> j & 1)) ans = min(ans, dis[key[i]] + d1[i]);


	rep(i,1,n) dis[i] = 0x7fffffff, vis[i] = 0;
	rep(i,1,kl) if (!(i >> j & 1)) dis[key[i]] = d[i], q.push(mp(-dis[key[i]], key[i]));
	while (!q.empty()){
		int x = q.top().second; q.pop();
		if (vis[x]) continue;
		vis[x] = 1;
		reg(i,x) if (dis[x] + ec < dis[v])
			dis[v] = dis[x] + ec, q.push(mp(-dis[v], v));
	}
	rep(i,1,kl) if (i >> j & 1) ans = min(ans, dis[key[i]] + d1[i]);
}

int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,m){
		int a, b, c, dd; scanf("%d%d%d%d",&a,&b,&c,&dd);
		if (a > b) {swap(a, b), swap(c, dd);}
		if (a == 1) key[++kl] = b, d[kl] = c, d1[kl] = dd; else
			ins(a, b, c), ins(b, a, dd);
	}
	rep(i,0,19) if ((1 << i) <= kl) solve(i); else break;
	printf("%d\n",ans);
	return 0;
}