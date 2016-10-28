#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 50010, M = 1000010, mod = 1000000 + 777;

bool A[M]; int p[M], q[M], l = 0;
void init(){
	rep(i,2,M - 10) {
		if (!A[i]) p[++l] = i, q[i] = i;
		rep(j,1,l) {
			int k = i * p[j]; if (k > M - 10) break;
			A[k] = true; q[k] = p[j];
			if (i % p[j] == 0) break;
		}
	}
}

int n;
int a[N];
inline int pw(int a, int b){ int w = 1; for(;b;b >>= 1, a = 1LL * a * a % mod) if (b & 1) w = 1LL * w * a % mod; return w; }
namespace seg{
	int s[N], inv[N];
	struct node{ int lc, rc, s; node(){ lc = rc = 0, s = 1; } }T[N * 7 * 21]; int tl = 0;

	#define mid ((l + r) >> 1)
	#define u T[k]
	#define ulc T[k].lc
	#define urc T[k].rc
	int add(int x, int l, int r, int a, int d){
		int k = ++tl; u = T[x]; u.s = 1LL * u.s * d % mod; 
		if (l < r) {
			if (a <= mid) ulc = add(ulc, l, mid, a, d); 
			else urc = add(urc, mid + 1, r, a, d);
		}
		return k;
	}

	int pre[M], rt[N];
 
	vector< pair<int, int> > g[N];
	typedef vector< pair<int, int> >::iterator vit;
	#define mp(a,b) make_pair(a,b)
	#define pb(a) push_back(a)

	#define xs T[x].s
	#define lc T[x].lc
	#define rc T[x].rc
	int qry(int x, int l, int r, int a, int b){
		if (a <= l && r <= b) return xs;
		else return (a <= mid ? qry(lc, l, mid, a, b) : 1) * 1LL * (b > mid ? qry(rc, mid + 1, r, a, b) : 1) % mod;
	}

	void init(){
		s[0] = 1; rep(i,1,n) s[i] = s[i - 1] * 1LL * a[i] % mod;
		rep(i,0,n) inv[i] = pw(s[i], mod - 2);
		rep(i,1,n){
			int t = a[i];
			while (t != 1){
				int k = q[t]; while (t % k == 0) t /= k;
				int tk = (k - 1) * 1LL * pw(k, mod - 2) % mod;
				g[pre[k]].pb(mp(i, tk)), pre[k] = i;
			}
		}

		rt[0] = 0;
		rep(i,0,n){
			if (i) rt[i] = rt[i - 1];
			for(vit it = g[i].begin(); it != g[i].end(); it++)
				rt[i] = add(rt[i], 1, n, it->first, it->second);
		}
	}

}

int main(){
	init();int q;scanf("%d%d",&n,&q); 
	rep(i,1,n) scanf("%d",&a[i]); 
	seg::init(); int la = 0;
	rep(i,1,q) {
		int l, r; scanf("%d%d",&l,&r); l ^= la, r ^= la;
		la = seg::s[r] * 1LL * seg::inv[l - 1] % mod * 1LL * seg::qry(seg::rt[l - 1], 1, n, l, r) % mod;
		if (la < 0) la += mod; printf("%d\n",la);
	}
	return 0;
}