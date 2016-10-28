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
#define min(a,b) ((a) < (b) ? (a) : (b))
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
int n, m;
const int N = 300100;
int a[N];
LL tag[N * 4][3];
LL mn[N * 4], se[N * 4];
int mnc[N * 4];
const LL inf = 400000000000000LL;
#define lc (x << 1)
#define rc (lc + 1)
#define mid ((l + r) >> 1)
#define lcq lc, l, mid
#define rcq rc, mid + 1, r
void mark(int x, int t, LL d){
	if (t == 0){
		tag[x][1] = tag[x][2] = 0;
		tag[x][0] = d;
	}else tag[x][t] += d;
}
LL getmin(int x){
	LL ans = mn[x];
	if (tag[x][0] != -1) ans = tag[x][0];
	if (tag[x][1]) ans += tag[x][1];
	if (tag[x][2]) ans += tag[x][2];
	return ans;
}
void push(int x, int l, int r){
	if (tag[x][0] != -1){
		mn[x] = tag[x][0], mnc[x] = r - l + 1;
		se[x] = inf;
		if (l < r) mark(lc, 0, tag[x][0]), mark(rc, 0, tag[x][0]);
		tag[x][0] = -1;
	}
	if (tag[x][1]){
		LL d = tag[x][1];
		mn[x] += d, se[x] = (se[x] == inf) ? inf : (se[x] + d);
		if (l < r) mark(lc, 1, d), mark(rc, 1, d);
		tag[x][1] = 0;	
	}
	if (tag[x][2]){
		LL d = tag[x][2];
		if (l < r) {
			if (getmin(lc) == mn[x]) mark(lc, 2, d);
			if (getmin(rc) == mn[x]) mark(rc, 2, d);
		}
		mn[x] += d;
		tag[x][2] = 0;
	}
}
void upd(int x){
	if (mn[lc] == mn[rc]){
		mn[x] = mn[lc], mnc[x] = mnc[lc] + mnc[rc];
		se[x] = min(se[lc], se[rc]);
	}else {
		int a = lc, b = rc;
		if (mn[a] > mn[b]) swap(a, b);
		mn[x] = mn[a], mnc[x] = mnc[a];
		se[x] = min(se[a], mn[b]);
	}
}
void md(int x, int l, int r, int a, int b, LL c, int tp){
	push(x, l, r);
	if (a <= l && r <= b){
		if (tp == 0)
			mark(x, 0, c);
		else if (mn[x] < -c){
			if (-c < se[x])
				mark(x, 2,(-c) - mn[x]), mark(x, 1, c);
			else 
				md(lcq, a, b, c, tp), md(rcq, a, b, c, tp), upd(x);
		} else mark(x, 1, c);
		push(x, l, r);
	} else {
		if (a <= mid) md(lcq, a, b, c, tp); else push(lcq);
		if (b >  mid) md(rcq, a, b, c, tp); else push(rcq);
		upd(x);
	}	
}
int qy(int x, int l, int r, int a, int b){
	push(x, l, r);
	if (a <= l && r <= b) return mn[x] == 0 ? mnc[x] : 0;
	else {
		LL ans = 0;
		if (a <= mid) ans += qy(lcq, a, b);
		if (b >  mid) ans += qy(rcq, a, b);
		return ans;
	}
}
int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,n) scanf("%d",&a[i]), md(1, 1, n, i, i, a[i], 0);
	rep(i,1,m){
		int op, a, b, c; scanf("%d",&op);
		if (op == 1){
			scanf("%d%d%d",&a,&b,&c);
			md(1, 1, n, a, b, c, 0);
		}else if (op == 2){
			scanf("%d%d%d",&a,&b,&c);
			md(1, 1, n, a, b, c, 1);
		}else if (op == 3){
			scanf("%d%d",&a,&b);
			printf("%d\n",qy(1, 1, n, a, b));
		}
	}
	return 0;
}