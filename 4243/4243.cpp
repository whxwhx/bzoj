#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;

const int N = 200000 + 10;
int f[N], s[N];
int find(int x){
	return f[x] == x ? x : f[x] = find(f[x]);
}
void Union(int a, int b){
	int fa = find(a), fb = find(b);
	if (fa != fb){
		s[fa] += s[fb];
		f[fb] = fa;
	}
}

int n, m;
struct edge{int to, pre;}e[N * 4];
int u[N], l = 0;
void ins(int a, int b){e[++l] = (edge){b, u[a]}, u[a] = l;} 
#define v e[i].to
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)

struct E{int a,b,c;}ed[N * 2];
bool operator < (const E &a, const E &b){
	return (a.a < b.a) || (a.a == b.a && a.b < b.b) || (a.a == b.a && a.b == b.b && a.c < b.c);
} 

bool vis[N];
int q[N];

void bfs(){
	int l = 0, r = 0;
	rep(i,1,n) if (vis[i]) q[r++] = i;
	while (l < r){
		int x = q[l++];
		reg(i,x) if (vis[v]) Union(x, v); else {
			vis[v] = 1, q[r++] = v;
			Union(x, v);
		}
	}
}


int main(){
	scanf("%d%d",&n,&m);
	int a, b;
	rep(i,1,n) s[i] = 1, f[i] = i, vis[i] = 0;
	rep(i,1,m) {
		scanf("%d%d",&a,&b);
		if (a < b) ed[i] = (E){a, b, 0}; else ed[i] = (E){b, a, 1};
	}
	sort(ed + 1, ed + m + 1);

	rep(i,1,m){
		if (i < m && ed[i].a == ed[i + 1].a && ed[i].b == ed[i + 1].b)
			Union(ed[i].a, ed[i].b), vis[ed[i].a] = vis[ed[i].b] = 1; 
		if (ed[i].c == 1) ins(ed[i].b, ed[i].a); else ins(ed[i].a, ed[i].b);
	}
	rep(x,1,n){
		int flag = 0, cnt = 0;
		reg(i,x){
			if (flag) Union(v, flag); else flag = v;
			cnt++;
		}
		if (cnt > 1) reg(i,x) vis[v] = 1;
	}

	bfs();
	long long ans = 0;
	rep(i,1,n) if (f[i] == i) ans += 1LL * s[i] * (s[i] - 1);
	rep(i,1,m){
		int a = ed[i].a, b = ed[i].b;
		if (find(a) != find(b)) ans++;
	}
	printf("%lld\n",ans);
	return 0;
}