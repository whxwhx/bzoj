#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
typedef long long LL;
const int N = 100010;
const LL INF = 1LL << 62;
int a[N]; LL ans = 1LL << 62, b[N];
int n, p, k, m; 
bool vis[N];

struct point{ int x; LL y; int id; }s[N], st[N];
inline bool operator < (const point &a, const point &b) { return a.x < b.x || (a.x == b.x && a.y < b.y); }
inline point operator - (const point &a, const point &b) { return (point){a.x - b.x, a.y - b.y, 0}; }
inline LL operator * (const point &a, const point &b) { return a.x * b.y - a.y * b.x; }
int h[N], t[N], ind[N];
LL d[N], an[N];

inline LL calc(int l, int x) { return st[x].y - 1LL * st[x].x * ind[l] + d[l]; }

void build(int l, int r){
	h[l] = l, t[l] = l - 1; ind[l] = d[l] = 0;
	rep(i,l,r) if ( !vis[ s[i].id ] ){
		while (t[l] - h[l] + 1 >= 2 && ( s[i] - st[t[l]] ) * ( st[t[l]] - st[t[l] - 1] ) >= 0) t[l]--;
		st[++t[l]] = s[i];
	}
	an[l] = calc(l, h[l]);
	while ( t[l] - h[l] + 1 >= 2 && calc(l, h[l] + 1) <= an[l] ) h[l]++, an[l] = calc(l, h[l]);
}

void init(){
	rep(i,1,n) s[i].x = -a[i], s[i].y = b[i];
	sort(s + 1, s + n + 1); m = (int)(sqrt(n)) + 2;
	rep(i,1,n) s[i].id = i;
	memset(vis, false, sizeof(vis));
	for(int l = 1; l <= n; l += m){
		int r = l + m - 1; if (r > n) r = n;
		build(l, r);
	}
}


LL mn; int mnl;
void findmn(){
	mn = INF, mnl = 0;
	for(int l = 1; l <= n; l += m)
		if ( h[l] <= t[l] && an[l] < mn ) mn = an[l], mnl = l;
}

void work(){
	LL sum = 0;
	rep(T,1,p) {
		findmn(); sum += mn;
		int md = st[h[mnl]].id, delta = -s[md].x; vis[md] = true;

		for(int l = mnl - m; l >  0; l -= m) d[l] += delta, an[l] += delta;
		for(int l = mnl + m; l <= n; l += m) {
			ind[l]++; an[l] = calc(l, h[l]);
			while ( t[l] - h[l] + 1 >= 2 && calc(l, h[l] + 1) <= an[l] ) h[l]++, an[l] = calc(l, h[l]);
		}

		int l = mnl, r = min( l + m - 1, n );
		rep(i,l,r) if (!vis[ s[i].id ]) s[i].y = s[i].y - 1LL * s[i].x * ind[l] + d[l];

		rep(i,l,md) s[i].y += delta;
		rep(i,md+1,r) s[i].y -= s[i].x;

		build(l, r);
	}
	if (sum < ans) ans = sum;
}

int main(){
	scanf("%d%d%d",&n,&p,&k);
	rep(i,1,n) scanf("%d%lld",&a[i],&b[i]);

	init(); work();
	if (k == 1) {
		LL mx = 0;
		rep(i,1,n) if (vis[i]) mx = max(mx, b[i]);
		ans -= mx;

		mx = 1LL << 62; int mxa = 0;
		rep(i,1,n) if (!vis[i]) if (a[i] < mx) mx = a[i], mxa = i;
		if (mxa) { b[mxa] = 0; init(); work(); }
	}
	printf("%lld\n", ans);
	return 0;
}