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

const int N = 100100, mod = 1000000009;

char s[N], op[10];
int pw[N], n;

struct str{ int h, l; };
str operator + (const str &a, const str &b){ return (str){( a.h + 1LL * pw[a.l] * b.h ) % mod, a.l + b.l}; }
bool operator == (const str &a, const str &b){ return (a.h == b.h && a.l == b.l); }

struct node *null;

struct node{
	node *ch[2];
	str s, v; int r;
	void upd(){ s = ch[0]->s + v + ch[1]->s; }
}T[N * 70]; int l = 0; 
node *rt[N];

void init(){ 
	null = &T[0]; null->ch[0] = null->ch[1] = null;
	null->s = null->v = (str){0, 0}, null->r = 0x7fffffff;
}

#define oc(d) (o->ch[d])
#define os (o->s)
#define ov (o->v)
node *nn(char c)
{ node *o = &T[++l]; oc(0)=oc(1)=null; os=ov=(str){c -'a'+1,1}; o->r=rand(); return o;}

node *merge(node *a, node *b){
	if (a == null) return b; if (b == null) return a;
	if (a->r < b->r)
	{ node *k = nn('a'); *k = *a; k->ch[1] = merge(k->ch[1], b); k->upd(); return k; } 
	else 
	{ node *k = nn('a'); *k = *b; k->ch[0] = merge(a, k->ch[0]); k->upd(); return k; }
}

#define lcs (oc(0)->s).l
str qry(node *o, int l){
	if (!l) return (str){0,0};
	if (l <= lcs) return qry(oc(0), l); 
	else return qry(oc(0), lcs) + ov + qry(oc(1), l - lcs - 1);
}

#define mid ((l + r) >> 1)
#define lc (x << 1)
#define rc (lc + 1)
#define lcq lc, l, mid
#define rcq rc, mid + 1, r

#define tx tag[x]
#define tlc tag[lc]
#define trc tag[rc]
#define txs (tx->s)
namespace seg{
	node *tag[N * 4]; int a, b; node *c;
	void build(int x, int l, int r)
	{ if (l == r) tag[x] = rt[l]; else { tag[x] = null; build(lcq), build(rcq);} }
	int len(int x, int l, int r) 
	{ if (l == r) return txs.l; else return txs.l + (a <= mid ? len(lcq) : len(rcq)); }
	int len(int x){ a = x; return len(1, 1, n); }
	void push(int x){ tlc = merge(tx, tlc); trc = merge(tx, trc); tx = null; }
	void add(int x, int l, int r){
		if (a <= l && r <= b) tag[x] = merge(c, tag[x]); else 
		{ push(x); if (a <= mid) add(lcq); if (b > mid) add(rcq); }
	}
	str qry(int x, int l, int r) {
		if (b <= txs.l) return qry(tx, b);
		else { b -= txs.l; return txs + (a <= mid ? qry(lcq) : qry(rcq)); }
	}
	str qry(int x, int l){ a = x, b = l; return qry(1, 1, n); }
	int lcp(int x){
		int l = 0, r = min(len(x - 1), len(x)) + 1;
		while (l + 1 < r) if (qry(x - 1, mid) == qry(x, mid)) l = mid; else r = mid;
		return l;
	}
}

namespace lcp{
	int mn[N * 4], d[N * 4], a, b, c;

	void build(int x, int l, int r) { 
		if (l == r) mn[x] = (l == 1 ? 0 : seg::lcp(l)) ; else 
		{ build(lcq), build(rcq); mn[x] = min(mn[lc], mn[rc]); }
	}
	void push(int x, int l, int r){
		mn[x] += d[x]; if (l < r) d[lc] += d[x], d[rc] += d[x]; d[x] = 0;
	}
	void add(int x, int l, int r){
		if (a <= l && r <= b) { d[x] += c; push(x, l, r); }
		else {
			if (a <= mid) add(lcq); else push(lcq);
			if (b >  mid) add(rcq); else push(rcq);
			mn[x] = min(mn[lc], mn[rc]);
		}
	}
	int qry(int x, int l, int r){
		push(x, l, r);
		if (a <= l && r <= b) return mn[x]; else {
			int ans = N + 10;
			if (a <= mid) ans = min(ans, qry(lcq));
			if (b >  mid) ans = min(ans, qry(rcq));
			return ans;
		}
	}
	int qry(int l, int r) { a = l, b = r; return qry(1, 1, n); }
	void upd(int x, int l, int r){
		push(x, l, r);
		if (l == r) mn[x] = seg::lcp(l); else {
			if (a <= mid) upd(lcq), push(rcq); else upd(rcq), push(lcq);
			mn[x] = min(mn[lc], mn[rc]);
		}
	}
}

int main(){
	int m; scanf("%d%d",&n,&m);
	pw[0] = 0; rep(i,1,n) pw[i] = 27LL * pw[i - 1] % mod;

	init();
	rep(i,1,n){
		scanf("%s",s + 1);
		rt[i] = null;
		int l = strlen(s + 1);
		rep(i,1,l) { node *c = nn(s[i]); rt[i] = merge(rt[i], c); };
	}

	seg::build(1, 1, n);
	lcp::build(1, 1, n);
	
	rep(i,1,m){
		scanf("%s",op + 1);
		if (op[1] == 'I'){
			int l, r; scanf("%d%d%s",&l,&r,s + 1);
			node *rt = null; int L = strlen(s + 1);
			rep(i,1,L) { node *c = nn(s[i]); rt = merge(rt, c); }
			seg::a = l, seg::b = r, seg::c = rt, seg::add(1, 1, n);
			
			lcp::a = l + 1, lcp::b = r, lcp::c = L, lcp::add(1, 1, n);
			lcp::a = l; if (l > 1) lcp::upd(1, 1, n);
			lcp::a = r + 1; if (r < n) lcp::upd(1, 1, n);
		} else {
			int l, r; scanf("%d%d",&l,&r);
			if (l == r) printf("%d\n",seg::len(l));
			else printf("%d\n",lcp::qry(l + 1, r));
		}
	}
	return 0;
}