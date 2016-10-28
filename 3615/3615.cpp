#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;

const int N = 50010, Q = 100010;
struct node *null;
struct node{
	node *ch[2];
	int mx, mn, s, id, d, s0;
	void upd(){
		mx = max(ch[0]->mx, ch[1]->mx);
		mn = min(ch[0]->mn, ch[1]->mn);
		s = ch[0]->s + ch[1]->s;
		s0 = ch[0]->s0 + ch[1]->s0;
		id = max(ch[0]->id, ch[1]->id);
	}
	void push(){
		if (d && this != null){
			ch[0]->d += d, ch[1]->d += d;
			mx += d, mn += d, s += s0 *d;
			d = 0;
		}
	}
}T[N * 3 + Q * 60], *null = NULL;
int l = 0;
node *nn(){
	l++;
	T[l].ch[0] = T[l].ch[1] = null;
	return &T[l];	
}

node *merge(node *a, node *b){
	a->push(), b->push();
	if (a == null) return b;
	if (b == null) return a;
	//本题特殊性（序列是单调递增子序列），所以不会有叶子合并
	//本题并没有可持久化等要求，所以可以直接用原来的a，节省空间
	a->ch[0] = merge(a->ch[0], b->ch[0]);
	a->ch[1] = merge(a->ch[1], b->ch[1]);
	a->upd();
	return a;
}

#define mid ((l + r) >> 1)

typedef pair<node*, node*> sta;
sta split(node *a, int l, int r, int k){
	a->push();
	if (a == null) return null;
	if (k >= r) return a;
	int d = k > mid;
	if (d == 0){
		sta t = split(a->ch[0], l, mid, k, f); a->ch[0] = t.second;
		node *b = nn(); b->ch[0] = t.first;
		a->upd(), b->upd();
		return mp(b, a);
	}else {
		sta = split(a->ch[0], mid + 1, r, k, f); a->ch[1] = t.first;
		node *b = nn(); b->ch[1] = t.second;
		a->upd(), b->upd();
		return mp(a, b);
	}
}


struct point{
	int x, y, v, id;
}a[N];
operator < (const point &a, const point &b){
	return a.x < b.x;
}

const int M = 260;

point k[N];
struct Tree{
	bool flag;
	node *rt[N + Q * 2];
	int c;
	point a[N];
	int l = 0;

	node *build(int l, int r, point a){
		node *o = nn();
		if (l == r) o->s0 = 1, o->s = a.v, o->id = a.y;
		else {
			if (a.x <= mid) o->ch[0] = build(l, mid, a); 
			else o->ch[1] = build(mid + 1, r, a);
			o->upd();
		}
	}
	void init(point x){
		a[++l] = x;
		rt[x.id] = build(1, n, x);
	}
	void pre(bool f){
		sort(a + 1, a + l + 1);
		flag = f;
	}
	void merge(int x, int y){
		rt[x] = merge(rt[x], rt[y]), rt[y] = NULL;
	}
	void split(int x, int d, int v){
		if (d == 1){
			
		}else {
			sta t = split(rt[x], 1, n, v);
			rt[++c] = t.first, rt[++c] = t.second;
			rt[x] = null;
		}
	}
	node* query(int x){
		return rt[x];
	}
	void add(int x, int d){
		rt[x]->d += d;
	}
}A[M];

int L = 0;
int f[N], g[N], fr[N];
bool vis[N];

int mx = 0;
int find(int x){
	int l = 0, r = mx + 1;
	while (l + 1 < r) if (x > g[mid]) l = mid; else r = mid;
	return l;
}

int fr[N], gfr[N];

int F[2][N], Fr[2][N];

void divide(){
	int cnt = 0;
	memset(vis, false, sizeof(vis));
	while (cnt < n){
		L++;

		mx = 0; 
		memset(g, 0, sizeof(g)); memset(f, 0, sizeof(f));
		memset(fr, 0, sizeof(fr)); memset(gfr, 0, sizeof(gfr));
		sort(a + 1, a + n + 1);

		rep(i,1,n) if (!vis[i]){
			f[i] = find(a[i].y) + 1; if (f[i] > mx) mx = f[i];
			fr[i] = gfr[f[i] - 1];

			g[f[i]] = a[i].y, gfr[f[i]] = i;
		}

		rep(i,1,n) F[0][i] = f[i], Fr[0][i] = fr[i];
		int Mx[2] = {mx, 0};

		mx = 0;
		memset(g, 0, sizeof(g)); memset(f, 0, sizeof(f));
		memset(fr, 0, sizeof(fr)); memset(gfr, 0, sizeof(gfr));
		dep(i,n,1) if (!vis[i]){
			f[i] = find(a[i].y) + 1; if (f[i] > mx) mx = f[i];
			fr[i] = gfr[f[i] - 1];

			g[f[i]] = a[i].y, gfr[f[i]] = i;
		}
		rep(i,1,n) F[1][i] = f[i], Fr[1][i] = fr[i];
		Mx[1] = mx;

		int d = 0;
		if (Mx[1] > Mx[0]) d = 1;

		cnt += Mx[d];
		int t = 0;
		rep(i,1,n) if (F[d][i] == Mx[d]){t = i; break;}
		while (t){
			A[L].init(a[t]); vis[t] = true;
			t = Fr[d][t];
		}
		A[L].pre(d);
	}
}

int b[N];

int fb(int x){
	int l = 0, r = n;
	while (l + 1 < r) if (b[mid] < x) l = mid; else r = mid;
	return r;
}

void init(){
	scanf("%d",&n);
	rep(i,1,n) scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].v), a[i].id = i;
	
	rep(i,1,n) b[i] = a[i].x;
	sort(b + 1, b + n + 1);
	rep(i,1,n) a[i].x = fb(a[i].y);

	rep(i,1,n) b[i] = a[i].y;
	sort(b + 1, b + n + 1);
	rep(i,1,n) a[i].y = fb(a[i].y);

	divide();
}

int main(){
	init();

}