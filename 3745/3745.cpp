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
const int N = 500010, mod = 1000000000;

int S[N];
int a[N];

#define lc (x << 1)
#define rc (lc + 1)
#define mid ((l + r) >> 1)
#define lcq lc, l, mid
#define rcq rc, mid+1, r
namespace seg{
	int a, b, c, f, d[2][N * 4], s[N * 4], t[2][N * 4], m[2][N * 4], mnx[N * 4];
	void push(int x, int l, int r){
		rep(i,0,1) {
			if (t[i][x]){
				d[i][x] = 1LL * t[i][x] * (S[r] - S[l - 1]) % mod;
				s[x] = 1LL * d[i ^ 1][x] * t[i][x] % mod;

				m[i][x] = 1LL * t[i][x] * (r - l + 1) % mod;
				mnx[x] = 1LL * m[i ^ 1][x] * t[i][x] % mod;
				
				if (l < r) t[i][lc] = t[i][x], t[i][rc] = t[i][x], t[i][x] = 0; 
			}
		}
	}

	void upd(int x){
		rep(i,0,1) 	d[i][x] = (d[i][lc] + d[i][rc]) % mod, 
					m[i][x] = (m[i][lc] + m[i][rc]) % mod,

		mnx[x] = (mnx[lc] + mnx[rc]) % mod;
		s[x] = (s[lc] + s[rc]) % mod;
	}

	void modi(int x, int l, int r){
		push(x, l, r);
		if (a <= l && r <= b) { t[f][x] = c; push(x, l, r); } else {
			if (a <= mid) modi(lcq); else push(lcq);
			if (b >  mid) modi(rcq); else push(rcq);
			upd(x);
		}
	}
}

struct stack{
	int a[N], id[N], top;
	stack() { a[0] = id[0] = top = 0; }
	int push(int v, int x){
		while (top && a[top] <= v) top--;
		top++; a[top] = v, id[top] = x; return id[top - 1];
	}
}s1, s2;

int main(){
	int n; scanf("%d",&n); rep(i,1,n) scanf("%d",&a[i]); S[0] = 0; rep(i,1,n) S[i] = (S[i - 1] + i) % mod;
	int ans = 0;
	rep(i,1,n){
		int mnl = s1.push(a[i], i) + 1; seg::a = mnl, seg::b = i, seg::c = a[i], seg::f = 0; seg::modi(1, 1, n);
		int mxl = s2.push(-a[i], i) + 1; seg::a = mxl, seg::b = i, seg::c = a[i], seg::f = 1; seg::modi(1, 1, n);
		seg::push(1, 1, n); ans -= seg::s[1], ans %= mod, ans += seg::mnx[1] * 1LL * (i + 1) % mod;
	}
	if (ans < 0) ans += mod;
	printf("%d\n",ans);
	return 0;
}