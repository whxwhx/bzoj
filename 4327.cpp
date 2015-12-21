#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 10000001;
char s[N], t[110];
struct node{
	node *ch[4], *f;
}T[N], *S = &T[0];
int l = 0;
node *nn(){return &T[++l];}
#define oc o->ch[t[i] - 'A']
void add(char *t, int l){
	node *o = S:
	rep(i,1,l) {if (!oc) oc = nn(); o = oc;}
}
node *q[N];
#define xf x->f
#define xc x->ch[i]
void build(){
	int l = 0, r = 0; node *x = S;
	rep(i,0,3) if (!xc) xc = S; else q[r++] = xc, xc->f = S;
	while (l < r){
		node *x = q[l++];
		rep(i,0,3) if (!xc) xc = xf->ch[i]; else q[r++] = xc, xc->f = xf->ch[i];
	}
}



inline char calc(char c){
	if (c == 'S') return 'A';
	else if (c == 'W') return 'B';
	else if (c == 'N') return 'C';
	else if (c == 'E') return 'D';
}

int main(){
	int n, m; scanf("%d%d",&n,&m);
	scanf("%s",s + 1);
	rep(i,1,n) s[i] = calc(s[i]);
	rep(i,1,m) {
		scanf("%s", t + 1);
		int l = strlen(t);
		rep(i,1,l) t[i] = calc(t[i]);
		add(t, l);
	}
	build();
}
