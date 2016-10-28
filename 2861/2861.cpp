#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 100100, M = 200100;

struct edge{
	int to, pre;
}e[M * 2];
int u[N], l = 0;
void ins(int a, int b){
	e[++l] = (edge){b, u[a]}, u[a] = l;
}
#define v e[i].to
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)

int a[M], b[M], c[M], pre[N], dfs_clock = 0, low[N];
int st[N], top = 0, scc[N], cnt = 0;
void dfs(int x, int f){
	st[top++] = x;
	pre[x] = low[x] = ++dfs_clock;
	reg(i,x){
		if (!pre[v]) dfs(v, x), low[x] = min(low[x], low[v]);
		else if (!scc[v]) low[x] = min(low[x], pre[v]);
	}
	if (low[x] == pre[x]){
		st[top] = 0; cnt++;
		while (st[top] != x) top--, scc[st[top]] = cnt;
	}
}

void clear(){
	memset(u, 0, sizeof(u));
	l = 1;
}

int bcc[N];
void dfs2(int x, int from){//割边一定要用from而不是fa判！考虑重边的情况
	st[top++] = x;
	pre[x] = low[x] = ++dfs_clock;
	reg(i,x) if ((i ^ from) != 1){
		//if (x == 4) cout <<' '<<v<<' '<<i<<' '<<from<<endl;
		if (!pre[v]) dfs2(v, i), low[x] = min(low[x], low[v]);
		else low[x] = min(low[x], pre[v]);
	}
	if (low[x] == pre[x]){
		st[top] = 0; cnt++;
		while (st[top] != x) top--, bcc[st[top]] = cnt;
	}
	//cout <<x<<' '<<pre[x]<<' '<<low[x]<<endl;
}

int main(){
	int n, m; scanf("%d%d",&n,&m);
	rep(i,1,m) scanf("%d%d%d",&a[i],&b[i],&c[i]), c[i]--;
	rep(i,1,m) if (c[i]) ins(a[i], b[i]), ins(b[i], a[i]); else ins(a[i], b[i]);
	rep(i,1,n) if (!pre[i]) dfs(i,0);
	clear();
	//rep(i,1,n) cout <<scc[i]<<endl;
	rep(i,1,m) if (scc[a[i]] == scc[b[i]]) ins(a[i], b[i]), ins(b[i], a[i]);
	
	dfs_clock = top = 0; cnt = 0;
	rep(i,1,n) pre[i] = low[i] = 0;
	rep(i,1,n) if (!pre[i]) dfs2(i,0);
	
	int ans = 0;
	//rep(i,1,n) cout <<bcc[i]<<endl;
	rep(i,1,m) if (bcc[a[i]] == bcc[b[i]] && scc[a[i]] == scc[b[i]] && c[i]) ans++;
	printf("%d\n",ans);
	return 0;
}