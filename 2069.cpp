#include <iostream>
#include <queue>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
const int N = 100000;
#define mp(a,b) make_pair(a,b)

struct Edge{
	int a, b, c, d;
}E[N];
bool operator < (const Edge &a, const Edge &b){
	return a.a < b.a || (a.a == b.a) && a.b < b.b;
}

struct edge{
	int to, pre, c;
}e[N * 2];
int u[N], l = 0;
void ins(int a, int b, int c){
	e[++l] = (edge){b, u[a], c}, u[a] = l;
}
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define v e[i].to
#define ec e[i].c

const int inf = 500000000;
typedef pair<int, int> node;
priority_queue<node> q;
int kl, ky[N], d1[N], d2[N], dis[N], n, ans = inf;
bool vis[N];

void solve(int j, int t){
	rep(i,1,n) dis[i] = -1, vis[i] = 0;
	rep(i,1,kl) if ((i >> j & 1) == t) {
		int x = ky[i];
		dis[x] = d1[i];
		q.push(mp(-dis[x], x));
	}
	while (!q.empty()){
		int x= q.top().second; q.pop();
		if (vis[x]) continue; else vis[x] = 1;
		reg(i,x) if (dis[v] == -1 || dis[x] + ec < dis[v])
			dis[v] = dis[x] + ec, q.push(mp(-dis[v], v));
	}
	rep(i,1,kl) if ((i >> j & 1) != t) {
		int x = ky[i];
		if (dis[x] > -1) ans = min(ans, dis[x] + d2[i]);
	}
}
int main(){
	int m; scanf("%d%d",&n,&m);
	rep(i,1,m) {
		scanf("%d%d%d%d",&E[i].a,&E[i].b,&E[i].c,&E[i].d);
		if (E[i].a > E[i].b) swap(E[i].a, E[i].b), swap(E[i].c, E[i].d);
	}
	sort(E + 1, E + m + 1);
	dep(i,m - 1,1) if (E[i].a == E[i + 1].a && E[i].b == E[i + 1].b) E[i].c = min(E[i].c, E[i + 1].c), E[i].d = min(E[i].d, E[i + 1].d);
	rep(i,1,m) if ((E[i].a != E[i - 1].a || E[i].b != E[i - 1].b) && E[i].a != E[i].b){
		int a = E[i].a, b = E[i].b, c = E[i].c, d = E[i].d;
		if (a == 1){
			ky[++kl] = b, d1[kl] = c, d2[kl] = d;
		}else ins(a, b, c), ins(b, a, d);
	}
	rep(i,0,19) if ((kl >> i) != 0) solve(i, 0), solve(i, 1); else break;
	printf("%d\n",ans);
}
