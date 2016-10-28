#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;

const int N = 21000;

typedef pair<int, int> num;
num x[N];
#define mp(a,b) make_pair(a,b)
inline num operator + (const num &a, const num &b) { return mp(a.first + b.first, a.second + b.second); }

int n, k, a[N], b[N], c[N];

#define lc (x << 1)
#define mid ((l + r) >> 1)
#define rc (lc | 1)
#define lcq lc, l, mid
#define rcq rc, mid+1, r

const int inf = 2147483646;

num f[N];
namespace seg{
	num mx[N << 2], c; int a, b;
	void modi(int x, int l, int r) {
		if (l == r) mx[x] = c;
		else ( (a <= mid) ? modi(lcq) : modi(rcq) ), mx[x] = max(mx[lc], mx[rc]);		
	}
	num qry(int x, int l, int r) {
		if (a <= l && r <= b) return mx[x];
		else return max( ((a <= mid) ? qry(lcq) : mp(-inf, 0)), ((b > mid) ? qry(rcq) : mp(-inf, 0)) );
	}
	void build(int x, int l, int r) { mx[x] = mp(-inf, 0); if (l < r) build(lcq), build(rcq); }
}

const int M = 41000000;
int l[M], r[M], d[M], tag[M], tl = 0; num w[M];

int newnode(int x) { tl++, l[tl] = l[x], r[tl] = r[x], w[tl] = w[x], d[tl] = d[x], tag[tl] = tag[x]; return tl; }
void push(int x) {
	if (tag[x]) {
		if (l[x]) l[x] = newnode(l[x]), tag[l[x]] += tag[x];
		if (r[x]) r[x] = newnode(r[x]), tag[r[x]] += tag[x];
		w[x].first += tag[x], tag[x] = 0;
	}
}
int merge(int a, int b) {
	if (!a || !b) return a | b;
	push(a), push(b); if (w[a] < w[b]) swap(a, b);
	a = newnode(a); r[a] = merge(r[a], b);
	if (d[r[a]] > d[l[a]]) swap(l[a], r[a]); 
	d[a] = d[r[a]] + 1; return a;
}

namespace seg2{
	int s[N << 2], a, b, c;
	void add(int x, int l, int r) {
		if (l == r) s[x] = c;
		else (a <= mid ? add(lcq) : add(rcq)), s[x] = merge(s[lc], s[rc]);
	}
	int qry(int x, int l, int r) {	
		if (a <= l && r <= b) return s[x];
		else return merge((a <= mid ? qry(lcq) : 0), (b > mid ? qry(rcq) : 0));
	}
}

int g[N];

priority_queue<num> q;

int main() {
	scanf("%d%d",&n,&k);
	rep(i,1,n) scanf("%d",&x[i].first), x[i].second = n - i;
	sort(x + 1, x + n + 1); rep(i,1,n) c[ n - x[i].second ] = i;
	rep(i,1,n) scanf("%d",&a[i]), a[i] = -a[i];
	rep(i,1,n) scanf("%d",&b[i]), b[i] = -b[i];
	
	seg::build(1, 1, n);
	f[n] = mp(0, 0); seg::a = c[n], seg::c = mp(0, n); seg::modi(1, 1, n);
	dep(i,n - 1,1) {
		f[i] = mp(-inf, 0);
		seg::a = 1, seg::b = c[i] - 1; 
		if (seg::a <= seg::b) {
			num t = seg::qry(1, 1, n);
			if (t.second) f[i] = max(f[i], t + mp(a[i], 0));
		}
		seg::a = c[i] + 1, seg::b = n; 
		if (seg::a <= seg::b) {
			num t = seg::qry(1, 1, n);
			if (t.second) f[i] = max(f[i], t + mp(b[i], 0));
		}
		
		seg::a = c[i], seg::c = mp(f[i].first, i); seg::modi(1, 1, n);
	}
	

	dep(i,n,1) {
		seg2::a = 1, seg2::b = c[i] - 1; 
		if (seg2::a <= seg2::b) {
			int t = seg2::qry(1, 1, n);
			if (t){
				if (w[t].second == f[i].second) push(t), t = merge(l[t], r[t]); //merge左右孩子之前要先把root到标记推下去
				tag[t] += a[i] - f[i].first;
				g[i] = merge(g[i], t);
			}
		}
		seg2::a = c[i] + 1, seg2::b = n;
		if (seg2::a <= seg2::b) {
			int t = seg2::qry(1, 1, n);
			if (t){
				if (w[t].second == f[i].second) push(t), t = merge(l[t], r[t]);
				tag[t] += b[i] - f[i].first;	
				g[i] = merge(g[i], t);
			}
		}
		
		seg2::a = c[i], w[seg2::c = ++tl] = mp(f[i].first, i); seg2::add(1, 1, n);
	}
	
	dep(i,n - 1,1) g[i] = merge(g[i], g[f[i].second]);
	
	if (k == 1) printf("%d\n",f[1].first);
	else {
		k--; push(g[1]), q.push(mp(f[1].first + w[g[1]].first, g[1]));
		int ans = f[1].first;
		rep(i,1,k) {
			num x = q.top(); q.pop(); ans = x.first;			
			//add1
				int xw = x.first, xg = x.second, to = w[xg].second;
				if (g[to]) push(g[to]), q.push(mp(xw + w[g[to]].first, g[to]));
			//add2
				xw = x.first, xg = x.second; push(xg); int xg1 = merge(l[xg], r[xg]);
				if (xg1) push(xg1), q.push(mp(xw - w[xg].first + w[xg1].first, xg1));
		}
		printf("%d\n",-ans);
	}	
	return 0;
}	
