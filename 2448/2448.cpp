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
const int N = 2005, inf = 2000000000;
int a[N], f[N][N], n, tl = 1, L[N * 2], R[N * 2];

#define lc L[x]
#define rc R[x]
#define mid ((l + r) >> 1)
#define lcq lc, l, mid
#define rcq rc, mid + 1, r
struct seg{
	int mn[N * 2], a, b;
	void modi(int x, int l, int r){
		if (l == r) mn[x] = b; else 
		(a <= mid ? modi(lcq) : modi(rcq)), mn[x] = min(mn[lc], mn[rc]);
	}
	void modi(int A, int B){ a = A, b = B; modi(1, 1, n); }
	int qry(int x, int l, int r){
		if (a <= l && r <= b) return mn[x]; else 
		return min( (a <= mid ? qry(lcq) : inf), (b > mid ? qry(rcq) : inf) );
	}
	int qry(int A, int B){ a = A, b = B; return a > b ? inf : qry(1, 1, n); }
}T1[N], T2[N];

void build(int x, int l, int r){
	if (l == r) return;
	else { L[x] = ++tl; build(lcq); R[x] = ++tl; build(rcq); }
}

int main(){
	scanf("%d",&n); rep(i,1,n) scanf("%d",&a[i]);
	build(1, 1, n);
	rep(i,1,n) T1[i].modi(i, a[i]), T2[i].modi(i, a[i]);
	dep(i,n,1){
		int t = i;
		rep(j,i,n){
			while (t <= j && f[i][t - 1] < f[t + 1][j]) t++;
			f[i][j] = min(T1[i].qry(t,j), T2[j].qry(i, t - 1));
			if (j < n) T1[i].modi(j + 1, f[i][j] + a[j + 1]);
			if (i > 1) T2[j].modi(i - 1, f[i][j] + a[i - 1]);
		}
	}
	printf("%d\n",f[1][n]);
	return 0;
}