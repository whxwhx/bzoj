#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
const int N = 100100;

struct edge{
	int to, pre;
}e[N * 2];
int u[N], l = 0;
void ins(int a, int b){
	e[++l] = (edge){b, u[a]}, u[a] = l;
}
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define v e[i].to

const int M = 1 << 18;

int rev[M];
int h[N], f[N];

struct node{
	node* ch[2];
	int tag;
	bool s, ed;
	void push(){
		if (tag){
			if (tag & 1) swap(ch[0], ch[1]);
			if (ch[0]) ch[0]->tag ^= tag >> 1;
			if (ch[1]) ch[1]->tag ^= tag >> 1;
			tag = 0;
		}
	}
	void upd(){
		if (!ch[0] || !ch[1]) s = 0;
		else s = ch[0]->s && ch[1]->s;
	}
}T[N * 25];
int Tl = 0;
node *nn(){
	return &T[++Tl];
}
#define oc o->ch[d >> i & 1]
node* par[18];
void insert(node *rt, int d){
	node *o = rt;
	dep(i,17,0){
		par[i] = o;
		o->push();
		if (!oc) oc = nn();
		o = oc;
	}
	o->ed = true;
	if (!o->s){
		o->s = 1;
		o = rt;
		rep(i,0,17) par[i]->upd();
	}
}

node* merge(node *a, node *b){
	if (!a) return b;
	if (!b) return a;
	if (a->ed) {a->s |= b->s; return a;}
	else {
		a->push(), b->push();
		a->ch[0] = merge(a->ch[0], b->ch[0]);
		a->ch[1] = merge(a->ch[1], b->ch[1]);
		a->upd();
		return a;
	}
}

int Mex(node *a){
	if (!a) return 0;
	a->push();
	if (!(a->ch[0])) return 0;
	if (a->ch[0]->s) return (Mex(a->ch[1]) << 1) | 1;
	else return Mex(a->ch[0]) << 1;
}

int mex(node *rt){
	return rev[Mex(rt)];
}

void xor_tag(node *rt, int d){
	if (rt) rt->tag ^= rev[d];
}

node *rt[N];

void print(node *o, int d){
	if (o->ed) cout <<' '<<d<<endl;
	else {
		o->push();
		if (o->ch[0]) print(o->ch[0], d << 1);
		if (o->ch[1]) print(o->ch[1], (d << 1) | 1);
	}
}
void dfs(int x, int fa){
	rt[x] = nn();
	int F = 0;
	reg(i,x) if (v != fa) dfs(v, x), F ^= f[v];
	reg(i,x) if (v != fa) {
		xor_tag(rt[v], F ^ f[v]);
		rt[x] = merge(rt[x], rt[v]);
	}
	if (!h[x])
		insert(rt[x], F);

	//if (x == 1) print(rt[x], 0);
	f[x] = mex(rt[x]);
	//printf("%d %d\n",x,f[x]);
}

int ans[N], ansl = 0;
void calc(int x, int fa, int d){
	int F = d;
	reg(i,x) if (v != fa) F ^= f[v];
	if (!F && !h[x]) ans[++ansl] = x;
	reg(i,x) if (v != fa) calc(v, x, F ^ f[v]);
}

int main(){
	int n; scanf("%d",&n);
	rep(i,1,n) scanf("%d",&h[i]);
	rep(i,1,M - 1) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << 17);
	rep(i,1,n - 1){
		int a, b; scanf("%d%d",&a,&b);
		ins(a, b), ins(b, a);
	}
	dfs(1,0);
	if (!f[1]) printf("-1\n");
	else {
		calc(1, 0, 0);
		sort(ans + 1, ans + ansl + 1);
		rep(i,1,ansl) printf("%d\n",ans[i]);
	}
	return 0;
}