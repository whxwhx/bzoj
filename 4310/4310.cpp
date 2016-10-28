#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef long long LL;
int k, n;
const int N = 100100;
char s[N], c[N];
LL l = 0, r = 0;
int cl;

struct node{
	node *trans[26], *ch[26], *par;
	int l, p, pre;
	LL s;
}T[N * 2], *rt[N], *S = &T[0];
int Tl = 0;
node *nn(){
	return &T[++Tl];
}
node *add(node *w, int x){
	node *p = nn(); p->l = w->l + 1;
	for(;w && !w->trans[x]; w = w -> par) w->trans[x] = p;
	if (!w) p->par = S;
	else {
		node *q = w->trans[x];
		if (q->l == w->l + 1) p->par = q;
		else {
			node *r = nn(); *r = *q; r->l = w->l + 1;
			p->par = q->par = r;
			for(; w && w->trans[x] == q; w = w->par) w->trans[x] = r;
		}
	}
	return p;
}

int dfs_clock = 0;
void dfs(node *o){
	o->s = 0, o->pre = ++dfs_clock;
	rep(i,0,25) if (o->ch[i]) dfs(o->ch[i]), o->s += o->ch[i]->s + o->ch[i]->l - o->l;
}

void build(){
	rt[n + 1] = S;
	dep(i,n,1) rt[i] = add(rt[i + 1], s[i] - 'a');
	rep(i,1,Tl) T[i].p = -1;
	rep(i,1,n){
		int p = n;
		for(node *x = rt[i]; x && x->p == -1; x = x->par)
			p -= x->l - x->par->l, x->p = p;
	}
	rep(i,1,Tl) T[i].par->ch[s[T[i].p + 1] - 'a'] = &T[i];

	//T[i]没有拓扑序！要按照l排序，或者dfs！
	dfs(S);r = S->s;
}

int c_pre = 0;
void get(LL x){
	node *o = S;
	cl = 0;
	while (x){
		rep(i,0,25) if (o->ch[i]) {
			if (x <= o->ch[i]->s + o->ch[i]->l - o->l){
				int l = o->ch[i]->p, j = 0;
				while (x && j < o->ch[i]->l - o->l)
					j++, x--, c[++cl] = s[l + j];
				o = o->ch[i];
				break;
			} else x -= o->ch[i]->s + o->ch[i]->l - o->l;
		}
	}
	c_pre = o->pre;
}

int p[N];
char t[N];
bool check(){
	p[1] = 0;
	/*
	solution1:
		考虑如果前i个都是合法的，第i+1个加入的时候导致了不合法，那么前i个的一个后缀一定match了一个前缀
		也就是每加入一个fail树上一个链都必须满足
		同时维护一下最长match即可
	*/
	rep(i,2,cl){
		int j = p[i - 1];
		while (j && c[j + 1] != c[i]) j = p[j];
		if (c[j + 1] == c[i]) p[i] = j + 1; else p[i] = 0;
	}
	
	t[1] = c[1];
	rep(i,2,cl) t[i] = min(c[i], t[p[i - 1] + 1]);
	
	int cnt = 1, j = 1;
	rep(i,1,n){
		if (j > cl || s[i] > t[j]){
			cnt++; if (cnt > k || s[i] > c[1]) return false;
			if (s[i] == c[1]) j = 2; else j = 1;
		}else if (s[i] < t[j]) j = 1;
		else{
			while (s[i] != c[j]) j = p[j - 1] + 1;
			j++;
		}
	}
	return true;
	/*
	solution2: SAM裸上
	node *o = S;
	int cnt = 1, len = 0;
	dep(i,n,1){
		o = o->trans[s[i] - 'a'], len++;
		//while (o->par->l >= len) o = o->par;
		while (((o->pre > c_pre) || (o->pre == c_pre && len > cl)) && cnt <= k){
			o = S->trans[s[i] - 'a'], len = 1;
			cnt++;
		}
		if (cnt > k) return false;
	}
	return true;
	*/
}

int main(){
	scanf("%d",&k);
	scanf("%s",s + 1); n = strlen(s + 1);
	build();
	while (l + 1 < r){
		LL mid = (l + r) >> 1;
		get(mid);
		if (check()) r = mid; else l = mid;
	}
	get(r);
	rep(i,1,cl) printf("%c",c[i]);
	return 0;
}