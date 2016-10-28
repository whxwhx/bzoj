#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int inf = 5000000;
int a[51], g[100010], f[100010];
int main(){
	int n; scanf("%d",&n);
	int t = 0;
	rep(i,1,n) scanf("%d",&a[i]), t = max(t, a[i]);
	rep(i,1,t) rep(j,1,n) g[i] += a[j] / i;
	rep(i,1,t) f[i] = inf;
	f[1] = g[1];
	rep(i,1,t)
		rep(j,2,t / i)
			f[i * j] = min(f[i * j], f[i] - g[i * j] * (j - 1));
	int ans = inf;
	rep(i,1,t) ans = min(ans, f[i]);
	printf("%d\n",ans);
}