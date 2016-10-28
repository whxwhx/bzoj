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
#define rep(i,a,b) for(int i = (a), _b = (b); i <= _b; i++)//(a)!
#define dep(i,a,b) for(int i = (a); i >= (b); i--)
#define ab(a) ((a) > 0 ? (a) : -(a))
#define mp(a,b) make_pair((a),(b))
#define pb(a) push_back(a)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
const int N = 65536, mod = 1000000000 + 7;
int f[N], p[N], l = 0; bool a[N];
void init() {
	rep(i,2,N - 10) {
		if (!a[i]) p[++l] = i; 
		rep(j,1,l){
			int k = i * p[j]; if (k > N - 10) break;
			a[k] = true; 
			if (i % p[j] == 0) break;
		}
	}
}

void fwt() { 
	rep(i,0,15) rep(j,0,65535) 
		if (j >> i & 1)
			f[j] = (f[j ^ (1<<i)] - (f[j] << 1)) % mod, f[j] = (f[j] < 0 ? f[j] + mod : f[j]); 
		else 
			f[j] = (f[j] + f[j ^ (1 << i)]) % mod;
}
int inv2;

void invfwt() { 
	dep(i,15,0) rep(j,0,65535) 
		if (j >> i & 1)
			f[j] = (f[j ^ (1 << i)] - f[j]) % mod, f[j] = (f[j] < 0 ? f[j] + mod : f[j]); 
		else 
			f[j] = (f[j] + f[j ^ (1 << i)]) % mod * 1LL * inv2 % mod;
}

int pw(int a, int b)
{ int w = 1; for(;b;b >>= 1, a = 1LL * a * a % mod) if (b & 1) w = 1LL * w * a % mod; return w; }

int main(){
	int n, m; init(); inv2 = pw(2, mod - 2);
	while (scanf("%d%d",&n,&m) == 2){
		memset(f, 0, sizeof(f));
		rep(i,1,l) if (p[i] <= m) f[p[i]] = 1;
		fwt();
		rep(i,0,65535) f[i] = pw(f[i], n);
		invfwt();
		printf("%d\n",f[0]);
	}
	return 0;
}