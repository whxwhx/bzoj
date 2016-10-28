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
#define mp(a,b) make_pair1((a),(b))
#define pb(a) push_back(a)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
#define id(a,b) ((a - 1) * m + b)
int n, m; 
const int N = 100010, inf = 1000000000;
int R[N], C[N], D[N];

#define r1(a, b) R[id(a, b)]
#define c(a, b) C[id(a, b)]
#define d(a, b) D[id(a, b)]

struct qry{ int x1, y1, x2, y2, id; }q[N], tmp[N];

inline void upd(int &a, int b){ if (a > b) a = b; }

struct node{ int d, x, y; };
inline bool operator < (const node &a, const node &b){ return a.d < b.d; }
inline bool operator > (const node &a, const node &b){ return a.d > b.d; }
priority_queue<node> que;

int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};

void dij(int a, int b, int l, int r, int sx, int sy, int d){
	rep(i,a,b) rep(j,l,r) if (d(i,j) < inf) d(i,j) += d; 
	d(sx, sy) = 0; que.push((node){0, sx, sy});
	while (!que.empty()){
		node x = que.top(); que.pop();
		if (-x.d != d(x.x, x.y)) continue;
		rep(i,0,3){
			int tx = x.x + dx[i], ty = x.y + dy[i];
			if (a <= tx && tx <= b && l <= ty && ty <= r){
				int cost = (i == 0 ? c(tx, ty): (i == 1 ? c(x.x, ty): (i == 2 ? r1(tx, ty) : r1(tx, x.y))));
				if (d(tx, ty) > -x.d + cost) 
					d(tx, ty) = -x.d + cost, que.push((node){x.d - cost, tx, ty});
			}
		}
	}
}

int s[N], ans[N];
void solve(int a, int b, int l, int r, int ql, int qr){
	if (ql > qr || a > b || l > r) return;
	if (l == r && a == b){
		rep(i,ql,qr) ans[q[i].id] = 0;
	}else if (b - a > r - l){
		int mid = (a + b) >> 1;
		//dij
		rep(i,a,b) rep(j,l,r) d(i,j) = inf;
		rep(j,l,r){
			dij(a, b, l, r, mid, j, j == l ? 0 : d(mid, j));
			rep(i,ql,qr) upd(ans[q[i].id], d(q[i].x1, q[i].y1) + d(q[i].x2, q[i].y2));
		}
		//divide 
		int t1 = ql, t2 = qr;
		rep(i,ql,qr) if (q[i].x1 < mid && q[i].x2 < mid) tmp[t1++] = q[i];
		rep(i,ql,qr) if (q[i].x1 > mid && q[i].x2 > mid) tmp[t2--] = q[i];
		rep(i,ql,qr) q[i] = tmp[i];
		//solve
		solve(a, mid - 1, l, r, ql, t1 - 1);
		solve(mid + 1, b, l, r, t2 + 1, qr);
	}else{
		int mid = (l + r) >> 1;
		//dij
		rep(i,a,b) rep(j,l,r) d(i,j) = inf;
		rep(j,a,b){
			dij(a, b, l, r, j, mid, j == a ? 0 : d(j, mid));
			rep(i,ql,qr) upd(ans[q[i].id], d(q[i].x1, q[i].y1) + d(q[i].x2, q[i].y2));
		}
		//divide
		int t1 = ql, t2 = qr;
		rep(i,ql,qr) if (q[i].y1 < mid && q[i].y2 < mid) tmp[t1++] = q[i];
		rep(i,ql,qr) if (q[i].y1 > mid && q[i].y2 > mid) tmp[t2--] = q[i];
		rep(i,ql,qr) q[i] = tmp[i];
		//solve
		solve(a, b, l, mid - 1, ql, t1 - 1);
		solve(a, b, mid + 1, r, t2 + 1, qr);
	}
}

int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,n) rep(j,1,m - 1) scanf("%d",&r1(i,j));
	rep(i,1,n - 1) rep(j,1,m) scanf("%d",&c(i,j));
	int Q; scanf("%d",&Q);
	rep(i,1,Q) scanf("%d%d%d%d",&q[i].x1,&q[i].y1,&q[i].x2,&q[i].y2), q[i].id = i, ans[i] = inf;
	solve(1, n, 1, m, 1, Q);
	rep(i,1,Q) printf("%d\n",ans[i]);
	return 0;
}