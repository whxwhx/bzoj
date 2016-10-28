#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 60;
string S[N];
int f[N];

struct edge{
	int to, pre;
}e[N * 2];
int u[N];
int l = 0;
void ins(int a, int b){
	e[++l] = (edge){b, u[a]}, u[a] = l;
}
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define v e[i].to

int rt, sum, sz[N], s[N];
void getrt(int x, int f){
	sz[x] = 1, s[x] = 0;
	reg(i,x) if (v != f) getrt(v, x), sz[x] += sz[v], s[x] = max(s[x], sz[v]);
	s[x] = max(s[x], sum - sz[x]);
	if (s[x] < s[rt]) rt = x;
}
string st[N], q[N];
string build(int x, int f){
	st[x] = "(";
	reg(i,x) if (v != f) build(v, x);
	int ql = 0;
	reg(i,x) if (v != f) q[++ql] = st[v];
	sort(q + 1, q + ql + 1);
	rep(i,1,ql) st[x] += q[i];
	st[x] += ")";
	return st[x];
}

void work(int t){
	int n; scanf("%d",&n);
	l = 0; rep(i,1,n) u[i] = 0;

	rep(i,1,n) {
		int a; scanf("%d",&a);
		if (a) ins(i, a), ins(a, i);
	}

	s[rt = 0] = sum = n, getrt(1,0);
	int rt1 = 0;
	rep(i,1,n) if (s[i] == s[rt] && i != rt) rt1 = i;
	if (rt1) S[t] = min(build(rt, 0), build(rt1, 0)); else S[t] = build(rt, 0);
}
int main(){
	int m; scanf("%d",&m);
	rep(i,1,m) work(i);
	rep(i,1,m) f[i] = i;
	rep(i,1,m) if (f[i] == i) rep(j,i + 1,m) if (S[i] == S[j]) f[j] = i;
	rep(i,1,m) printf("%d\n",f[i]);
	return 0;
}