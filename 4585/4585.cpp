#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef long long LL;
const int N = 300010;
int n, m, f[N], r[N]; 

int rt[N];
LL v[N * 2];
int lc[N * 2], rc[N * 2], d[N * 2], c[N];
LL b[N];

typedef long long LL;

int merge(int a, int b){
	if (!a || !b) return a | b; if (v[a] < v[b]) swap(a, b);
	rc[a] = merge(rc[a], b); if (d[rc[a]] > d[lc[a]]) swap(lc[a], rc[a]);
	d[a] = d[rc[a]] + 1; return a;
}

int a[N];

int main(){
	scanf("%d%d",&n,&m);
	rep(i,2,n + m) scanf("%d%d",&f[i],&r[i]);
	dep(i,n+m,n+1) {
		rt[i] = 0, v[i] = r[i], v[n + m + i] = r[i];
		rt[i] = merge(i, n + m + i);
		rt[ f[i] ] = merge(rt[ f[i] ], rt[i]), c[ f[i] ]++;
		b [ f[i] ] += r[i];
	}

	dep(i,n,2) {
		rep(j,1,c[i] - 1) rt[i] = merge(lc[rt[i]], rc[rt[i]]);
		LL L, R, w = r[i];
		R = v[ rt[i] ]; rt[i] = merge(lc[rt[i]], rc[rt[i]]);
		L = v[ rt[i] ]; rt[i] = merge(lc[rt[i]], rc[rt[i]]); 

		v[i] = L + w; rt[i] = merge(rt[i], i);
		v[n + m + i] = R + w; rt[i] = merge(rt[i], n + m + i);

		rt[f[i]] = merge(rt[f[i]], rt[i]); b[f[i]] += r[i] + b[i]; c[f[i]]++;
	}


	dep(i,c[1],1) rt[1] = merge(lc[ rt[1] ], rc[ rt[1] ]);


	LL ans = b[1];
	while (rt[1]) { ans -= v[ rt[1] ]; rt[1] = merge(lc[ rt[1] ], rc[ rt[1] ]); }
	printf("%lld\n",ans);

	return 0;
}