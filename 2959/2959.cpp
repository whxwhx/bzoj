#include <iostream>
#include <cstdio>
#include <cmath>
#include <set>
#include <map>
#include <queue>
#include <bitset>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define Rep(i,a) for(int i = 0; i < (a); i++)
#define rep(i,a,b) for(int i = (a); i <= (b); i++)//(a)!
#define dep(i,a,b) for(int i = (a); i >= (b); i--)
#define ab(a) ((a) > 0 ? (a) : -(a))
#define mp(a,b) make_pair((a),(b))
#define pb(a) push_back(a)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;

const int N = 150010;
int f[N], val[N], A[N];
int find(int x){
	return f[x] == x ? x : f[x] = find(f[x]);
}

struct node *null;
struct node{
	node *ch[2], *f;
	bool rev;
	int s, v;
	bool c(){return f == null || (f->ch[0] != this && f->ch[1] != this);}
	int d(){return f->ch[1] == this;}
	void st(node *c, int d){ch[d] = c, c->f = this;}
	void upd(){s = ch[0]->s + ch[1]->s + v;}
	void push(){
		if (rev){
			swap(ch[0], ch[1]);
			ch[0]->rev ^= 1, ch[1]->rev ^= 1;
			rev = 0;
		}
	}
}T[N];

int l = 0;
node *nn(){
	return &T[++l];
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
	if (o->f != null) o->f = &T[find(o->f - T)];
	o->upd();
}

void access(node *o){
	node *t = o;
	for(node *c = null; o != null; o = o->f){
		splay(o);
		o->ch[1] = c; 
		o->upd();
		c = o;
	}
	splay(t);
}

void mroot(node *o){
	access(o), o->rev ^= 1;
}

void link(node *u, node *v){
	mroot(v), v->f = u;
}

int g[N];
int fg(int x){
	return g[x] == x ? x : g[x] = fg(g[x]);
}

void merge(node *o, node *a){
	if (o->ch[0] != null) merge(o->ch[0], a);
	if (o->ch[1] != null) merge(o->ch[1], a);
	o->ch[0] = o->ch[1] = null;
	if (o != a) f[o - T] = a - T, val[a - T] += val[o - T];
}

int main(){
	null = &T[0];
	null->ch[0] = null->ch[1] = null->f = null;
	null->s = null->v = 0;
	int n, m; scanf("%d%d",&n,&m);
	rep(i,1,n){
		scanf("%d",&T[i].v), T[i].s = T[i].v;
		A[i] = val[i] = T[i].v;
		T[i].ch[0] = T[i].ch[1] = T[i].f = null; T[i].rev = false;
		f[i] = g[i] = i;
	}

	rep(i,1,m){
		int op, a, b; scanf("%d%d%d",&op,&a,&b);
		if (op == 1){
			int ga = fg(a), gb = fg(b);
			if (ga != gb) {
				int fa = find(a), fb = find(b);
				link(&T[fa], &T[fb]);
				g[ga] = gb;
			}else{
				int fa = find(a), fb = find(b);
				if (fa != fb){
					mroot(&T[fa]); access(&T[fb]);
					merge(&T[fb], &T[fb]);
					T[fb].v = T[fb].s = val[fb];
				}
			}
		}else if (op == 2){
			int fa = find(a);
			val[fa] += b - A[a], A[a] = b;
			access(&T[fa]), T[fa].v = val[fa], T[fa].upd();
		}else if (op == 3){
			int ga = fg(a), gb = fg(b);
			if (ga != gb) printf("-1\n");
			else{
				int fa = find(a), fb = find(b);
				mroot(&T[fa]), access(&T[fb]);
				printf("%d\n",T[fb].s);
			}
		}
	}
	return 0;
}