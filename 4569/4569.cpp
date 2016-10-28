#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a, _b = b; i <= _b; i++)
using namespace std;
const int N = 100010, mod = 1000000000 + 7;
#define id(a,b) ((a - 1) * 17 + b + 1)
int f[N * 18];
int find(int x){ return f[x] == x ? x : f[x] = find(f[x]); }

void merge(int a, int b, int j){
	int fa = find(id(a,j)), fb = find(id(b,j));
	if (fa != fb) f[fa] = fb; else return;
	if (j) merge(a, b, j - 1), merge(a + (1 << (j-1)), b + (1 << (j-1)), j - 1); 
}

int main(){
	int n, m; scanf("%d%d",&n,&m);
	rep(i,1,n) rep(j,0,16) f[id(i,j)] = id(i,j);
	rep(i,1,m){
		int l1, r1, l2, r2; scanf("%d%d%d%d",&l1,&r1,&l2,&r2); int len = r1 - l1 + 1;
		rep(j,0,16) if (len >> j & 1) merge(l1, l2, j), l1 += 1 << j, l2 += 1 << j;
	}
	int cnt = 0, ans = 9;
	rep(i,1,n) if (f[id(i,0)] == id(i,0)) cnt++;
	rep(i,2,cnt) ans = ans * 10LL % mod;
	printf("%d\n",ans);
	return 0;
}