#include <iostream>
#include <cstdio>
#include <algorithm>
typedef long long LL;
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
long double ans = 0;
const int N = 100;
double f[N], g[N];
int main(){
	LL n; scanf("%lld",&n); double p; scanf("%lf",&p);
	int t = 0; LL m = n; while (m >> 1) t++, m >>= 1;
	//case1
	dep(i,t,0){
		ans += (long double)((1LL << i) - 1) / n * ((1LL << i) - 1) / n * ((1LL << i) - 1) * 0.5 * p;
		ans += (long double) 2LL* ((1LL << i) - 1) / n * (n & ((1LL << i) - 1)) / n * ( (1LL << i) - 1 ) * 0.5 * p;
	}
	//case2
	g[t + 1] = 0, f[t + 1] = 1;
	dep(i,t,0){
		f[i] = f[i - 1]	
	}
	double A = ans;
	printf("%.8lf\n",A); return 0;
}