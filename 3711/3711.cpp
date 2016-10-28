#include <iostream>
#include <queue>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
const int N = 1000010;

const int mod = 1000000007;
typedef pair<int, int> sta;
#define F first
#define W second
#define mp(a,b) make_pair(a,b)

priority_queue<sta> q;

inline int read(){
	int x = 0, f = 1;char c = getchar();
	while (c < '0' || c > '9') {if (c == '-') f = -1;c = getchar();}
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return x * f;
}

int D[N], n, DL[N], d[N], c[N]; 
inline void calc_D(){
	int l = 1;
	rep(i,1,n){
		q.push(mp(-d[i], i));
		while (!q.empty() && (-q.top().first) < i - l){
			if (q.top().second <= l) q.pop();
			else l++;
		}
		D[i] = l;
	}
	rep(i,2,n)
		rep(j, D[i - 1], D[i] - 1) DL[j] = i - 1;
	rep(j,D[n],n) DL[j] = n;
}

sta f[N * 4], mx[N * 4], tag[N * 4];
sta merge(const sta &a, const sta &b){
	sta c;
	if (a.F > b.F) c = a;
	else if (a.F < b.F) c = b;
	else c.F = a.F, c.W = (a.W + b.W) % mod;
	return c;
}
inline sta operator * (const sta &a, const sta &b){
	if (a.F > b.F) return a; 
	else if (a.F < b.F) return b;
	else return b;
}

#define mid ((l + r) >> 1)
#define lc (x << 1)
#define rc (lc + 1)
#define lcq lc, l, mid
#define rcq rc, mid + 1, r

void build(int x, int l, int r){
	if (l == r){
		f[x] = mp(0, 0);
		mx[x] = mp(c[l], l);
	}else {
		build(lcq), build(rcq);
		f[x] = merge(f[lc], f[rc]);
		mx[x] = mx[lc] * mx[rc];
	}
}

int a, b;

sta fmx(int x, int l, int r){
	if (a <= l && r <= b) return mx[x];
	else {
		sta ans = mp(-1, 0);
		if (a <= mid) ans = ans * fmx(lcq);
		if (b >  mid) ans = ans * fmx(rcq);
		return ans;
	}
}

sta fmx(int a1, int b1){
	a = a1, b = b1;
	return fmx(1, 1, n);
}

sta F[N];

inline void push(int x, int l, int r){
	f[x] = merge(f[x], tag[x]);
	if (l < r){
		tag[lc] = merge(tag[lc], tag[x]);
		tag[rc] = merge(tag[rc], tag[x]);
	}
	tag[x] = mp(0, 0);
}

sta delta;

void modi(int x, int l, int r){
	if (a <= l && r <= b){
		tag[x] = merge(tag[x], delta);
		push(x, l, r);
	}else {
		push(x, l, r);
		if (a <= mid) modi(lcq); else push(lcq);
 		if (b >  mid) modi(rcq); else push(rcq);
 		f[x] = merge(f[lc], f[rc]);
	}
}

void modi(int a1, int b1, sta d){
	a = a1, b = b1, delta = d;
	modi(1, 1, n);
}

sta qry(int x, int l, int r){
	if (a > b) return mp(0,0);
	push(x, l, r);
	if (a <= l && r <= b) return f[x];
	else {
		sta c = mp(0,0);
		if (a <= mid) c = merge(c, qry(lcq));
		if (b >  mid) c = merge(c, qry(rcq));
		return c;
	}
}

sta qry(int a1, int b1){
	a = a1, b = b1;
	return qry(1, 1, n);
}

void solve(int l, int r){
	if (l == r) {
		if (D[l] == 0) F[l] = merge(F[l], mp(1,1));
		modi(l,l,F[l]);
		F[l] = qry(l,l);
		return;
	}
	int k = fmx(l + 1, r).second;
	solve(l, k - 1);
	
	int l1 = max(k, l + c[k]), r1 = min(r, k - 1 + c[k]);
	
	sta f = mp(0, 0);
	if (l <= l1 - c[k] - 1) f = qry(l, l1 - c[k] - 1); 
	if (f.F) f.F++;

	int L = l;
	rep(i,l1,r1){
		if (D[i] > L){
			L = D[i]; if (L >= k) break;
			f = qry(L, i - c[k]);
			if (f.F) f.F++;
		} else if (i - c[k] >= L && F[i - c[k]].F) f = merge(f, mp(F[i - c[k]].F + 1, F[i - c[k]].W));
		F[i] = merge(F[i], f);
	}

	int t = max(DL[l] + 1, r1 + 1);
	//r1 + 1 -- t-1
	L = r1 + 1; int R = min(t - 1, r);
	if (L <= R){
		f = qry(l, k - 1);
		if (f.F) f.F++;
		modi(L, R, f);
	}
	
	L = -1;
	rep(i,t,r){
		if (D[i] >= k) break;
		if (L < D[i]) {
			L = D[i], f = qry(D[i], k - 1);
			if (f.F) f.F++;
		}
		F[i] = merge(F[i], f);
	}
	/**/
	
	solve(k, r);
}

int main(){
	scanf("%d",&n);
	rep(i,1,n) c[i] = read(), d[i] = read();
	calc_D();
	int c1 = 0, d1 = n;
	rep(i,1,n){
		c1 = max(c1, c[i]), d1 = min(d1, d[i]);
		if (i >= c1 && i <= d1) D[i] = 0;
	}
	build(1, 1, n);
	//cout <<D[6]<<endl;
	solve(1, n);
	
/*	rep(i,1,n){
		sta g = F[i];
		cout <<i<<' '<<g.F<<' '<<g.W<<endl;
	}*/

	sta f = F[n];
	if (f.W < 0) f.W += mod;
	if (f.F == 0) printf("NIE\n");//不能用w判因为可能方案数是mod的倍数
	else printf("%d %d\n",f.F,f.W);
	return 0;
}