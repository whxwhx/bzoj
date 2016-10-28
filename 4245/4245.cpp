#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
typedef long long LL;
using namespace std;
const int N = 500000 + 10;
LL s[N], ans = 0;
bool b[N], c[N];
int main(){
	int n, m; scanf("%d%d",&n,&m);
	s[0] = 0;
	rep(i,1,n) scanf("%lld",&s[i]), s[i] ^= s[i - 1];
	rep(i,1,n) b[i] = 1;
	ans = (1ull << 63) - 1;
	dep(i,62,0){
		LL t = 1LL << i;
		rep(j,1,n) c[j] = b[j] && ((s[j] & t) == 0);
		int tmp = 0;
		rep(j,1,n) if (c[j]) tmp++;
		if (tmp >= m && c[n]){
			ans -= t;
			rep(j,1,n) b[j] = c[j]; 
		}
	}
	printf("%lld\n",ans);
}