#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
typedef long long LL;
const int N = 100000 + 10, M = 950;
int a[N], t[N], pos[N], n, cl;
LL b[N], c[N];
inline int find(LL x){
	int l = 1, r = cl + 1;
	while (l + 1 < r){
		int mid = (l + r) >> 1;
		if (c[mid] <= x) l = mid; else r = mid;
	}
	return l;
}

struct qry{
	int a, b, c, num;
}Q[N];

int ans[N];

inline bool cmp(const qry &a, const qry &b){
	return (a.c < b.c) || (a.c == b.c && a.b < b.b);
}

int bel[N], sum[M], s[N], block_cnt, L[M], R[M];
inline void add(int x){
	sum[bel[x]]++;
	s[x]++;
}
inline void del(int x){
	sum[bel[x]]--;
	s[x]--;
}

#define dep(i,a,b) for(int i=a;i>=b;i--)
inline int qry(){
	dep(i,block_cnt,1) if (sum[i])
		dep(j,R[i],L[i]) if (s[j]) return j;
}

int cnt[N];
inline void op(int a, int x){
	if (cnt[a] > 0) del(b[pos[a] + cnt[a]]);
	cnt[a]+=x;
	if (cnt[a] > 0) add(b[pos[a] + cnt[a]]);
}
inline int read(){
	char c = getchar();
	int x = 0, f = 1;
	while (c < '0' || c > '9') {if (c == '-') f = -1; c = getchar();}
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return x * f;
}
int main(){
	int q; scanf("%d%d",&n,&q);
	rep(i,1,n) a[i] = read(), b[i] = a[i];
	sort(b + 1, b + n + 1);
	rep(i,1,n) if (b[i] == b[i - 1]) c[i] = c[i - 1] + b[i]; else c[i] = b[i], t[i] = 1;
	rep(i,1,n) b[i] = c[i];

	sort(c + 1, c + n + 1);
	cl = unique(c + 1, c + n + 1) - c - 1;
	rep(i,1,n) a[i] = find(a[i]);

	rep(i,1,n) {
		b[i] = find(b[i]);
		if (t[i]) pos[b[i]] = i - 1;
	}

	int m = sqrt(cl) + 1;
	rep(i,1,cl) {
		bel[i] = (i - 1) / m + 1;
		if (i % m == 1) L[bel[i]] = i;
		if (i % m == 0) R[bel[i]] = i;
	}
	R[bel[cl]] = cl;
	block_cnt = bel[cl];

	m = sqrt(q) + 1;
	rep(i,1,q) scanf("%d%d",&Q[i].a, &Q[i].b), Q[i].c = Q[i].a / m, Q[i].num = i;
	sort(Q + 1, Q + q + 1, cmp);

	int l = 1, r = 0;
	rep(i,1,q){
		int L = Q[i].a, R = Q[i].b;
		while (r < R) r++, op(a[r], 1);
		while (r > R) op(a[r], -1), r--;
		while (l < L) op(a[l], -1), l++;
		while (l > L) l--, op(a[l], 1);
		ans[Q[i].num] = qry();
	}

	rep(i,1,q) printf("%lld\n",c[ans[i]]);
	return 0;
}