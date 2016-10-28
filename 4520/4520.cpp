#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#define rep(i,a,b) for(int i = a, _b = b; i <= _b; i++)
using namespace std;
const int N = 100100;
typedef long long LL;

struct point { 
	int d[2]; 
	point (int x = 0, int y = 0) { d[0] = x, d[1] = y; }
};

struct node { node *ch[2]; int d[2], mx[2], mn[2]; }T[N];
LL dis(const point &a, const point &b)
{ LL ans = 0; rep(i,0,1) ans += 1LL * (a.d[i] - b.d[i]) * (a.d[i] - b.d[i]); return ans; }

int D;
inline bool operator < (const node &a, const node &b) { return a.d[D] < b.d[D] || (a.d[D] == b.d[D] && a.d[D^1] < b.d[D^1]); }
node* build(int l, int r, int d){
	D = d; int mid = (l + r) >> 1; nth_element(T + l, T + mid, T + r + 1); swap(T[l], T[mid]);

	node *x = &T[l];
	rep(i,0,1) x->mx[i] = x->mn[i] = x->d[i];
	
	if (l + 1 <= mid) x->ch[0] = build(l + 1, mid, d ^ 1);
	if (mid + 1 <= r) x->ch[1] = build(mid + 1, r, d ^ 1);
	rep(j,0,1) if (x->ch[j]){
		rep(i,0,1) {
			x->mn[i] = min(x->mn[i], x->ch[j]->mn[i]);
			x->mx[i] = max(x->mx[i], x->ch[j]->mx[i]);
		}
	}

	return x;
}

LL dis(node *a, node &b){ return dis(point(a->d[0], a->d[1]), point(b.d[0], b.d[1])); }

LL calc(node *a, node &b){
	if (!a) return 0; LL ans = 0;
	point w = point(b.d[0], b.d[1]), t;
	t = point(a->mx[0], a->mn[1]);  ans = max(ans, dis(w, t));
	t = point(a->mn[0], a->mx[1]);  ans = max(ans, dis(w, t));
	t = point(a->mx[0], a->mx[1]);  ans = max(ans, dis(w, t));
	t = point(a->mn[0], a->mn[1]);  ans = max(ans, dis(w, t));
	return ans;
}

priority_queue<LL> q; 
void kmxdis(node *x, node &a){
	LL xd = dis(x, a);
	if (xd > -q.top()) { q.push(-xd); q.pop(); }

	LL v[2]; bool t[2] = {0, 1};
	rep(i,0,1) v[i] = calc(x->ch[i], a);

	if (v[0] < v[1]) swap(t[0], t[1]);
	rep(i,0,1) if (v[t[i]] > -q.top()) kmxdis(x->ch[t[i]], a);
}

int main(){
	int n, k; scanf("%d%d",&n,&k); k <<= 1;
	rep(i,1,n) scanf("%d%d",&T[i].d[0],&T[i].d[1]);
	rep(i,1,k) q.push(0);
	build(1, n, 0); node *rt = &T[1];
	rep(i,1,n) kmxdis(rt, T[i]);
	printf("%lld\n",-q.top());
	return 0;
}