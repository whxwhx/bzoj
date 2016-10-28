#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 10000001;

char s[N], t[110];
struct node{
	node *ch[4], *f, *par;
	int l;
}T[N], *S = &T[0], *rt[100010];
int l = 0;
bool vis[N];
node *nn(){return &T[++l];}
#define oc o->ch[t[i] - 'A']
node* add(char *t, int l){
	node *o = S;
	rep(i,1,l) {if (!oc) oc = nn(), oc->par = o; o = oc, o->l = i;}
	return o;
}
node *q[N];
#define xf x->f
#define xc x->ch[i]
void build(){
	int l = 0, r = 0; node *x = S;
	rep(i,0,3) if (xc) q[r++] = xc, xc->f = S; else xc = S;
	while (l < r){
		node *x = q[l++];
		rep(i,0,3) if (!xc) xc = xf->ch[i]; else 
			q[r++] = xc, xc->f = xf->ch[i];
	}
}



inline char calc(char c){
	if (c == 'S') return 'A';
	else if (c == 'W') return 'B';
	else if (c == 'N') return 'C';
	else if (c == 'E') return 'D';
}
#undef oc
#define oc o->ch[s[i] - 'A']

int main(){
	int n, m; scanf("%d%d",&n,&m);
	scanf("%s",s + 1);
	rep(i,1,n) s[i] = calc(s[i]);
	S->l = 0;
	rep(i,1,m){
		scanf("%s", t + 1);
		int l = strlen(t);
		rep(i,1,l) t[i] = calc(t[i]);
		rt[i] = add(t, l);
	}
        cout <<(bool)(S->ch[2])<<endl;
	build();
	node *o = S;
	vis[0] = 1;
	rep(i,1,n) o = oc, vis[o - T] = 1;
	rep(i,1,l) if (vis[i]) for(node *x = &T[i]; x != S && !vis[xf - T]; x = xf) vis[xf - T] = 1;
	rep(i,1,m)
		for(node *x = rt[i]; x; x = x->par) if (vis[x - T]){printf("%d\n",x->l);break;}
	return 0;
}
