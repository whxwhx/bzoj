#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 1010;
int a[N][N], b[N][N], t1[N], t2[N], ans = N * N, n;
void calc(){
	rep(i,1,n) t1[i] = t2[i] = 0;
	rep(i,1,n) rep(j,1,n) t1[i] ^= a[i][j];
	rep(i,1,n) rep(j,1,n) t2[j] ^= a[i][j];
	int cnt = 0;
	rep(i,1,n) rep(j,1,n) {
		b[i][j] = t1[i] ^ t2[j] ^ a[i][j];
		if (b[i][j]) cnt++;
	}
	ans = min(ans, cnt);
}
int main(){
	scanf("%d",&n);
	rep(i,1,n) rep(j,1,n) {
		char c = getchar();
		while (c < '0' || c > '1') c = getchar();
		if (c == '0') a[i][j] = 0; else a[i][j] = 1;
	}
	calc();
	rep(i,1,n) rep(j,1,n) a[i][j] ^= 1;
	calc();
	printf("%d\n",ans);
}