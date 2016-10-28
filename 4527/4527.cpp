#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a, _b = b; i <= _b; i++)
#define dep(i,a,b) for(int i = a, _b = b; i >= _b; i--)
using namespace std;
const int N = 200010;
struct sta{ 
	int l, r; 
	sta(int a = 0, int b = 0) { l = a, r = b; }
}ans;
inline bool operator > (const sta &a, const sta &b) { return a.r - a.l > b.r - b.l || (a.r - a.l == b.r - b.l && a.l < b.l)}
int a[N], n, k, d;
#define cal(x) (((x % d) + d) % d)
int mn[N], mx[N], pre[N], nxt[N], C[N], mt[N];
void solve(int l, int r){
	if (l == r) { if (sta(l, l) > ans) ans = sta(l, l); }
	else{
		int mid = (l + r) >> 1;
		if (cal(a[mid]) == cal(a[mid + 1])){
			int k = cal(a[mid]), l1 = l, r1 = r;
			dep(i,mid,l) if (cal(a[i]) != k || nxt[i] <= mid) { l1 = i + 1; break; }
			rep(i,mid + 1,r) if (cal(a[i]) != k || pre[i] > mid) { r1 = i - 1; break; }
			
			C[mid] = nxt[mid], mn[mid] = mx[mid] = a[mid]; 
			dep(i,mid - 1,l1) mn[i] = min(mn[i + 1], a[i]), mx[i] = max(mx[i + 1], a[i]), C[i] = min(C[i + 1], nxt[i]);
			
			C[mid + 1] = pre[mid + 1], mn[mid + 1] = mx[mid + 1] = a[mid + 1]; 
			rep(i,mid + 1,r1) mn[i] = min(mn[i - 1], a[i]), mx[i] = max(mx[i - 1], a[i]), C[i] = max(C[i - 1], pre[i]);

			int mxr = r1, mnr = r1, mtr = r1;
			dep(i,mid,l){
				while (mx[mxr] > mx[i] && mxr > mid) mxr--; if (mxr == mid) break;
				mnr = min(mnr, mxr);
				while (mn[mnr] < mn[i] && mnr > mid) mnr--;
				if (mnr > mid && (mx[i] - mn[i]) / d <= mnr - i + k) * d && sta(i, mnr) > ans) ans = sta(i, mnr);
				int tmp = mx / d + l - k;
				while (mx[i] / d + l - k)
			}
		}
		solve(l, mid); solve(mid + 1, r);
	}
}
int b[N], c[N], vis[N];
int find(int x) { int l = 1, r = n + 1; while (l + 1 < r) { int mid = (l + r) >> 1; if (b[mid] <= x) l = mid; else r = mid;} return l;}
int main(){
	scanf("%d%d%d",&n,&k,&d); 
	rep(i,1,n) scanf("%d",&a[i]), b[i] = c[i] = a[i]; sort(b + 1, b + n + 1);
	rep(i,1,n) c[i] = find(a[i]);
	rep(i,1,n) pre[i] = vis[c[i]], vis[c[i]] = i;
	dep(i,n,1) nxt[i] = vis[c[i]], vis[c[i]] = i;
	solve(1, n);
	return 0;
}