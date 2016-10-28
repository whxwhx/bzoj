#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
typedef long long LL;
const int N = 1010;
struct point{ int x, y, id; }a[N], q, r;
point operator + (const point &a, const point &b) { return (point){a.x + b.x, a.y + b.y}; }
point operator - (const point &a, const point &b) { return (point){a.x - b.x, a.y - b.y}; }
LL operator * (const point &a, const point &b) { return 1LL * a.x * b.x + 1LL * a.y * b.y; }
LL cross(const point &a, const point &b) { return 1LL * a.x * b.y - 1LL * a.y * b.x; }
bool cmp(const point &a, const point &b) { return a * r > b * r; }
bool operator < (const point &a, const point &b) { 
	if (a.y >= 0 && b.y < 0) return true;
	if (a.y < 0 && b.y >= 0) return false;
	if (a.y == 0 && b.y == 0) return a.x > 0 && b.x < 0;
	return cross(a, b) > 0;
}
struct sp{ point r; int a, b; LL w; }b[N * N]; int l = 0;
bool operator < (const sp &a, const sp &b) { return a.r < b.r || (!(a.r < b.r) && !(b.r < a.r) && a.w < b.w); }
int n, id[N]; point s[N]; LL ans[N];
#define ab(x) ((x >= 0) ? x : -(x))
void work(){
	r = (point){100000000, 1}; sort(a + 1, a + n + 1, cmp); 
	rep(i,1,n) rep(j,1,n) if (a[i] < a[j] || a[j] < a[i]) {
		point t = a[i] - a[j]; swap(t.x, t.y); t.x = -t.x;
		b[++l] = (sp){t, i, j, a[i] * t};
	} 
	sort(b + 1, b + l + 1); 
	s[0] = (point){0, 0}; 
	rep(i,1,n) id[i] = i, s[i] = s[i - 1] + a[i], ans[i] = max(ans[i], s[i] * s[i]), a[i].id = i;
	int L = n, R = 0;
	rep(i,1,l) if (i == n || b[i].r < b[i + 1].r){
		int t1 = b[i].a, t2 = b[i].b; 
		L = min(L, min(id[t1], id[t2])), R = max(R, max(id[t1], id[t2]));
		r = b[i].r; int f = 100000000 / (max(ab(r.x), ab(r.y)) + 1); 
		r.x *= f, r.y *= f, r.y = (r.x < 0) ? (r.y - 1) : (r.y + 1); 
		sort(a + L, a + R + 1, cmp);
		cout <<L<<' '<<R<<endl;
		rep(j,L,R) s[j] = s[j - 1] + a[j], ans[j] = max(ans[j], s[j] * s[j]), id[a[j].id] = j;
		L = n, R = 0;
	} else {
		int t1 = b[i].a, t2 = b[i].b; 
		L = min(L, min(id[t1], id[t2])), R = max(R, max(id[t1], id[t2]));
	}

	LL mx = 0; rep(i,1,n) mx = max(mx, ans[i]);
	printf("%lld\n",mx); rep(i,1,n) printf("%lld%c",ans[i],(i==n ? '\n' : ' '));
}	
int main(){
	scanf("%d",&n); scanf("%d%d",&q.x,&q.y); LL ans = 0;
	rep(i,1,n) scanf("%d%d",&a[i].x,&a[i].y), ans += max(a[i] * q, 0LL);
	printf("%lld\n",ans); work(); return 0;
}