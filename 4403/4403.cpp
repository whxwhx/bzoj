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
const int p = 1000003;
using namespace std;
LL ans=0;
int fac[p], inv[p];
int pow(int a, int b){
	int w = 1;
	for(;b;b >>= 1, a = 1LL * a * a % p) if (b & 1) w = 1LL * w * a % p;
	return w;
}
int C(int n,int m){//C(n,m) % p
	if (n < m) return 0;
	return 1LL * fac[n] * inv[m] * inv[n - m] % p;
}
int Lucas(int n,int m){
	if (m==0) return 1;
	else return 1LL * Lucas(n/p,m/p) * C(n%p,m%p) % p;
}
int main(){
	fac[0] = 1;
	rep(i,1,p - 1) fac[i] = 1LL * fac[i - 1] * i % p;
	inv[p - 1] = pow(fac[p - 1], p - 2);
	dep(i,p - 2, 0) inv[i] = 1LL * inv[i + 1] * (i + 1) % p;
	int T; scanf("%d",&T);
	rep(i,1,T){
		int n, l, r; scanf("%d%d%d",&n,&l,&r);
		int m = r - l;
		printf("%d\n",(Lucas(m + n + 1, n) + p - 1) % p);
	}
	return 0;
}