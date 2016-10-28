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
const int mod = 1000000000 + 7;
typedef long long LL;
typedef unsigned long long uLL;
int p[35], l = 0;
int phi(int n){
	int ans = n;
	rep(i,1,l) if (n % p[i] == 0) ans = ans / p[i] * (p[i] - 1);
	return ans;
}
int pow(int a, int b){
	int w = 1;
	for(;b;b >>= 1, a = 1LL * a * a % mod) if (b & 1) w = 1LL * w * a % mod;
	return w;
}
int n, k;
#define m1(a) ((a) & 1 ? -1 : 1)
int invfac[1010];
int C(int n, int m){
	int ans = 1;
	rep(i,0,m - 1) ans = 1LL * ans * (n - i) % mod;
	ans = 1LL * ans * invfac[m] % mod;
	return ans;
}
int calc(int a, int c){
	if (k % a != 0) return 0;
	int t = k / a;
	return C(c, t) * m1(t) * m1(a & t);
}
int main(){
	scanf("%d%d",&n, &k);
	if (n == 1 && k <= 1) {printf("1\n");return 0;}
	int tmp = 1;
	rep(i,1,k) tmp = 1LL * tmp * i % mod;
	invfac[k] = pow(tmp, mod - 2);
	dep(i,k - 1,0) invfac[i] = 1LL * invfac[i + 1] * (i + 1) % mod;

	int t = n;
	for(int i = 2; i * i <= t; i++) if (t % i == 0){
		p[++l] = i;
		while (t % i == 0) t /= i;
	}
	if (t > 1) p[++l] = t;

	int ans = 0;
	for(int i = 1; i * i <= n; i++) if (n % i == 0){
		int k = i;
		ans = (ans + 1LL * calc(n / k, k) * phi(n / k)) % mod;
		if (i * i != n){
			int k = n / i;
			ans = (ans + 1LL * calc(n / k, k) * phi(n / k)) % mod;
		}
	}
	ans = 1LL * ans * pow(n, mod - 2) % mod;
	if (ans < 0) ans += mod;
	printf("%d\n",ans);
}