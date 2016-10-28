#include <iostream>
#include <cstdio>
#include <algorithm>
#define ab(a) ((a) < 0 ? -(a) : (a))
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
typedef long long LL;
LL ans = 0;
const int N = 1000100;
int a[N], aver;
LL s[N], sum;
int main(){
	int n;scanf("%d",&n); sum = 0;
	rep(i,0,n - 1) scanf("%d",&a[i]), sum += a[i];
	aver = sum / n, s[0] = 0;
	rep(i,1,n - 1) s[i] = s[i - 1] + a[i] - aver;
	rep(i,1,n - 1) s[i] = -s[i];
	nth_element(s, s + n / 2, s + n);
	LL t = s[n/2];
	rep(i,0,n - 1) ans += ab(t - s[i]);
	printf("%lld\n",ans);
	return 0;
}