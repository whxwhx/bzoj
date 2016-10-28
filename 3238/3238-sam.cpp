#include <iostream>
#include <cstdio>
#include <cmath>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define Rep(i,a) for(int i = 0; i < a; i++)
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
#define ab(a) ((a) > 0 ? (a) : -(a))
#define mp(a,b) make_pair(a,b)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
const int N = 1000010;
struct node{
	node *trans[26], *ch[26], *par;
	int l, p;
	bool end;
}T[N], *S = &T[0];
int tl = 0;
node *nn(){
	++tl; 
	T[tl].end = false, T[tl].l = 0, T[tl].p = -1;
	return &T[tl];
}
node *p = S, *nd[N];
void add(int x){
	node *w = p;
	p = nn(), nd[ p->l = w->l + 1 ] = p;
	for (; w && !(w->trans[x]); w = w->par) w->trans[x] = p;
	if (!w) p->par = S;
	else {
		node *q = w->trans[x];
		if (w->l + 1 == q->l) p->par = q;
		else{
			node *r = nn(); *r = *q, r->l = w->l + 1;
			p->par = q->par = r;
			for(; w && w->trans[x] == q; w = w->par) w->trans[x] = r;
		}
	}
}
void build(char *s){
	int n = strlen(s + 1);
	dep(i,n,1) add(s[i] - 'a');
	rep(i,1,n){
		nd[i]->end = true; int p = n;
		for(node *x = nd[i]; x && x->par && x -> p == -1; x = x -> par)
			p -= x->l - x->par->l, x -> p = p;
	}
	rep(i,1,tl) T[i].par->ch[s[T[i].p + 1] - 'a'] = &T[i]; 
}
char s[N];
LL ans = 0;
int dfs(node *o){
	int sz = 0; if (o->end) sz++;
	rep(i,0,25) if (o->ch[i]) sz += dfs(o->ch[i]);
	ans -= 1LL * (o->l - o->par->l) * sz * (sz - 1);
	return sz; 
}
int main(){
	scanf("%s",s + 1);
	int n = strlen(s + 1);
	build(s);
	ans = 1LL * (n - 1) * n * (n + 1) >> 1;
	rep(i,0,25) if (S->ch[i]) dfs(S->ch[i]);
	printf("%lld\n",ans);
}
//教训1：注意o->l的含义是从S到这个节点的距离，而不是这条边的长。、