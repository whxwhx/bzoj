#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
const int N = 100100;

struct node{
	node *ch[2];
	int s;
}T[N * 30], *rt = &T[0];
int l = 0;

node *nn(){
	return &T[++l];
}
#define oc o->ch[a >> i & 1]
void ins(int a){
	node *o = rt;
	dep(i,30,0) {
		if (!oc) oc = nn();
		o = oc, (o->s)++;
	}
}

typedef long long LL;
#define cs(x, d) ((x->ch[d]) ? x->ch[d]->s : 0)

LL G(node *a, node *b, int t){
	if (!a || !b) return 0;
	if ((a->ch[0] && b->ch[1]) || (a->ch[1] && b->ch[0])){
		return max(G(a->ch[0], b->ch[1], t - 1), G(a->ch[1], b->ch[0], t - 1)) + (1LL << t);
	}else {
		return max(G(a->ch[0], b->ch[0], t - 1), G(a->ch[1], b->ch[1], t - 1));
	}
}

#define sz(o) (o ? o->s : 0)

LL g(node *a, node *b, int t){
	if (!a || !b) return 0;
	if (t < 0) return 0;
	LL ans = 0;
	if (b->ch[0]) 
		ans += g(a->ch[1], b->ch[0], t - 1) + (1LL << t) * sz(a->ch[1]);
	else 
		ans += g(a->ch[1], b->ch[1], t - 1);
	if (b->ch[1])
		ans += g(a->ch[0], b->ch[1], t - 1) + (1LL << t) * sz(a->ch[0]);
	else 
		ans += g(a->ch[0], b->ch[0], t - 1);
	return ans;
}

LL F(node *a, node *b, int t){
	if (!a && !b) return 0;
	if (t < 0) return 0;
	if (!a) {
		LL ans = F(b->ch[0], b->ch[1], t - 1);
		if (b->ch[0] && b->ch[1]) ans += (1LL << t) * (b->s - 1);
		return ans;
	}
	if (!b) {
		LL ans = F(a->ch[0], a->ch[1], t - 1);
		if (a->ch[0] && a->ch[1]) ans += (1LL << t) * (a->s - 1);
		return ans;
	}
	
	if (!((a->ch[0] && b->ch[1]) || (a->ch[1] && b->ch[0]))){
		if (a->ch[0] && b->ch[0]) return F(a->ch[0], b->ch[0], t - 1);
		if (a->ch[1] && b->ch[1]) return F(a->ch[1], b->ch[1], t - 1);
	}
	
	LL ans = 0;
	
	if (a->ch[0] && b->ch[1]) ans += F(a->ch[0], b->ch[1], t - 1) + (1LL << t) * (sz(a->ch[0]) + sz(b->ch[1]) - 1);
	if (a->ch[1] && b->ch[0]) ans += F(a->ch[1], b->ch[0], t - 1) + (1LL << t) * (sz(a->ch[1]) + sz(b->ch[0]) - 1);
	if ((a->ch[0] && b->ch[1]) && (a->ch[1] && b->ch[0])) 
		ans += max(G(a->ch[0], b->ch[0], t - 1), G(a->ch[1], b->ch[1], t - 1));
	else if (a->ch[0] && b->ch[1]){
		if (b->ch[0])
			ans += g(b->ch[0], a->ch[0], t - 1);
		else if (a->ch[1])
			ans += g(a->ch[1], b->ch[1], t - 1);
	}
	else if (a->ch[1] && b->ch[0]){
		if (a->ch[0])
			ans += g(a->ch[0], b->ch[0], t - 1);
		else if (b->ch[1])
			ans += g(b->ch[1], a->ch[1], t - 1);
	}
	return ans;
}

int main(){
	int n; scanf("%d",&n);
	rep(i,1,n) {
		int a; scanf("%d",&a);
		ins(a);
	}
	printf("%lld\n",F(rt, NULL, 30));
	return 0;
}