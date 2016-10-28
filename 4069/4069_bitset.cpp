#include <iostream>
#include <cstdio>
#include <algorithm>
#include <bitset>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
typedef long long LL;
const int N = 2000 + 10;
int n, l, r, a[N];
LL ans;
bitset<N> f[N];
LL s[N];
void work1(){
	ans = (1ull << 61) - 1;
	dep(t,60,0){
		ans -= (1LL << t);
		rep(i,0,n) f[i] = 0;
		f[0][0] = 1;
		rep(i,1,n) rep(j,0,i - 1) if (((s[i] - s[j]) | ans) == ans){
			f[i] |= f[j] << 1;
			f[i][r + 1] = 0;
		}
		bool flag = 0;
		rep(i,l,r) if (f[n][i]) flag = 1;
		if (!flag) ans += (1LL << t);
	}
	printf("%lld\n",ans);
}
void work2(){}
int main(){
	scanf("%d%d%d",&n,&l,&r);
	s[0] = 0;
	rep(i,1,n) scanf("%d",&a[i]), s[i] = s[i - 1] + a[i];
	work1();
	return 0;
}