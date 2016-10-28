#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
typedef long long LL;

const int N = 1000000 + 10;

int a[N], s[N], n, b[N];
LL k;
void add(int x){
	for(;x <= n;x += (-x) & x) s[x]++;
}
int sum(int x){
	int ans = 0;
	for(;x;x -= (-x) & x) ans += s[x];
	return ans;
}

int up[N];
int main(){
	scanf("%d%lld",&n,&k);
	rep(i,1,n) scanf("%d",&a[i]), s[i] = 0;
	rep(i,1,n)
		up[i] = (i - 1) - sum(a[i]), add(a[i]);

	int l = -1, r = n + 1;//(l,r]
	while (l + 1 < r){
		int mid = (l + r) >> 1;
		LL cnt = 0;
		rep(i,1,n) cnt += min(mid, up[i]);
		if (cnt >= k) r = mid; else l = mid;//注意这里应该找>=k的第一轮而不是<=k的最后一轮。。因为可能某一轮就交换完了。。于是一直<=k
	}
	if (l == n) {printf("Impossible!\n");return 0;}

	LL cnt = k;
	rep(i,1,n) cnt -= min(l, up[i]);
	rep(i,1,n) if (up[i] >= l){
		b[i - l] = a[i];
		a[i] = n + 1;
	}
	sort(a + 1, a + n + 1);
	int j = 1;
	rep(i,1,n) if (!b[i]) b[i] = a[j++];
	rep(j,1,n - l){
		if (!cnt) break;
		if (b[j] > b[j + 1]) swap(b[j], b[j + 1]), cnt--;
	}
	rep(i,1,n - 1) printf("%d ", b[i]);
	printf("%d\n",b[n]);
	return 0;
}