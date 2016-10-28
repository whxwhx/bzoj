#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N = 8 + 1, L = 6 + 1;


struct node{
	node *ch[10], *f; 
	int v;
}T[N * L], *root;
int l;
node *nn(){
	l++;
	rep(i,0,9) T[l].ch[i] = NULL;
	T[l].f = NULL;T[l].v = 0;
	return &T[l];
}
#define oc o->ch[c[i] - 'a']
void ins(char *c, int t){
	node *o = root;
	int l = strlen(c);
	rep(i,0,l - 1) {if (!oc) oc = nn(); o = oc;}
	o->v = 1 << t;
}
node *q[N * L];
#define xc x->ch[i]
#define xcf xc->f
#define xf x->f
int n, l1, t1;
void build(){
	int l = 0, r = 0;
	node *x = root;
	rep(i,0,t1 - 1) if (xc) q[r++] = xc, xcf = root; else xc = root;
	while (l < r){
		node *x = q[l++];
		rep(i,0,t1 - 1) if (!xc) xc = xf->ch[i]; else 
			q[r++] = xc, xcf = xf->ch[i];
	}
}

char s[10];
int p[10];

typedef long double ld;
struct equ{
	ld x[N * L];
}e[N * L];

ld E[N * L][256];
void sol_equ(){
	rep(i,0,l){
		int t = i;
		rep(j,i + 1, l)
			if (fabs(e[j].x[i]) > fabs(e[t].x[i])) t = j;
		swap(e[i], e[t]);
		rep(j,i + 1, l){
			double f = e[j].x[i] / e[i].x[i];
			rep(k,i,l + 1) e[j].x[k] -= e[i].x[k] * f;
		}
	}
	dep(i,l,0){
		rep(k, i + 1, l) e[i].x[l + 1] -= e[k].x[l + 1] * e[i].x[k];
		e[i].x[l + 1] /= e[i].x[i];
	}
}
void calc(int t){
	rep(i,0,l) rep(j,0,l) e[i].x[j] = 0;
	rep(i,0,l)if ((T[i].v & t) == 0 && T[i].v){
		e[i].x[i] = 1, e[i].x[l + 1] = E[i][t ^ T[i].v];
	}else {
		e[i].x[i] = 1;
		rep(j,0,t1 - 1) e[i].x[T[i].ch[j] - T] -= (long double) p[j] / 10000.0; //j may appear twice or more times
		e[i].x[l + 1] = 1;
	}
	sol_equ();
	rep(i,0,l) E[i][t] = e[i].x[l + 1];
}
void work(){
	l = 0;
	scanf("%d%d%d",&n,&l1,&t1);
	root = &T[0]; rep(i,0,t1) root->ch[i] = NULL; root->f = root; root->v = 0;
	rep(i,0,n - 1) scanf("%s",s), ins(s, i);
	build();
	rep(i,0,t1 - 1) scanf("%d",&p[i]);
	rep(i,0,l) E[i][(1 << n) - 1] = 0;
	dep(i,(1 << n) - 2,0) calc(i);
	printf("%.10Lf\n",E[0][0]);
}
int main(){
	int c; scanf("%d",&c);
	while (c--) work();
}