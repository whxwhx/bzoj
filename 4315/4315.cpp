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
const int N = 100010, mod = 1000000007;

int a[N];
typedef pair<int, int> node;
node b[N];
#define val first
#define pos second

bool cmp(const node &a, const node &b){
	return a.pos < b.pos;
}

int fac[N], inv[N];
int C(int n, int m){
	if (n < m) return 0;
	return 1LL * fac[n] * inv[m] % mod * inv[n - m] % mod;
}

int ans = 0;
int n, k;
void work(int m){
	sort(b + 1, b + k + 1, cmp);
	int ways = 1;
	int t[2] = {0,0}, d = 0, cur[2] = {0,n + 1};
	rep(i,1,k){
		d = (b[i].val > m);
		int x = cur[d] - b[i].val; if (x < 0) x = -x;
		if (x - 1 < t[d ^ 1]) return;
		x -= t[d ^ 1], t[d ^ 1] = 0;
		
		t[d] += b[i].pos - b[i - 1].pos - x;
		if (b[i].pos - b[i - 1].pos < x) return;
		ways = 1LL * ways * C(b[i].pos - b[i - 1].pos - 1, x - 1) % mod;
		
		cur[d] = b[i].val;
	}
	if (a[n] == 0){
		d ^= 1;
		rep(i,cur[0] + 1,cur[1] - 1){
			int x = cur[d] - i; if (x < 0) x = -x;
			if (x - 1 < t[d ^ 1]) continue;
			x -= t[d ^ 1];
			
			if (n - b[k].pos < x) return;
			ans += 1LL * ways * C(n - b[k].pos - 1, x - 1) % mod;
			ans %= mod;
		}
	}else{
		if (t[1] != a[n] - cur[0] - 1) return;
		ans = (ans + ways) % mod;
	}
}

int pow(int a, int b){
	int w = 1;
	for(;b;b >>= 1, a = 1LL * a * a % mod) if (b & 1) w = 1LL * w * a % mod;
	return w;
}

void init(){
	scanf("%d%d",&n,&k);

	fac[0] = 1;
	rep(i,1,n) fac[i] = 1LL * fac[i - 1] * i % mod;
	inv[n] = pow(fac[n], mod - 2);
	dep(i,n - 1,0) inv[i] = 1LL * inv[i + 1] * (i + 1) % mod;	

}

int main(){
	init();

	rep(i,1,k){
		int x, y;
		scanf("%d%d",&y,&x);
		if (a[x]) {printf("0\n");return 0;}
		a[x] = y;
		b[i] = mp(y, x);
	}

	if (!k) work(0);
	else {
		sort(b + 1, b + k + 1);

		int t1 = k;
		rep(i,2,k) if (b[i - 1].second > b[i].second)
			{t1 = i - 1; break;}

		rep(i,t1 + 1,k) if (b[i - 1].second < b[i].second)
			{printf("0\n");return 0;}

		int tmp = b[t1].val;
		work(b[t1 - 1].val);
		if (!a[n]) work(tmp);
	}

	if (ans < 0) ans += mod;
	printf("%d\n",ans);
	return 0;
}