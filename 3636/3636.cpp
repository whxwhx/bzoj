#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
const int N = 100010;
int A[N], ans[N], L;
struct qry{
	int a, b, t;
}q[N], ch[N][3];
int f[N], g[N];
#define gl(x) (((x) > mid - lf) ? 0 : g[(x)])
#define gr(x) (((x) < mid + rt) ? 0 : g[(x)])
void solve(int l, int r, int a, int b){
	if (a > b || l > r) return;
	if (l == r){
		rep(i,a,b) if (q[i].a <= q[i].b)
			ans[q[i].t] = max(ans[q[i].t], A[l]);
	}else {
		int cl[3] = {0,0,0};
		int mid = (l + r) >> 1;
		rep(i,a,b){
			int d;
			if (q[i].b <= mid) d = 0;
			else if (q[i].a <= mid && q[i].b > mid) d = 1;
			else d = 2;
			ch[++cl[d]][d] = q[i];
		}
		int t = a;
		rep(d,0,2) rep(i,1,cl[d]) q[t++] = ch[i][d];
		int t1 = a + cl[0], t2 = a + cl[0] + cl[1] - 1;
		if (t1 <= t2){
			rep(lf,0,L - 1){
				int rt = L - lf;
				dep(i,mid - lf,l)
					f[i] = gl(i + L) + A[i],
					g[i] = max(gl(i + 1), f[i]);
				rep(i,mid + rt,r)
					f[i] = gr(i - L) + A[i],
					g[i] = max(gr(i - 1), f[i]);
				rep(i,t1,t2){
					if (q[i].a <= q[i].b)
						ans[q[i].t] = max(ans[q[i].t], gl(q[i].a) + gr(q[i].b));
				}
			}
		}
		solve(l, mid, a, t1 - 1), solve(mid + 1, r, t2 + 1, b);
	}
}
int B[N];
int main(){
	int n; scanf("%d%d",&n,&L);
	rep(i,1,n) scanf("%d",&A[i]), B[i] = A[i];
	int Q; scanf("%d",&Q);
	rep(i,1,Q) {
		scanf("%d%d",&q[i].a,&q[i].b), q[i].t = i;
		q[i].a += L - 1;
	}
	rep(i,2,L) A[i] += A[i - 1];
	rep(i,L + 1,n) A[i] += A[i - 1] - B[i - L];
	solve(L, n, 1, Q);
	rep(i,1,Q) printf("%d\r\n",ans[i]);
	return 0;
}