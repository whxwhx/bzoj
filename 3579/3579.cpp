#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N = 1010, M = 1000003;
int d[N], c[N][N];
void work(){
	int n,m; 
	scanf("%d%d",&n,&m);
	
	rep(i,1,n) d[i] = 0;
	rep(i,1,m){
		int x, y;
		scanf("%d%d",&x,&y);
		d[x]++, d[y]++;
	}

	sort(d+1, d+n+1);
	rep(i,1,n/2) swap(d[i], d[n - i + 1]);

	rep(i,1,n){
		c[i][0] = c[i][i] = 1;
		rep(j,1,i - 1) c[i][j] = c[i - 1][j] +c[i - 1][j - 1], c[i][j] %= M;
	}

	d[0] = -1;
	int ans = 0;
	rep(i,1,n) if (d[i] != d[i-1]){
		int sum1 = 0, sum2 = 0, cnt1 = 0, cnt = 0;
		rep(j,1,n)
	 		if (d[j] > d[i]) sum1 += d[j], cnt1++;
	 		else if (d[j] < d[i]) sum2 += d[j];
	 		else cnt++;
		rep(j,1,cnt){
			if (cnt1 + j == n) break;
			if (sum1 + d[i] * j - sum2 - d[i] * (cnt - j) == (cnt1 + j) * (cnt1 + j - 1)) ans += c[cnt][j], ans %= M;
		}
	}
	printf("%d\n",ans);
}
int main(){
	int T; 
	scanf("%d",&T);
	while (T--) work();
}