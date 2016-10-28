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
const int N = 200010;
int fa[N], dep[N], sz[N], mx[N], mn[N];

struct edge{
	int to, pre;
}e[N * 2];
int u[N];
int l = 0;
void ins(int a, int b){
	e[++l] = (edge){b, u[a]}, u[a] = l;
}
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define v e[i].to

bool leaf[N];

void dfs(int x){
	if (leaf[x]) mx[x] = mn[x] = 1;
	else if (dep[x] & 1){//max
		int mx1 = sz[x];
		reg(i,x) dfs(v);
		reg(i,x) mx1 = min(mx1, sz[v] - mx[v]);
		mx[x] = sz[x] - mx1;

		int mn1 = 0;
		reg(i,x) mn1 += sz[v] - mn[v];
		mn[x] = sz[x] - mn1;
	}else{//min
		int mn1 = sz[x];
		reg(i,x) dfs(v);
		reg(i,x) mn1 = min(mn1, mn[v]);
		mn[x] = mn1;

		int mx1 = 0;
		reg(i,x) mx1 += mx[v] - 1;
		mx[x] = mx1 + 1;
	}
}

int main(){
	int n; scanf("%d",&n);
	rep(i,1,n) leaf[i] = true;
	rep(i,1,n - 1){
		int a, b; scanf("%d%d",&a,&b);
		fa[b] = a; ins(a, b);
		leaf[a] = false;
	}
	dep[1] = 1;
	rep(i,2,n) dep[i] = dep[fa[i]] + 1;

	rep(i,1,n) sz[i] = leaf[i];
	dep(i,n,1) sz[fa[i]] += sz[i];

	dfs(1);
	printf("%d %d\n",mx[1], mn[1]);
}