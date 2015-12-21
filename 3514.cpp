#include <iostream>
#include <cstdio>
#include <algorithm>
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
	void upd(){mn = min(ch[0], ch[1]), mn = min(mn, w);}
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
void *findrt(node *o){
	access(o);
	while (o->ch[0] != null) o = o->ch[0];
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
struct segnode{

};
//work
int n, m, k, type; 
int pre[N];
void init(){
    LCT_init();
    rep(i,1,n) T[i].mn = T[i].w = inf, T[i].f = T[i].ch[0] = T[i].ch[1] = null;
    rep(i,n + 1, n + m) T[i].mn = T[i].w = i, T[i].f = T[i].ch[0] = T[i].ch[1] = null;
    rep(i,1,m){
        node *fa = findrt(a[i]), *fb = findrt(b[i]);
        if (fa != fb) link(a[i], n + i), link(b[i], n + i);
        else {
            int t = findmin(a[i], b[i]);
            pre[i] = t;
            cut(a[t], n + t), cut(b[t], n + t);
            link(a[i], n + i), link(b[i], n + i);
        }
    }


}
 
int qry(){
 
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
}
