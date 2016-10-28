
struct node{
    node *ch[2],*f;
    int fl,s,v;
    void upd(){s= (ch[0]->s) ^ (ch[1]->s) ^ v; }
    int d(){return f->ch[1]==this;}
    bool c(){return f->ch[0]==this || f->ch[1]==this;}
    void st(node *c,int d){ch[d]=c;c->f=this;}
    void push(){
        if (fl){
            ch[0]->fl^=1;ch[1]->fl^=1;
            swap(ch[0],ch[1]);
            fl=0;
        }
    }
}T[N],*null;
void rot(node *o){
    node *f=o->f;int d=o->d();
    if (f->c()) f->f->st(o,f->d()); else o->f=f->f;
    f->st(o->ch[d^1],d);o->st(f,d^1);
    f->upd();
}
void fix(node *o){
    if (o->c()) fix(o->f);
    o->push();
}
void splay(node *o){
    fix(o);
    while (o->c())
        if (!o->f->c()) rot(o); else 
            (o->d()==o->f->d()) ? (rot(o->f),rot(o)) : (rot(o),rot(o));
    o->upd();
}
void access(node *o){
    node *c=null,*t=o;
    for(;o!=null;o=o->f){
        splay(o);
        o->ch[1]=c, o->upd();
        c=o;
    }
    splay(t);
}
node *findrt(node *o){
    access(o);
    while (o->ch[0]!=null) o=o->ch[0];
    return o;
}
void mroot(node *o){
    access(o);o->fl^=1;
}
void link(node *x,node *y){
    mroot(x);x->f=y;
}
void cut(node *x,node *y){
    mroot(x);access(y);
    if (y->ch[0]==x) x->f=y->ch[0]=null;
}