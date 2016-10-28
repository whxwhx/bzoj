#include <iostream>
#include <cstdio>
#include <map>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 52;
typedef long long LL;
LL g[N];
map<LL, LL> sum, G;
LL dfs(LL x){
	if (x == 0) return 1;
	if (sum.find(x) != sum.end()) return sum[x];
	LL tmp = (-x) & x;
	return sum[x] = dfs(x ^ tmp) + dfs(x & G[tmp]);
}
int main(){
	sum.clear();
	int n; scanf("%d",&n);
	rep(i,1,n) {
		g[i] = 0;
		rep(j,1,n) {
			char c = getchar();
			while (c != '0' && c != '1') c = getchar();
			g[i] |= ((LL)c - (LL)'0') << (j - 1);
		}
		G[1LL << (i - 1)] = g[i];
	}
	printf("%lld\n",dfs((1LL << n) - 1));
}