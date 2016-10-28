#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define rep(i,a,b) for(int i=a;i<=b;i++)
const int N = 100000 + 10;
struct edge{
	int a, b, s, t;
}e[N * 2];
bool cmp(const edge &a, const edge &b){
	return a.s < b.s || (a.s == b.s && a.t > b.t);
}

const int inf = N * 10;
struct node *null;
struct node{
	node *ch[2], *f;
	int s, t, v;
	node* mt;
	bool rev;
	void push(){if (rev) rev = 0, swap(ch[0], ch[1]), ch[0]->rev ^= 1, ch[1]->rev ^= 1;}
	void upd(){
		s = ch[0]->s + ch[1]->s + v;
		mt = ch[0]->mt;
		if (ch[1]->mt->t < mt->t) mt = ch[1]->mt;
		if (v && t < mt->t) mt = this;
	}
	void st(node *o, int d){ch[d] = o, o->f = this;}
	bool c(){return f == null || (f->ch[0] != this && f->ch[1] != this);}
	bool d(){return f->ch[1]==this;}
}T[N * 3];

void rot(node *o){
	node *f = o->f; int d = o -> d();
	if (f->c()) o->f = f->f; else f->f->st(o,f->d());//upd(f->f)?
	f->st(o->ch[d^1], d), o->st(f, d^1);
	f->upd();
}
void fix(node *o){
	if (!o->c()) fix(o->f);
	o->push();
}
void splay(node *o){
	fix(o);
	while (!o->c())
		if (o->f->c()) rot(o); else
			(o->f->d() == o->d()) ? (rot(o->f), rot(o)): (rot(o), rot(o));
	o->upd();
}
void access(node *o){
	node *t = o;
	for(node *c = null; o != null; o = o->f){
		splay(o);
		o->st(c, 1), o->upd();
		c = o;
	}
	splay(t);
}
void mroot(node *o){
	access(o), o->rev ^= 1;//access!
}
void link(node *u, node *v){
	mroot(v), v->f = u, access(v);
}
void cut(node *v){
	access(v), v->ch[0]->f = null, v->ch[0] = null, v->upd();
}
node *findrt(node *o){
	access(o);o->push();
	while (o->ch[0] != null) o = o->ch[0], o->push();
	splay(o);
	return o;
}
node *qry(node *u, node *v){
	mroot(u), access(v);
	return v->mt;
}
int dis(node *u, node *v){
	mroot(u), access(v);
	return v->ch[0]->s;
}
void init(){
	null = &T[0];
	null->ch[0] = null->ch[1] = null->f = null->mt = null;
	null->s = 0, null->t = inf, null->v = null -> rev = 0;
}

#define dot(a) (a + m)
int mxt = 0;
int main(){
	int n, m, t1; scanf("%d%d%d",&n,&m,&t1);
	rep(i,1,m) scanf("%d%d%d%d",&e[i].a,&e[i].b,&e[i].s,&e[i].t), e[i].s++;
	sort(e + 1, e + m + 1, cmp);
	init();
	rep(i,1,n) T[dot(i)] = *null;
	int i = 1;
	rep(j,1,t1){
		for(;i <= m && e[i].s <= j; i++){
			T[i].ch[0] = T[i].ch[1] = T[i].f = null;
			T[i].mt = &T[i];
			T[i].s = T[i].v = 1, T[i].t = e[i].t, T[i].rev = 0;
			if (findrt(&T[dot(e[i].a)]) == findrt(&T[dot(e[i].b)])){
				node *t = qry(&T[dot(e[i].a)], &T[dot(e[i].b)]);
				int tt = t - T;
				int ds = dis(&T[dot(e[i].a)], &T[dot(e[i].b)]);

				if (t->t < e[i].t){
					mroot(t), cut(&T[dot(e[tt].a)]), cut(&T[dot(e[tt].b)]);
					link(&T[i], &T[dot(e[i].a)]), link(&T[i], &T[dot(e[i].b)]);
					if ((ds & 1) == 0) mxt = max(mxt, t->t);
				}else 
					if ((ds & 1) == 0) mxt = max(mxt, e[i].t);
			}else
				link(&T[i], &T[dot(e[i].a)]), link(&T[i], &T[dot(e[i].b)]);
		}
		if (mxt < j) printf("Yes\n"); else printf("No\n");
	}
	return 0;
}