#include <iostream>
#include <cstdio>
#include <algorithm>
#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))
#define upd(a,b) ((a == -1) ? (a = b) : (a = min(a,b)))
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 200010;
int fa[N], p[N];

typedef long long LL;
LL f[N], q[N], s[N], l[N];
struct edge{
	int to, pre;
}e[N * 2];
int el = 0, u[N];
void ins(int a, int b){
	e[++el] = (edge){b, u[a]}, u[a] = el;
}
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define v e[i].to

int s1[N], sz[N], sum, rt;
int vis[N];
void getrt(int x, int f){
	sz[x] = 1, s1[x] = 0;
	reg(i,x) if (!vis[v] && v != f) getrt(v, x), sz[x] += sz[v], s1[x] = max(s1[x], sz[v]);
	s1[x] = max(s1[x], sum - sz[x]);
	if (s1[x] < s1[rt]) rt = x;
}
LL dis[N];
int cnt, par[N];
struct child{
	int x;
	LL d;
}ch[N];
int cl;
bool cmp1(const child &a, const child &b){
	return a.d > b.d;
}
void dfs(int x, int f){
	if (f) ch[++cl] = (child){x, dis[x] - l[x]};
	reg(i,x) if (v != f && !vis[v]) dfs(v, x);
}
const LL inf = 1LL << 61;
typedef pair<LL, LL> node;
node q1[N];
#define mp(a,b) make_pair(a,b)
double calc(const node &a, const node &b){ //a-->b
	return (double)(b.second - a.second) / (b.first - a.first);
}
bool cmp(const node &a, const node &b, const node &c){
	return calc(b, c) < calc(a, b);
}

LL find(int a, int b, LL d, LL p, LL q){
	//LL ans = -1;
	//rep(i,a,b - 1) upd(ans, q1[i].second - q1[i].first * p + d * p + q);
	//rep(i,a + 1,b - 1) cout <<calc(q1[i - 1], q1[i])<<' '<<(ans == q1[i].second - q1[i].first * p + d * p + q)<<' '<<p<<endl;
	//cout <<endl;
	//return ans;

	if (a + 1 == b) return q1[a].second - q1[a].first * p + d * p + q;
	int l = a + 1, r = b; //[l,r)
	while (l + 1 < r){
		int mid = (l + r) >> 1;
		if (calc(q1[mid - 1], q1[mid]) >= p) l = mid; else r = mid;
	}
	if (calc(q1[l - 1], q1[l]) >= p) return q1[l].second - q1[l].first * p + d * p + q;
	else return q1[a].second - q1[a].first * p + d * p + q;
}

void calc(int x){
	cl = 0, dfs(x, 0);
	sort(ch + 1, ch + cl + 1, cmp1);
	int j = 1, l = 0, r = 0;
	rep(i,1,cnt){
		int x = par[i];
		//add (dis[x], f[x]) dis[x]单调递减
		while (l <= r - 2 && !cmp(q1[r - 2], q1[r - 1], mp(dis[x], f[x]))) r--;
		q1[r++] = mp(dis[x], f[x]);

		LL t; 
		if (i == cnt) t = -inf; else t = dis[par[i + 1]];
		while (j <= cl && ch[j].d > t){
			if (l < r && ch[j].d <= dis[par[i]]){
				int t = ch[j].x;
				upd(f[t], find(l, r, dis[t], p[t], q[t]));
			}
			j++;
		}
	}
}
int vis_clock = 0;
void work(int x){
	vis[x] = ++vis_clock;
	if (fa[x]){
		if (!vis[fa[x]]) {
			rt = 0, sum = sz[fa[x]], getrt(fa[x], x);
			work(rt);
		}
		par[ cnt = 1 ] = x;
		for(int w = fa[x]; w && vis[w] > vis[x]; w = fa[w]) {
			par[ ++cnt ] = w;
			if (dis[w] >= dis[x] - l[x])
				upd(f[x], f[w] - dis[w] * p[x] + dis[x] * p[x] + q[x]);
		}
	} else par[ cnt = 1 ] = x;
	calc(x);
	reg(i,x) if (!vis[v] && v != fa[x]){
		rt = 0, sum = sz[v], getrt(v, x);
		work(rt);
	}
}
int main(){
	int n, t; scanf("%d%d",&n,&t);
	dis[1] = 0;
	rep(i,2,n) scanf("%d%lld%d%lld%lld",&fa[i],&s[i],&p[i],&q[i],&l[i]), dis[i] = dis[fa[i]] + s[i], ins(fa[i], i), ins(i, fa[i]);
	rep(i,1,n) f[i] = -1;
	f[1] = 0;
	s1[rt = 0] = sum = n, getrt(1, 0);
	work(rt);
	rep(i,2,n) printf("%lld\n",f[i]);
	return 0;
}