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
const int N = 1010, mod = 1000000007;
struct edge{
	int a, b, c;
}e[N];
bool operator < (const edge &a, const edge &b){
	return a.c < b.c;
}
int a[N], fa[N], val[N], f[N];
int find(int x){
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main(){
	int n, m; scanf("%d%d",&n,&m);
	rep(i,1,n - 1){
		int a, b; scanf("%d%d",&a,&b);
		e[i] = (edge){a, b, 0};
	}
	rep(i,1,n) scanf("%d",&a[i]);
	rep(i,1,n - 1) e[i].c = max(a[e[i].a], a[e[i].b]) + 1;
	sort(e + 1, e + n);
	rep(i,1,n) fa[i] = i, val[i] = a[i];
	rep(i,1,n - 1){
		int x = find(e[i].a), y = find(e[i].b);
		if (x == y) continue;
		f[x] += e[i].c - val[x];
		f[y] += e[i].c - val[y];
		fa[y] = x, val[x] = e[i].c, f[x] = 1LL * f[x] * f[y] % mod;
	}
	int x = find(1);
	f[x] += m + 1 - val[x], f[x] %= mod;
	printf("%d\n",f[x]);
}