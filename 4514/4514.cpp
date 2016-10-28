#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
typedef long long LL;
const int N = 1010, M = 160010;

struct edge{ int to, pre, w; LL c; } e[M * 2]; int u[N], l = 1;//l==1!
void ins(int a, int b, int w, LL c) { e[++l] = (edge){b, u[a], w, c}, u[a] = l; }
void insert(int a, int b, int w, LL c) { ins(a, b, w, c), ins(b, a, 0, -c); }
#define v e[i].to
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define ec e[i].c
#define ew e[i].w
bool inq[N];
LL h[N];
const LL INF = 1000000000000000000LL;
int S, T, from[N], q[N];
bool spfa(){
	rep(i,S,T) h[i] = INF, inq[i] = false;
	int l = 0, r = 1; q[h[S] = 0] = S;
	while (l < r){
		int x = q[l++]; inq[x] = false;
		reg(i,x) if ( ew && (h[v] > h[x] + ec) )
			{ h[v] = h[x] + ec, from[v] = i; if (!inq[v]) q[r++] = v, inq[v] = true; }
	}
	return h[T] < INF;
}
int ans = 0;
LL cost = 0;
void mcf(int f){
	LL c = 0;
	for(int i = T; i != S; i = e[from[i] ^ 1].to) f = min(f, e[from[i]].w), c += e[from[i]].c;
	for(int i = T; i != S; i = e[from[i] ^ 1].to) e[from[i]].w -= f, e[from[i] ^ 1].w += f;
	ans += f; cost += c * f;
}

int a[N], b[N]; LL c[N];
int f[N], r[N];
void find(int x) { 
	if (x == f[x]) return;
	find(f[x]); r[x] ^= r[f[x]]; f[x] = f[f[x]];
}

int pw(int a, int b, int c) { int w = 1; for(;b;b >>= 1, a = 1LL * a * a % c) if (b & 1) w = 1LL * w * a % c; return w;}

bool check(int a, int n){
	if (n == a) return true; else if (n <= 1) return false;
	int k = n - 1, t = 0; while (!(k & 1)) k >>= 1, t++;
	int w = pw(a, k, n); if (w == 1) return true;
	rep(i,1,t) { if (w == n - 1) return true; w = 1LL * w * w % n; }
	return false;
}

bool is_prim(int n){
	return check(2, n) && check(3, n) && check(5, n) && check(7, n) && check(11, n) && check(13, n) && check(17, n) && check(19, n) && check(23, n); 
}

const int inf = 1000000000;

bool mp[N][N];
LL sum = 0;
int main(){
	int n; scanf("%d",&n);
	rep(i,1,n) scanf("%d",&a[i]);
	rep(i,1,n) scanf("%d",&b[i]);
	rep(i,1,n) scanf("%lld",&c[i]);
	rep(i,1,n) f[i] = i, r[i] = 0;
	rep(i,1,n) rep(j,1,n) if (a[i] > a[j]) {
		if ( a[i] % a[j] == 0 && is_prim(a[i] / a[j]) ){
			mp[i][j] = 1; find(i); find(j);
			if (f[i] != f[j]) {
				int fi = f[i], fj = f[j];
				r[fi] = r[i] ^ r[j] ^ 1, f[fi] = fj;//否则i==f[i]的时候可能炸锅 
			}
		}
	}
	S = 0, T = n + 1;
	rep(i,1,n) {
		find(i);
		if (r[i] == 1) insert(S, i, b[i], 0); else insert(i, T, b[i], 0);
	}
	rep(i,1,n) rep(j,1,n) if (mp[i][j]){
		int a = i, b = j;
		if (r[b] == 1) swap(a, b);
		insert(a, b, inf, -c[i] * c[j]);
	}

	ans = 0;
	while (spfa()){
		if (h[T] + cost > 0) break;
		if (h[T] <= 0) mcf(inf); else mcf(min((-cost) / h[T], (LL)inf));
	}
	printf("%d\n",ans);
	return 0;
}