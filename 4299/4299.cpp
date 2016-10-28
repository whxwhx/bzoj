#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 100010;
typedef long long LL;
struct node{
	node *ch[2];
	LL s;
}T[N * 61];
int l = 0;
node *nn(){
	l++;
	T[l].s = 0, T[l].ch[0] = T[l].ch[1] = NULL;
	return &T[l];
}
node *rt[N];
#define c0(o) (o ? o->ch[0] : NULL)
#define c1(o) (o ? o->ch[1] : NULL)
node* add(node *o, int l, int r, int a){
	node *k = nn(); if (o) *k = *o;
	if (l == r) (k->s) += a;else{
		int mid = (l + r) >> 1;
		(k->s) += a;
		if (a <= mid) 
			k->ch[0] = add(c0(o), l, mid, a); 
		else 
			k->ch[1] = add(c1(o), mid + 1, r, a);
	}
	return k;
}
LL sum(node *o, int l, int r, int a){
	if (!o) return 0;
	if (r <= a) return o->s; else{
		int mid = (l + r) >> 1;
		LL ans = 0;
		if (a >= l) ans += sum(c0(o), l, mid, a);
		if (a > mid) ans += sum(c1(o), mid + 1, r, a);
		return ans;
	}
}
int a[N];
const int inf = 1000000000;
int main(){
	int n; scanf("%d",&n);
	rep(i,1,n) scanf("%d",&a[i]);
	rt[0] = NULL;
	rep(i,1,n) rt[i] = add(rt[i - 1], 1, inf, a[i]);
	int m; scanf("%d",&m);
	rep(i,1,m){
		int a, b; scanf("%d%d",&a,&b);
		LL s = 0, t;
		while ((t = sum(rt[b], 1, inf, s + 1) - sum(rt[a - 1], 1, inf, s + 1)) > s){
			s = t;
			if (s + 1 > inf) break;
		}
		printf("%lld\n",s + 1);
	}
	return 0;
}