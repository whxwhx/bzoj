#include <iostream>
#include <cstdio>
#include <algorithm>
#define mp(a,b) make_pair(a,b)
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 200010, inf = 1000000000;
int a[N], b[N];
#define min(a,b) ((a) < (b) ? (a) : (b))
//lct
struct node{
	node *ch[2], *f;
	int mn, w;
	bool rev;
	int d(){return f->ch[1] == this;}
	bool c(){return f->ch[0] != this && f->ch[1] != this;}
	void push(){if (rev) rev = 0, swap(ch[0], ch[1]), ch[0]->rev ^= 1, ch[1]->rev ^= 1;}
	void upd(){mn = min(ch[0]->mn, ch[1]->mn), mn = min(mn, w);}
	void st(node *c, int d){ch[d] = c, c->f = this;}
}T[N * 2], *null = &T[0];

void LCT_init(){
	null->ch[0] = null->ch[1] = null->f = null;
	null->mn = null->w = inf;
	null->rev = 0;
}
void rot(node *o){
	node *f = o->f; int d = o->d();
	if (!f->c()) f->f->st(o, f->d()); else o->f = f->f;
	f->st(o->ch[d ^ 1], d), o->st(f, d ^ 1);
	f->upd();
}
void fix(node *o){
	if (!o->c()) fix(o->f);
	o->push();
}
void splay(node *o){
	fix(o);
	while (!o->c())
		if (o->f->c()) rot(o);
		else (o->d() == o->f->d()) ? (rot(o->f), rot(o)) : (rot(o), rot(o));
	o->upd();
}
void access(node *o){
	node *t = o;
	for(node *c = null; o; o = o->f){
		splay(o);
		o->st(c, 1);
		o->upd();
		c = o;
	}
	splay(t);
}
node *findrt(int a){
	node *o = &T[a];
	access(o);
	o->push();//!
	while (o->ch[0] != null) {
		o = o->ch[0];
		o->push();//!
	}
	splay(o);
	return o;
}
void mrt(node *o){
	access(o), o->rev ^= 1;
}
void link(int a, int b){
	node *x = &T[a], *y = &T[b];
	mrt(x), x->f = y, access(x);
}
void cut(int a, int b){
	node *x = &T[a], *y = &T[b];
	mrt(x), access(y), y->ch[0]->f = null, y->ch[0] = null, y->upd();
}
int findmin(int a, int b){
	node *x = &T[a], *y = &T[b];
	mrt(x), access(y); return y->mn;
}
//segment-tree
struct seg{
	seg *ch[2];
	int s;
}Seg[N * 50], *segnull = &Seg[N * 50], *rt[N];
int l = 0;
seg* nn(){
	return &Seg[++l];
}
void seg_init(){
	segnull->ch[0] = segnull->ch[1] = segnull;
	segnull->s = 0;
}
seg* add(seg *x, int l, int r, int a){
	seg *k; *k = *x; (k->s)++;
	if (l < r){
		int mid = (l + r) >> 1;
		if (a <= mid) k->ch[0] = add(k->ch[0], l, mid, a);
		else k->ch[1] = add(k->ch[1], mid + 1, r, a);
	}
	return k;
}
int qry(seg *x, int l, int r, int a, int b){
	if (a <= l && r <= b) return x->s;
	else{
		int mid = (l + r) >> 1;
		int ans = 0;
		if (a <= mid) ans += qry(x->ch[0], l, mid, a, b);
		if (b >  mid) ans += qry(x->ch[1], mid + 1, r, a, b);
		return ans;
	}
}
//work
int n, m, k, type; 
int pre[N];
pair<int, int> t[N];
void init(){
    LCT_init();
    rep(i,1,n) T[i].mn = T[i].w = inf, T[i].f = T[i].ch[0] = T[i].ch[1] = null;
    rep(i,n + 1, n + m) T[i].mn = T[i].w = i, T[i].f = T[i].ch[0] = T[i].ch[1] = null;
    rep(i,1,m){
        node *fa = findrt(a[i]), *fb = findrt(b[i]);
    	cout <<i<<endl;
        if (fa != fb) link(a[i], n + i), link(b[i], n + i), pre[i] = 0;
        else {
            int t = findmin(a[i], b[i]);
            pre[i] = t;
            cut(a[t], n + t), cut(b[t], n + t);
            link(a[i], n + i), link(b[i], n + i);
        }
    }
    seg_init();
    rep(i,1,m) t[i] = mp(pre[i], i);
    sort(t + 1, t + m + 1);
    int j = 1; rt[0] = segnull;
    rep(i,1,m){
    	rt[i] = rt[i - 1];
    	while (j <= n && t[j].first < i) rt[i] = add(rt[i], 1, m, t[j].second), j++;
    }
}
 
int qry(int l, int r){
 	return qry(rt[l], 1, m, l, r);
}
 
int main(){
	scanf("%d%d%d%d",&n,&m,&k,&type);
    rep(i,1,m) scanf("%d%d",&a[i],&b[i]);
    init();
    int lastans = 0;
    rep(i,1,k){
        int a, b; scanf("%d%d",&a,&b);
        if (type == 1) a ^= lastans, b ^= lastans;
        printf("%d\n",lastans = qry(a,b));
    }
    return 0;
}
