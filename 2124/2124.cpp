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

const int N = 10100;
int mod[2] = {532145707, 732145717};
int n, a[N];
#define mid ((l + r) >> 1)
#define lc (x << 1)
#define rc (lc + 1)
#define lcq lc, l, mid
#define rcq rc, mid + 1, r
struct node{
	int s[3], l;
};
int pw[N][3];
node operator + (const node &a, const node &b){
	node c = {{0,0,0},0};
	c.l = a.l + b.l;
	rep(i,0,1)
		c.s[i] = (1LL * a.s[i] * pw[b.l][i] + b.s[i]) % mod[i];
	return c;
}
bool operator != (const node &a, const node &b){
	return a.s[0] != b.s[0] || a.s[1] != b.s[1] || a.s[2] != b.s[2] || a.l != b.l;
}
struct seg{
	int s[N * 4][3];
	void clear(){
		memset(s, 0, sizeof(s));
	}
	void add(int x, int l, int r, int a){
		if (l == r) {
			rep(i,0,1) s[x][i] = 1;
		} else {
			if (a <= mid) add(lcq, a);
			else add(rcq, a);
			rep(i,0,1) s[x][i] = (1LL * s[lc][i] * pw[r - mid][i] + s[rc][i]) % mod[i];
		}
	}
	node qry(int x, int l, int r, int a, int b){
		if (a <= l && r <= b) return (node){{s[x][0], s[x][1], s[x][2]}, r - l + 1};
		else {
			node ans = {{0,0,0},0};
			if (a <= mid) ans = qry(lcq, a, b);
			if (b  > mid) ans = ans + qry(rcq, a, b);
			return ans;
		}
	}
}b1, b2;
void work(){
	scanf("%d",&n);
	rep(i,1,n) scanf("%d",&a[i]);
	b1.clear(), b2.clear();
	rep(i,1,n){
		 int l = min(a[i] - 1, n - a[i]);
		 if (b1.qry(1, 1, n, a[i] - l, a[i] + l) != b2.qry(1, 1, n, n - (a[i] + l) + 1, n - (a[i] - l) + 1)){
		 	printf("Y\n");return;
		 }
		 b1.add(1, 1, n, a[i]), b2.add(1, 1, n, n - a[i] + 1);
	}
	printf("N\n");
}

int main(){
	rep(j,0,1) pw[0][j] = 1;
	rep(i,1,N - 1) rep(j,0,1) pw[i][j] = (pw[i - 1][j] << 1) % mod[j];
	int T; scanf("%d",&T);
	while (T--) work();
}