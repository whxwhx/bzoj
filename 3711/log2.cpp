#include <iostream>
#include <queue>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
const int N = 1001000;

const int mod = 1000000007;
typedef pair<int, int> sta;
#define F first
#define W second
#define mp(a,b) make_pair(a,b)

priority_queue<sta> q;

int D[N], n, DL[N], d[N], c[N]; 
void calc_D(){
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

sta f[N * 4], mx[N * 4];
sta operator + (const sta &a, const sta &b){
	sta c;
	if (a.F > b.F) c = a;
	else if (a.F < b.F) c = b;
	else c.F = a.F, c.W = (a.W + b.W) % mod;
	return c;
}
sta operator * (const sta &a, const sta &b){
	if (a.F > b.F) return a; else return b;
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
		f[x] = f[lc] + f[rc];
		mx[x] = mx[lc] * mx[rc];
	}
}

sta fmx(int x, int l, int r, int a, int b){
	if (a <= l && r <= b) return mx[x];
	else {
		sta ans = mp(-1, 0);
		if (a <= mid) ans = ans * fmx(lcq, a, b);
		if (b >  mid) ans = ans * fmx(rcq, a, b);
		return ans;
	}
}

sta tag[N * 4], F[N];

void push(int x, int l, int r){
	f[x] = f[x] + tag[x];
	if (l < r){
		tag[lc] = tag[lc] + tag[x];
		tag[rc] = tag[rc] + tag[x];
	}
	tag[x] = mp(0, 0);
}

void modi(int x, int l, int r, int a, int b, sta d){
	if (a <= l && r <= b){
		tag[x] = tag[x] + d;
		push(x, l, r);
	}else {
		push(x, l, r);
		if (a <= mid) modi(lcq, a, b, d); else push(lcq);
 		if (b >  mid) modi(rcq, a, b, d); else push(rcq);
 		f[x] = f[lc] + f[rc];
	}
}

sta qry(int x, int l, int r, int a, int b){
	push(x, l, r);
	if (a <= l && r <= b) return f[x];
	else {
		sta c = mp(0,0);
		if (a <= mid) c = c + qry(lcq, a, b);
		if (b >  mid) c = c + qry(rcq, a, b);
		return c;
	}
}

void solve(int l, int r){
	if (l == r) {
		if (D[l] == 0) F[l] = F[l] + mp(1,1);
		modi(1,1,n,l,l,F[l]);
		F[l] = qry(1,1,n,l,l);
		return;
	}
	int k = fmx(1, 1, n, l + 1, r).second;
	solve(l, k - 1);
	if (k - l < r - k + 1){
		rep(i,l,k - 1){
			int L = max(i + c[k], k), R = min(DL[i], r);
			if (L <= R) {
				sta f = F[i];
				if (f.F) f.F++;
				modi(1, 1, n, L, R, f);
			}
		}
	}else {
		rep(i,k,r){
			int L = max(D[i], l), R = min(i - c[k], k - 1);
			if (L <= R){
				sta f = qry(1, 1, n, L, R);
				if (f.F) f.F++;
				F[i] = F[i] + f;
			}
		}
	}
	solve(k, r);
}

int main(){
	scanf("%d",&n);
	rep(i,1,n) scanf("%d%d",&c[i],&d[i]);
	calc_D();
	int c1 = 0, d1 = n;
	rep(i,1,n){
		c1 = max(c1, c[i]), d1 = min(d1, d[i]);
		if (i >= c1 && i <= d1) D[i] = 0;
	}
	build(1, 1, n);
	//cout <<D[6]<<endl;
	solve(1, n);
	rep(i,1,n){
		sta g = qry(1,1,n,i,i);
		cout <<i<<' '<<g.F<<' '<<g.W<<endl;
	}
	sta f = F[n];
	if (f.W < 0) f.W += mod;
	if (f.F == 0) printf("NIE\n");//不能用w判因为可能方案数是mod的倍数
	else printf("%d %d\n",f.F,f.W);
	return 0;
}