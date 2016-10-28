#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
typedef long long LL;
const int N = 2000 + 10;
int n, l, r, a[N], f[N][N], ans;
LL s[N];
void work1(){
	ans = 0x7fffffff;
	dep(t,30,0){
		ans ^= (1 << t);
		rep(i,0,n) rep(j,0,r) f[i][j] = 0;
		f[0][0] = 1;
		rep(i,1,n) rep(j,0,i - 1) if (((s[i] - s[j]) | ans) == ans){
			rep(k,0,r) f[i][k] = f[i][k] | f[j][k - 1];
		}
		bool flag = 0;
		rep(j,l,r) if (f[n][j]) flag = 1;
		if (!flag) ans ^= (1 << t);
	}
	printf("%d\n",ans);
}
void work2(){}
int main(){
	scanf("%d%d%d",&n,&l,&r);
	s[0] = 0;
	rep(i,1,n) scanf("%d",&a[i]), s[i] = s[i - 1] + a[i];
	work1();
	return 0;
}