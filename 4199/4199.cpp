#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define mp(a,b) make_pair(a,b)
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))
using namespace std;
const int N = 300000 + 10;
typedef long long LL;
char s[N];
struct mnx{
	int mn1, mn2, mx1, mx2;
};
int r1[5], r2[5];
mnx merge(const mnx &a, const mnx &b){
	r1[1] = a.mn1, r1[2] = a.mn2, r1[3] = b.mn1, r1[4] = b.mn2;
	r2[1] = a.mx1, r2[2] = a.mx2, r2[3] = b.mx1, r2[4] = b.mx2;
	sort(r1 + 1, r1 + 5), sort(r2 + 1, r2 + 5);
	mnx ans = (mnx){r1[1], r1[2], r2[4], r2[3]};
	return ans;
}
struct node{
	node *trans[26], *par;
	int s, l;
	mnx t;
}T[N * 2], *p = &T[0], *S = &T[0];
int tl = 0;
const int inf = 1000000001;
node *nn(){
	++tl;
	T[tl].t = (mnx){inf, inf, -inf, -inf};//小心初始化的问题！（因为新建了r嘛）
	return &T[tl];
}
void add(int x, int a){
	node *w = p;
	p = nn(), p->l = w->l + 1, p->s = 1;
	(p->t).mn1 = inf, (p->t).mx1 = -inf;
	if (a < 0) (p->t).mn1 = a; else (p->t).mx1 = a;
	(p->t).mn2 = inf, (p->t).mx2 = -inf;
	for(;w && !w->trans[x];w = w->par) w->trans[x] = p;
	if (!w) p->par = S;
	else{
		node *q = w->trans[x];
		if (q->l == w->l + 1) p->par = q;
		else{
			node *r = nn(); r->l = w->l + 1, r->par = q->par;
			rep(i,0,25) r->trans[i] = q->trans[i];
			q->par = p->par = r;
			for(;w && w->trans[x] == q;w = w->par) w->trans[x] = r;
		}
	}
}
int a[N];
void build(char *s){
	int l = strlen(s + 1);
	dep(i,l,1) add(s[i] - 'a', a[i]);
}
LL ans1[N], ans2[N];
pair<int, int> t[N * 2];
void work(){
	T[0].t = (mnx){inf, inf, -inf, -inf};
	rep(i,1,tl) t[i] = mp(T[i].l, i);
	sort(t + 1, t + tl + 1);
	rep(i,0,tl) ans1[T[i].l] += 1LL * (T[i].s) * (T[i].s - 1) / 2;
	dep(i,tl,1){
		int x = t[i].second;
		ans1[T[x].par->l] += 1LL * (T[x].par->s) * T[x].s;
		T[x].par->s += T[x].s;
	}
	dep(i,tl,1){
		int x = t[i].second;
		T[x].par->t = merge(T[x].par->t, T[x].t);
	}
	rep(i,0,tl)if (T[i].s > 1){
		if (T[i].t.mx1 != -inf && T[i].t.mx2 != -inf)
			ans2[T[i].l] = max(ans2[T[i].l], 1LL * T[i].t.mx1 * T[i].t.mx2);
		if (T[i].t.mn1 != inf && T[i].t.mn2 != inf)
			ans2[T[i].l] = max(ans2[T[i].l], 1LL * T[i].t.mn1 * T[i].t.mn2);
		if (T[i].t.mx1 != -inf && T[i].t.mn1 != inf)
			ans2[T[i].l] = max(ans2[T[i].l], 1LL * T[i].t.mx1 * T[i].t.mn1);
	}
}
int main(){
	int n; scanf("%d",&n);
	scanf("%s",s + 1);
	rep(i,1,n) scanf("%d",&a[i]);
	rep(i,0,n - 1) ans2[i] = - 1LL * inf * inf;
	build(s);
	work();
	dep(i,n - 1,1) ans1[i - 1] += ans1[i];
	dep(i,n - 1,1) ans2[i - 1] = max(ans2[i - 1], ans2[i]);
	rep(i,0,n - 1) if (ans1[i] == 0) printf("0 0\n"); else printf("%lld %lld\n",ans1[i],ans2[i]);
}