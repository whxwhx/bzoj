#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 100010, M = 1000000007;
int p[N], l = 0, mu[N];
bool a[N];

void pri(){
	mu[1] = 1;
	rep(i,2,N - 10) a[i] = true;
	rep(i,2,N - 10) {
		if (a[i]) p[++l] = i, mu[i] = -1;
		rep(j,1,l){
			int k = i * p[j];
			if (k > N - 10) break;
			a[k] = false;
			if (i % p[j] == 0){
				mu[k] = 0; break;
			}else
				mu[k] = -mu[i];
		}
	}
}


int gcd(int a, int b){
	return b ? gcd(b, a % b) : a;
}

int pw(int a, int b){
	int w = 1;
	for(;b;b >>= 1, a = 1LL * a * a % M) if (b & 1) w = 1LL * w * a % M;
	return w;
}

int main(){
	pri();
	int n, k, l, r; scanf("%d%d%d%d",&n,&k,&l,&r);
	int ans = 0;
	rep(i,1,r - l + 1){
		int t = pw(r / k / i - (l - 1) / k / i, n) - (r / k / i - (l - 1) / k / i);
		ans = (ans + t * mu[i]) % M;
	} 
	if (l <= k && k <= r) ans++;
	if (ans < 0) ans += M;
	printf("%d\n",ans);
}