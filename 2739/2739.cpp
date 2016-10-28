#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
typedef long long LL;
const int N = 500010;
struct node{ int x, y; }a[N];
int f[N], n;
LL dis(node &a, node &b) { return 1LL * (a.x - b.x) * (a.x - b.x) + 1LL * (a.y - b.y) * (a.y - b.y); }
void solve(int l, int r, int l1, int r1){
	if (l > r) return;
	int mid = (l + r) >> 1; int t1 = max(l1, mid + 1), t2 = min(r1, mid + n);
	int mx = 0; rep(i,t1,t2) if (!mx || dis(a[i], a[mid]) > dis(a[mx], a[mid])) mx = i;
	f[mid] = mx <= n ? mx : mx - n; solve(l, mid - 1, l1, mx); solve(mid + 1, r, mx, r1);
}
void work(){
	scanf("%d",&n); rep(i,1,n) scanf("%d%d",&a[i].x,&a[i].y), a[n + i] = a[i], f[i] = 0;
	solve(1, n, 1, n << 1); rep(i,1,n) printf("%d\n",f[i]); printf("\n");
}
int main(){ int T; scanf("%d",&T); while (T--) work(); return 0; }