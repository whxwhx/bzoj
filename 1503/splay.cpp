#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
const int N = 100000 + 10;
struct node{
	node *ch[2], *f;
	int s, w, t;
	int d(){return f->ch[1] == this};
	void upd(){s = (ch[0]->s) + (ch[1]->s) + t;}
}T[N], *root, *null;
int l = 0;
node *nn(){
	return T[++l];
}
void rot(node *o){
	node *f = o->f; int d = o -> d();
	if (f == null) o->f = null; else o->f->st(o, f->d());
	f->st(o->ch[d ^ 1], d), o -> st(f, d ^ 1);
	f->upd();
}
void splay(node *o){
	while (o->f != null){
		if (o->f->f == null) rot(o); 
		else (o->d() == o->f->d()) ? (rot(o->f), rot(o)) : (rot(o), rot(o));
	}
	o->upd();
}
void ins(node *o){
	node *
}
int main(){
	int n, min, m;

}