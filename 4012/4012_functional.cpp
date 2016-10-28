#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
typedef long long LL;
using namespace std;
const int N = 150010;

struct edge{
	int to, pre, c;
}e[N * 2];
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define v e[i].to
#define ec e[i].c
int u[N], el = 0;
void ins(int a, int b, int c){
	e[++el] = (edge){b, u[a], c}, u[a] = el;
}

int n;
bool vis[N];
int sum, sz[N], s[N], rt;
int par[N], dis[N][25], dep[N], pch[N];
void getrt(int x, int f){
	sz[x] = 1, s[x] = 0;
	reg(i,x) if (v != f && !vis[v])
		getrt(v, x), sz[x] += sz[v], s[x] = max(s[x], sz[v]);
	s[x] = max(s[x], sum - sz[x]);
	if (s[x] < s[rt]) rt = x;
}
void dfs(int x, int f, int d){
	dis[x][++dep[x]] = d;
	reg(i,x) if (v != f && !vis[v])
		dfs(v, x, d + ec);
}
void work(int x){
	vis[x] = 1;
	dfs(x, 0, 0);
	int tmp = sum - sz[x], cl = 0;
	reg(i,x) if (!vis[v]){
		sum = sz[v] < sz[x] ? sz[v] : tmp; 
		rt = 0, getrt(v, x);
		par[rt] = x, pch[rt] = cl++;
		work(rt);
	}
}
void build(){
	s[rt = 0] = sum = n, getrt(1,0);
	work(rt);
}

struct node{
	node *ch[3];
	LL s[3], s0[3], S, S0;
}T[N * 30], *null = &T[0], *root[N];
int Tl = 0;
void init(){
	null->ch[0] = null->ch[1] = null->ch[2] = null;
	null->s[0] = null->s[1] = null->s[2] = 0;
}
node *nn(){
	return &T[++Tl];
}
int pc[N];
node *pt[N];
node* add(node *rt, int x){
	int t = dep[x] - 1, k = x;
	dep(i,t,1) pc[i] = pch[x], x = par[x];
	x = k;

	node *o = rt;
	rep(i,1,t){
		pt[i] = nn(), *pt[i] = *o;

		pt[i]->s[pc[i]] += dis[x][i]; 
		pt[i]->S += dis[x][i];

		pt[i]->s0[pc[i]]++; 
		pt[i]->S0++;
		
		o = o->ch[pc[i]];
	}
	pt[t + 1] = nn(), *pt[t + 1] = *o, pt[t + 1]->S0++;
	dep(i,t,1) pt[i]->ch[pc[i]] = pt[i + 1];

	return pt[1];
}

LL S(node *rt, int x){
	int t = dep[x] - 1, k = x;
	dep(i,t,1) pc[i] = pch[x], x = par[x];
	x = k;

	node *o = rt;
	LL ans = 0;
	rep(i,1,t){
		ans += o->S - o->s[pc[i]];
		ans += (o->S0 - o->s0[pc[i]]) * dis[x][i];
		o = o->ch[pc[i]];
	}
	ans += o->S;
	return ans;
}

typedef pair<int, int> nd;
nd a[N];
int find(int x){
	int l = 0, r = n + 1;
	while (l + 1 < r){
		int mid = (l + r) >> 1;
		if (a[mid].first <= x) l = mid; else r = mid;
	}
	return l;
}

int main(){
	int Q, A; scanf("%d%d%d",&n,&Q,&A);
	rep(i,1,n) scanf("%d",&a[i].first), a[i].second = i;
	sort(a + 1, a + n + 1);
	rep(i,1,n - 1){
		int a, b, c;scanf("%d%d%d",&a,&b,&c);
		ins(a,b,c), ins(b,a,c);
	}
	build();
	init();
	root[0] = null;
	rep(i,1,n) root[i] = add(root[i - 1], a[i].second);
	LL ans = 0;
	a[0].first = -1;
	rep(i,1,Q){
		int x, a, b; scanf("%d%d%d",&x,&a,&b);
		a = (a + ans) % A, b = (b + ans) % A;
		if (a > b) swap(a,b);
		a = find(a - 1), b = find(b);
		printf("%lld\n",ans = (S(root[b], x) - S(root[a], x)));
	}
	return 0;
}