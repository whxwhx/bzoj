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
const int N = 300100;

int a[N], f[N];
LL h[N], v[N];
typedef pair<LL, LL> node;
node tag[N];
LL val[N];
int lc[N], rc[N], rt[N], d[N];
node operator + (const node &a, const node &b){
	return mp(a.first * b.first, a.second * b.first + b.second);
}
void push(int x){
	if (tag[x] != mp(1LL, 0LL)){
		tag[lc[x]] = tag[lc[x]] + tag[x];
		tag[rc[x]] = tag[rc[x]] + tag[x];
		val[x] = val[x] * tag[x].first + tag[x].second;
		tag[x] = mp(1LL, 0LL);
	}
}

int merge(int a, int b){
	if (!a || !b) return a | b;
	else {
		push(a), push(b);
		if (val[a] > val[b]) swap(a,b);
		rc[a] = merge(rc[a], b);
		if (d[rc[a]] > d[lc[a]]) swap(lc[a], rc[a]);
		d[a] = d[rc[a]] + 1;
		return a;
	}
}

int dep[N], ans1[N], ans2[N];

int main(){
	int n, m; scanf("%d%d",&n,&m);
	rep(i,1,n) scanf("%lld",&h[i]);
	rep(i,2,n) scanf("%d%d%lld",&f[i],&a[i],&v[i]);

	dep[1] = 1;
	rep(i,2,n) dep[i] = dep[f[i]] + 1;
	rep(i,1,m) {
		int s, c; scanf("%d%d",&s,&c);
		tag[i] = mp(1LL, s);
		lc[i] = rc[i] = val[i] = 0;
		rt[c] = merge(rt[c], i);
		ans2[i] = dep[c];
	}

	dep(i,n,1){
		while (rt[i] && (push(rt[i]), val[rt[i]] < h[i])) {
			ans1[i]++;
			ans2[rt[i]] -= dep[i];
			rt[i] = merge(lc[rt[i]], rc[rt[i]]);
		} 
		if (f[i] && rt[i]){
			if (a[i]) 
				tag[rt[i]] = tag[rt[i]] + mp(v[i], 0LL);
			else 
				tag[rt[i]] = tag[rt[i]] + mp(1LL, v[i]);
			rt[f[i]] = merge(rt[i], rt[f[i]]);
		}
	}

	rep(i,1,n) printf("%d\n",ans1[i]);
	rep(i,1,m) printf("%d\n",ans2[i]);
	return 0;
}