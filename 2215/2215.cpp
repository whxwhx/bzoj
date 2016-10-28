#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N = 5010;
typedef long long LL;
int d[N];
LL c[N][N];
void work(){
	int n; 
	scanf("%d",&n);
	
	rep(i,1,n) d[i] = 0;
	rep(i,1,n){
		int k; scanf("%d",&k);
		rep(j,1,k) {
			int t; scanf("%d",&t);
			d[t]++;
		}
	}

	sort(d+1, d+n+1);
	rep(i,1,n/2) swap(d[i], d[n - i + 1]);

	LL M = n * n;
	rep(i,1,n){
		c[i][0] = c[i][i] = 1;
		rep(j,1,i - 1) {
			c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
			if (c[i][j] > M) break;
		}
		dep(j,i - 1,1){
			c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
			if (c[i][j] > M) break;
		}
	}

	d[0] = -1;
	LL ans = 0;
	rep(i,1,n) if (d[i] != d[i-1]){
		int sum1 = 0, sum2 = 0, cnt1 = 0, cnt = 0;
		rep(j,1,n)
	 		if (d[j] > d[i]) sum1 += d[j], cnt1++;
	 		else if (d[j] < d[i]) sum2 += d[j];
	 		else cnt++;
		rep(j,1,cnt){
			if (cnt1 + j == n) break;
			if (sum1 + d[i] * j - sum2 - d[i] * (cnt - j) == (cnt1 + j) * (cnt1 + j - 1)) ans += c[cnt][j];
		}
	}
	printf("%lld\n",ans);
}
int main(){
	work();
}