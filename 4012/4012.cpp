#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 150010;
int a[N];

struct edge{
	int to, pre, c;
}e[N * 2];
int u[N];
int l = 0;
void ins(int a, int b, int c){
	e[++l] = (edge){b, u[a], c}, u[a] = l;
}
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define v e[i].to
#define ec e[i].c

typedef long long LL;
int par[N], dep[N], dis[N][20];
int ch[N][4], cnt[N];
int s[N], sz[N], rt, vis[N], pch[N], sum;
vector< pair<int, int> > sbt[N][4];
vector<LL> S[N][4];
#define pb(a) push_back(a)

#define mp(a,b) make_pair(a,b)

void getrt(int x, int f){
	s[x] = 0, sz[x] = 1;
	reg(i,x) if (v != f && !vis[v]) getrt(v, x), s[x] = max(s[x], sz[v]), sz[x] += sz[v];
	s[x] = max(s[x], sum - sz[x]);
	if (s[x] < s[rt]) rt = x;
}

void dfs(int x, int f, int ds){
	dis[x][++dep[x]] = ds;
	reg(i,x) if (v != f && !vis[v]) dfs(v, x, ds + ec);
}

void dfs1(int x, int f, int ds, int rt, int sub){
	sbt[rt][sub].pb(mp(a[x], ds));
	reg(i,x) if (v != f && !vis[v]) dfs1(v, x, ds + ec, rt, sub);
}

#define sbt sbt[x][cnt[x]]
#define S S[x][cnt[x]]
void work(int x){
	vis[x] = 1;
	dfs(x,0,0);
	cnt[x] = 0;
	reg(i,x) if (!vis[v]){
		sum = sz[v], rt = 0, getrt(v, x);
		ch[x][++cnt[x]] = rt, par[rt] = x, pch[rt] = cnt[x];

		dfs1(v, x, ec, x, cnt[x]); sort(sbt.begin(), sbt.end());

		S.pb(sbt[0].second);
		for(int j = 1; j < sbt.size(); j++) S.pb(S[j - 1] + sbt[j].second);
		work(rt);
	}
}
#undef sbt
#undef S
int n;
void build(){
	s[rt = 0] = sum = n, getrt(1,0);
	work(rt);
}

#define sbt sbt[x][c]
int find(int x, int c, int D){
	int l = -1, r = sbt.size();//[l,r)
	while (l + 1 < r){
		int mid = (l + r) >> 1;
		if (sbt[mid].first <= D) l = mid; else r = mid;
	}
	return l;
}
#undef sbt
#define Sx(a) (a < 0 ? 0 : S[x][c][a])
LL calc(int x, int c, int L, int R, int dep){
	int x1 = find(x,c,L - 1), x2 = find(x,c,R);
	return 1LL * (x2 - x1) * dep + Sx(x2) - Sx(x1);
}

LL qry(int x, int L, int R){
	int c = -1;
	LL ans = 0;
	for(int w = x; w; w = par[w]){
		rep(i,1,cnt[w]) if (i != c) ans += calc(w, i, L, R, dis[x][dep[w]]);//children of w
		if (L <= a[w] && a[w] <= R) ans += dis[x][dep[w]];//w itself
		c = pch[w];
	}
	return ans;
}

int main(){
	int Q, A; scanf("%d%d%d",&n,&Q,&A);
	rep(i,1,n) scanf("%d",&a[i]);
	rep(i,1,n - 1){
		int a, b, c; scanf("%d%d%d",&a,&b,&c);
		ins(a, b, c), ins(b, a, c);
	}
	build();
	/*rep(i,1,n){
		cout <<i<<endl;
		rep(j,1,cnt[i]){
			cout <<' '<<j<<endl;
			rep(k,0,((int)sbt[i][j].size()) - 1) cout <<"  "<<k<<' '<<sbt[i][j][k].first<<endl;
		}
	}*/
	LL lastans = 0;
	rep(i,1,Q){
		int u, a, b; scanf("%d%d%d",&u,&a,&b);
		int L = (a + lastans) % A, R = (b + lastans) % A;
		if (L > R) swap(L, R);
		printf("%lld\n",lastans = qry(u, L, R));
	}
	return 0;
}