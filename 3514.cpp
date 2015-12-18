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
    int mn, t;
    void upd(){
        mn = min(ch[0]->mn, ch[1]->mn), mn = min(mn, t);
    }
    void st(node *c, int d){ ch[d] = c, c->f = *this; }
}T[N], *null = &T[0];
void LCT_init(){
 
}
void rot(node *o){
 
}
void splay(){
 
}
void access(){
 
}
void link(){
 
}
void cut(){
 
}
 
//segment-tree
 
//work
int pre[N];
void init(){
    LCT_init();
    rep(i,1,m){
        int fa = findrt(a), fb = findrt(b);
        if (fa != fb) link(a, b, i);
        else {
            int t = findmin(a, b);
            pre[i] = t;
            cut(a[t], b[t]);
            link(a[t], b[t], i);
        }
    }
}
 
int qry(){
 
}
 
int main(){
    int n, m, k, type; scanf("%d%d%d%d",&n,&m,&k,&type);
    rep(i,1,m) scanf("%d%d",&a[i],&b[i]);
    init();
    int lastans = 0;
    rep(i,1,k){
        int a, b; scanf("%d%d",&a,&b);
        if (type == 1) a ^= lastans, b ^= lastans;
        printf("%d\n",lastans = qry(a,b));
    }
}
