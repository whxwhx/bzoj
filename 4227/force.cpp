#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
typedef long long LL;
using namespace std;
const int N = 100010, M = 200010;
int n, S;
struct edge{ int to, pre, c; }e[M * 2]; int u[N], l = 1;
void ins(int a, int b, int c) { e[++l] = (edge){b, u[a], c}, u[a] = l; }
#define v e[i].to
#define ec e[i].c
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)

bool fb[M];

const LL inf = 1000000000LL * N;
LL h[N]; int from[N]; bool vis[N];
typedef pair<LL, int> node;
#define mp(a,b) make_pair(a,b)
priority_queue<node> q;
void dij(){
	rep(i,1,n) h[i] = inf; h[S] = 0; q.push(mp(-h[S], S)); memset(vis, false, sizeof(vis));
	while (!q.empty()){
		int x = q.top().second; q.pop();
		if (vis[x]) continue; vis[x] = true;
		reg(i,x) if (!fb[i] && h[x] + ec < h[v]) from[v] = i, h[v] = h[x] + ec, q.push(mp(-h[v], v));
	}
}

LL h1[N];
int main(){
	int m; scanf("%d%d",&n,&m);
	rep(i,1,m){ int a, b, c; scanf("%d%d%d",&a,&b,&c); ins(a, b, c), ins(b, a, c); }
	scanf("%d",&S); dij();
	rep(i,1,n) h1[i] = h[i];
	int x = 6;
		int ans = 0;
		reg(i,x){
			int cnt = 0;
			fb[i] = fb[i^1] = true;
			dij(); rep(i,1,n) if (h1[i] != h[i]) cnt++, ans++;
			fb[i] = fb[i^1] = false;
			cout <<v<<' '<<cnt<<endl;
		}
		printf("%d\n",ans);
	return 0;
}