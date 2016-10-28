#include <iostream>
#include <cstdio>
#include <cmath>
#include <set>
#include <map>
#include <queue>
#include <bitset>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define Rep(i,a) for(int i = 0; i < a; i++)
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
#define ab(a) ((a) > 0 ? (a) : -(a))
#define mp(a,b) make_pair(a,b)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
const int N = 500000 + 10;
int p[N * 2], mx, n;
char s[N * 2];
void manacher(){
	dep(i,n,1) s[i << 1] = s[i];
	n = 2 * n + 1;
	rep(i,1,n) if (i & 1) s[i] = '#';
	
	mx = 0;
	int j = 0;
	rep(i,1,n){
		if (mx > i) {
			p[i] = min(mx - i, p[2 * j - i]);
			if ((j & 1) == 0) p[i] = min(p[i], i - j);
		}else p[i] = 1;
		while ((i - p[i] > 0) && (i + p[i] <= n) && (s[i - p[i]] != s[i + p[i]] || s[i - p[i]] == '#')) p[i]++;
		if (i + p[i] > mx) mx = i + p[i], j = i;
	}
}
int main(){
	scanf("%d",&n);
	scanf("%s",s + 1);
	manacher();
	long long ans = 0;
	rep(i,1,n) if (i & 1) ans += (p[i] - 1) >> 1;
	printf("%lld\n",ans);
	return 0;
}