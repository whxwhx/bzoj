#include <iostream>
#include <cstdio>
#include <algorithm>
#define max(a,b) ((a) < (b) ? (b) : (a))
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
#define get(L) ((l < r && y[l] <= L) ? s[l] : -1)
#define upd() s[x] = (head[b[i].b] == x) ? f[x] : max(s[x - 1], f[x]);
#define binary(a,L) for(l=head[a], r=head[a + 1]; l + 1 < r; mid = (l + r) >> 1, (y[mid] <= L ? (l = mid) : (r = mid)))
using namespace std;
const int M = 300000 + 10;
struct bus{
	int a, b, x, y, num;
}b[M];
bool cmp1(const bus &a, const bus &b){
	return a.b < b.b || (a.b == b.b && a.y < b.y) || (a.a == b.b && a.y == b.y && a.num < b.num);
}
bool cmp2(const bus &a, const bus &b){
	return a.y < b.y ||  (a.y == b.y && a.num < b.num); 
}
int y[M], f[M], s[M], head[M];
int main(){
	int n, m; scanf("%d%d",&n,&m);
	rep(i,1,m) scanf("%d%d%d%d",&b[i].a, &b[i].b, &b[i].x, &b[i].y), b[i].num = i;
	 
	sort(b + 1, b + m + 1, cmp1);
	rep(i,1,m) b[i].num = i, y[i] = b[i].y;
	b[0].b = 0;
	rep(i,1,m) if (b[i].b != b[i - 1].b) head[b[i].b] = i;
	head[n + 1] = m + 1;
	dep(i,n,1) if (head[i] == 0) head[i] = head[i + 1];

	sort(b + 1, b + m + 1, cmp2);
	rep(i,1,m) f[i] = s[i] = -1;
	rep(i,1,m){
		int x = b[i].num;
	 	if (b[i].a == 1) {
	 		f[x] = b[i].x;
	 		if (head[b[i].b] == x) s[x] = f[x]; else s[x] = max(s[x - 1], f[x]);
	 	}else{
	 		int l,r,mid;//[l,r)
	 		binary(b[i].a, b[i].x);
	 		f[x] = get(b[i].x);
	 		upd();
	 	}
	}
	int Q; scanf("%d",&Q);
	rep(i,1,Q) {
	 	int L; scanf("%d",&L);
	 	int l, r, mid;
	 	binary(n, L);
	 	printf("%d\n",get(L));
	}
	return 0;
}