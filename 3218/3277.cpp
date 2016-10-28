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
#define Rep(i,a) for(int i = 0; i < a; i++)
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
#define ab(a) ((a) > 0 ? (a) : -(a))
#define mp(a,b) make_pair(a,b)
#define pb(a) push_back(a)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
const int N = 200000 + 20;

struct edge{
	int to, pre;
}e[N];
int u[N], l = 0;
void ins(int a, int b){
	e[++l] = (edge){b, u[a]}, u[a] = l;
}
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define v e[i].to

int a[N];
struct node{
	node *trans[26], *par;
	int l, w;
}T[N] , *S = &T[0];
int tl = 0;
node *nn(){return &T[++tl];}

node* add(node *p, int x){
	node *w = p;
	p = nn(), p->l = w->l + 1;
	for(;w && !w->trans[x];w = w->par) w->trans[x] = p;
	if (!w) p->par = S;
	else {
		node *q = w->trans[x];
		if (q->l == w->l + 1) p->par = q;
		else{
			node *r = nn(); *r = *q, r->l = w->l + 1, r->w = 0; //! r->w = 0!
			p->par = q->par = r;
			for(;w && w->trans[x] == q; w = w->par) w->trans[x] = r;
		}
	}
	return p;
}

int n, k, dfs_pre[N], dfs_ed[N], dfs_clock = 0;
char s[N];
void dfs(int x){
	dfs_pre[x] = ++dfs_clock; 
	if (T[x].w) a[dfs_pre[x]] = T[x].w;
	reg(i,x) dfs(v);
	dfs_ed[x] = dfs_clock;
}


int sum1[N];
void add(int x){
	for(;x <= dfs_clock; x += (-x) & x) sum1[x]++;
}

int sum(int x){
	int ans = 0;
	for(;x;x -= (-x) & x) ans += sum1[x];
	return ans;
}


int last[N], pre[N], ans[N];

struct qyp{
	int pre, x, f;
};
typedef vector<qyp>::iterator vit;
vector<qyp> qy[N];

#define oc o->trans[s[i] - 'a']

void build(){
	rep(i,1,n){
		scanf("%s", s + 1);
		int l = strlen(s + 1);
		node *q = S;
		dep(j,l,1){
			q = add(q, s[j] - 'a');
			q->w = i;
		}
	}

	rep(i,1,tl) ins(T[i].par - T, i);
	dfs(0);
	rep(i,1,tl){
		int l = dfs_pre[i], r = dfs_ed[i];
		qyp tmp = (qyp){l - 1, i, -1};
		qy[l - 1].pb(tmp);
		tmp = (qyp){l - 1, i, 1};
		qy[r].pb(tmp);
	}
}

void work(){
	int n = dfs_clock;
	rep(i,1,n) if (a[i]){
		if (!last[a[i]])
			last[a[i]] = i;
		else 	
			pre[i] = last[a[i]], last[a[i]] = i;
	}

	rep(i,1,n) {
		if (a[i]) add(pre[i] + 1);
		for(vit it = qy[i].begin(); it != qy[i].end(); it++)
			ans[(*it).x] += (*it).f * sum((*it).pre + 1);
	}
}

int f[N];
LL Ans[N];
void calc(int x, int w){
	if (ans[x] >= k) w = T[x].l;
	if (T[x].w) Ans[T[x].w] += w;
	reg(i,x) calc(v, w);
}
//不能直接按照l排序处理，原因是有长度为0的边存在的话，按照l排序处理无法保证T[i].par在T[i]之前

int main(){
	scanf("%d%d",&n,&k);
	build(); 
	work();
	calc(0, 0);
	rep(i,1,n) printf("%lld ",Ans[i]);
	printf("\n");
}