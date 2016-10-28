#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int n = 100000, N = 100000 + 10, M = 19961993;
typedef long long LL;
LL inv[70], p[70];
LL S[N * 4], P[N * 4];
LL pow(LL a, int b){
	LL w = 1;
	for(;b;b >>= 1, a = a * a % M) if (b & 1) w = w * a % M;
	return w;
}
int l = 0;
#define lc (x << 1)
#define rc (lc + 1)
#define mid ((l + r) >> 1)
#define lcq lc, l, mid
#define rcq rc, mid + 1, r
void build(int x, int l, int r){
	if (l == r) S[x] = 3, P[x] = 1 << 1;else{
		build(lcq), build(rcq);
		S[x] = S[lc] * S[rc] % M;
		P[x] = P[lc] | P[rc];
	}
}
typedef pair<LL, LL> node;
#define mp(a,b) make_pair(a,b)
node qry(int x, int l, int r, int a, int b){
	if (a <= l && r <= b) return mp(S[x], P[x]);
	node ans = mp(1, 0);
	if (a <= mid){
		node t = qry(lcq, a, b);
		ans.first = ans.first * t.first % M;
		ans.second |= t.second;
	}
	if (b >  mid){
		node t = qry(rcq, a, b);
		ans.first = ans.first * t.first % M;
		ans.second |= t.second;
	}
	return ans;
}
void modi(int x, int l, int r, int a, LL s, LL p){
	if (l == r) S[x] = s, P[x] = p; else{
		if (a <= mid) modi(lcq,a,s,p); else modi(rcq,a,s,p);
		S[x] = S[lc] * S[rc] % M;
		P[x] = P[lc] | P[rc];
	}
}
void init(){
	rep(i,2,281){
		bool flag = true;
		rep(j,2,i - 1) if (i % j == 0) {flag = false;break;}
		if (flag) p[l++] = i;
	}
	rep(i,0,l - 1) inv[i] = pow(p[i], M - 2);
	build(1,1,n);
}
int main(){
	init();
	int Q;scanf("%d",&Q);
	rep(i,1,Q){
		int a, b, c; scanf("%d%d%d",&a,&b,&c);
		if (a == 0){
			node ans = qry(1, 1, n, b, c);
			LL a1 = ans.first, a2 = ans.second;
			rep(j,0,l - 1) if ((a2 >> j) & 1) a1 = a1 * (p[j] - 1) % M * inv[j] % M; //cout <<'-'<<p[j]<<endl;
			printf("%lld\n", a1);
		}else{
			LL p1 = 0;
			rep(j,0,l - 1) if (c % p[j] == 0) p1 |= 1LL << j; // 1LL !!! j <= 60 !
			modi(1,1,n,b,c,p1);
		}
	}
}