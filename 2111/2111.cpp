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
#define Rep(i,a) for(int i = 0; i < a; i++)
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
#define ab(a) ((a) > 0 ? (a) : -(a))
#define mp(a,b) make_pair(a,b)
#define pb(a) push_back(a)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
const int N = 1000000 + 10;
int s[N], f[N], fac[N], inv[N], P;
int pow(int a, int b){
	int w = 1;
	for(;b;a = 1LL * a * a % P, b >>= 1) if (b & 1) w = 1LL * w * a % P;
	return w;
}
int C(int n, int m){
	if (m > n) return 0;
	if (n < P && m < P) 
		return 1LL * fac[n] * inv[n - m] % P * inv[m] % P;
	else 
		return 1LL * C(n / P, m / P) * C(n % P, m % P) % P;
}
int main(){
	int n; scanf("%d%d",&n,&P);
	fac[0] = 1;

	int m = n; if (m >= P) m = P - 1;
	rep(i,1,m) fac[i] = 1LL * fac[i - 1] * i % P;
	inv[m] = pow(fac[m], P - 2);
	dep(i,m - 1,0) inv[i] = 1LL * inv[i + 1] * (i + 1) % P;

	dep(i,n,1) if ((i << 1) > n)
		s[i] = 1, f[i] = 1;
	else if ((i << 1) + 1 > n)
		s[i] = s[i << 1] + 1, f[i] = f[i << 1];
	else{
		s[i] = s[i << 1] + s[(i << 1) + 1] + 1;
		f[i] = 1LL * C(s[i] - 1, s[i << 1]) * f[i << 1] % P * f[(i << 1) + 1] % P;
	}
	printf("%d\n",f[1]);
	return 0;
}