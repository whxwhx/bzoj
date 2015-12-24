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
int pow(int b, int c){
	int w = 1, a = 2;
	for(;b;b >>= 1, a = 1LL * a * a % c) if (b & 1) w = 1LL * w * a % c;
	return w;
}
const int N = 10000010;
int ans[N], l;
int phi(int n){
	int ans = n;
	for(int i = 2; i * i <= n; i++) if (n % i == 0){
		ans = ans / i * (i - 1);
		while (n % i == 0) n /= i;
	}
	if (n > 1) ans = ans / n * (n - 1);
	return ans;
}
int solve(int P){
	if (ans[P]) return ans[P];
	if (P == 1) return 0;
	int t = 0;
	while (P && !(P & 1)) P >>= 1, t++;
	if (!P) return 0; else{
		int ph = phi(P), t1 = pow((solve(ph) - t) % ph + ph, P);
		return ans[P] = t1 << t;
	}
}
int main(){
	int T; scanf("%d",&T);
	while (T--){
		int P; scanf("%d",&P);
		printf("%d\n",solve(P));
	}
}
