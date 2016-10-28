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
const int N = 560, M = 20000, inf = 1000000000;
struct edge{
	int to, pre, w, c;
}e[M * 4];
int l = 1, u[N];
#define v e[i].to
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define ew e[i].w
#define ec e[i].c
void ins(int a, int b, int w, int c){
	e[++l] = (edge){b, u[a], w, c}, u[a] = l;
}
void insert(int a, int b, int w, int c){
	ins(a, b, w, c), ins(b, a, 0, -c);
}
int d[N][N];
#define min(a,b) ((a) < (b) ? (a) : (b))

#define out(x) (x << 1)
#define in(x) (out(x) - 1)

int h[N], q[N], from[N], S, T;
bool inq[N];
bool spfa(){
	rep(i,S,T) h[i] = inf, inq[i] = false;
	int l = 0, r = 1; q[h[S] = 0] = S;
	while (l != r){
		int x = q[l++]; if (l == N) l = 0; inq[x] = false;
		reg(i,x) if (ew && h[v] > h[x] + ec){
			h[v] = h[x] + ec, from[v] = i;
			if (!inq[v]) { 
				inq[v] = true; q[r++] = v; if (r == N) r = 0;
			}
		}
	}
	return h[T] < inf;
}

long long cost = 0;
void mcf(){
	int f = inf;
	for(int i = from[T]; i; i = from[e[i ^ 1].to]) f = min(f, ew);
	for(int i = from[T]; i; i = from[e[i ^ 1].to]) ew -= f, e[i^1].w += f, cost += 1LL * f * ec;
}

int main(){
	int n, m, k; scanf("%d%d%d",&n,&m,&k);n++;
	S = 0, T = out(n) + 3;
	int s = out(n) + 1, t = out(n) + 2;

	insert(s, in(1), k, 0), insert(in(1), out(1), k, 0);
	rep(i,1,n) insert(out(i), t, k, 0);

	rep(i,2,n) insert(in(i), T, 1, 0), insert(S, out(i), 1, 0);
	insert(t, s, inf, 0);

	rep(i,1,n) {
		rep(j,1,n) d[i][j] = inf;
		d[i][i] = 0;
	}

	rep(i,1,m){
		int a, b, c; scanf("%d%d%d",&a,&b,&c);
		a++, b++;
		d[a][b] = d[b][a] = min(d[a][b], c);
	}

	rep(k,1,n)
		rep(i,1,n)
			rep(j,1,n)
				if (k <= i || k <= j) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

	rep(i,1,n) rep(j,i + 1,n)
		if (d[i][j] < inf) insert(out(i), in(j), k, d[i][j]);

	while (spfa()) mcf();
	printf("%lld\n",cost);
}