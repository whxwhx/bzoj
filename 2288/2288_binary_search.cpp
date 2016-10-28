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
const int inf = 1000000000, N = 100100;
int n, k, a[N], s[N], f[N], g[N];
int check(int K){
	int mx = 0, mxa = 0;
	rep(i,1,n){
		if (mx + s[i] - K > f[i - 1] || (mx + s[i] - K == f[i - 1] && mxa + 1 < g[i - 1])) {
			f[i] = mx + s[i] - K;
			g[i] = mxa + 1;
			if (f[i] - s[i] > mx) mx = f[i] - s[i], mxa = g[i];
		} else {
			f[i] = f[i - 1]; g[i] = g[i - 1];
			if (f[i] - s[i] > mx || (f[i] - s[i] == mx && g[i] < mxa)) mx = f[i] - s[i], mxa = g[i];
		}
	}
	int tmp = inf; mx = 0;
	rep(i,1,n) mx = max(mx, f[i]);//, cout <<f[i]<<' '; cout <<endl;
	rep(i,1,n) if (mx == f[i]) tmp = min(tmp, g[i]);
	//cout <<K<<' '<<mx<<' '<<tmp<<endl;
	return tmp;
}
int main(){
	scanf("%d%d",&n,&k); rep(i,1,n) scanf("%d",&a[i]);
	rep(i,1,n) s[i] = s[i - 1] + a[i];
	int l = -1, r = inf; 
	while (l + 1 < r){ int mid = (l + r) >> 1; if (check(mid) > k) l = mid; else r = mid; }
	check(r); int ans = 0; rep(i,1,n) ans = max(ans, f[i]); ans += r * k;
	printf("%d\n",ans);
	return 0;
}