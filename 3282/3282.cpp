
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
inline int read(){
    int x=0,f=1;char c=getchar();
    while (c<'0' || c>'9') {if (c=='-') f=-1;c=getchar();}
    while (c>='0' && c<='9') x=x*10+c-'0',c=getchar();
    return x*f;
}

const int N=300010;
struct node* null;
struct node{
    node *ch[2], *f; int s, v; bool rev;
    int d() { return f->ch[1] == this; }
    bool c() { return f == null || (f->ch[0] != this && f->ch[1] != this);}
    void upd(){ s = v ^ (ch[0]->s) ^ (ch[1]->s); }
    void push() { if (rev){ rev = 0; swap(ch[0], ch[1]); ch[0]->rev ^= 1, ch[1]->rev ^= 1;}}
    void st(node *o, int d) { (ch[d] = o)->f = this; }
}T[N];
void rot(node *o){
    node *f = o->f; int d = o->d(); if (!f->c()) f->f->st(o, f->d()); else o->f = f->f;
    f->st(o->ch[d^1], d), o->st(f, d^1), f->upd();
}
void fix(node *o) { if (!o->c()) fix(o->f); o->push(); }
void splay(node *o){
    fix(o);
    while (!o->c()){ if (!o->f->c()) (o->d() == o->f->d() ? rot(o->f) : rot(o)); rot(o); }
    o->upd();
}
void access(node *o){
    node *t = o; 
    for(node *c = null; o != null; o = o->f) { splay(o); o->ch[1] = c; (c = o)->upd(); }
    splay(t);
}
void mroot(node *o){ access(o); o->rev ^= 1; }
void link(node *u, node *v) { mroot(u), u->f = v; access(u); }
void cut(node *u, node *v) { mroot(u), access(v); v->ch[0] = u->f = null; v->upd(); }
node *findrt(node *o) 
{ access(o); for(o->push(); o->ch[0] != null; o = o->ch[0], o->push()); splay(o); return o;}
int main(){
    int n=read(),m=read();
    null=&T[0], null->s=null->rev=0, null->ch[0]=null->ch[1]=null->f=null;
    rep(i,1,n) T[i].ch[0]=T[i].ch[1]=T[i].f=null, T[i].rev=0, T[i].s=T[i].v=read();
    rep(i,1,m){
        int tp=read(),x1=read(),y1=read();
        node *x=&T[x1],*y=tp==3 ? null :&T[y1];
        if (tp==0) mroot(x),access(y),printf("%d\n",y->s);
        else if (tp==1) { if (findrt(x)!=findrt(y)) link(x,y); }
        else if (tp==2) { if (findrt(x)==findrt(y)) cut(x,y); }
        else if (tp==3){
            mroot(x);x->v=y1;x->upd();
        }
    }
}