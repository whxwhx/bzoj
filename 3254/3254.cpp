#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
typedef long long LL;
LL ans = 0;
const int N = 10000 + 10, M = (1 << 5);
int n, m; 
LL f[6][N][M];
#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))
int a[6][N], b[6][N], c[6][N], c1[6][N];
void dp(int t){
	LL tmp = (1ull << 63) - 1;
	int M = (1 << n);
	rep(i,0,M - 1) f[n][0][i] = 0;

	rep(j,1,m){
		int t = 1 << (n - 1);
		rep(k,0,M - 1)
			f[1][j][k] = ((a[1][j] & 1) ^ (k & t ? 1 : 0)) * 1LL * b[1][j],
			f[1][j][k] += min(f[n][j - 1][k], f[n][j - 1][k ^ t] + c1[1][j - 1]);
		rep(i,2,n - 1){
			t = 1 << (n - i);
			rep(k,0,M - 1)
				f[i][j][k] =  ((a[i][j] & 1) ^ (k & t ? 1 : 0)) * 1LL * b[i][j],
				f[i][j][k] += (k >> (n - i) & 1) == (k >> (n - i + 1) & 1) ? 0 : c[i - 1][j],
				f[i][j][k] += min(f[i - 1][j][k], f[i - 1][j][k ^ t] + c1[i][j - 1]);
		}
		t = 1;
		rep(k,0,M - 1)
			f[n][j][k] = ((a[n][j] & 1) ^ (k & t)) * 1LL * b[n][j], 
			f[n][j][k] += (k & 1) == (k >> 1 & 1) ? 0 : c[n - 1][j],
			f[n][j][k] += (k & 1) == (k >> (n - 1) & 1) ? 0 : c[n][j],
			f[n][j][k] += min(f[n - 1][j][k], f[n - 1][j][k ^ t] + c1[n][j - 1]);
	}
	rep(k,0,M - 1) tmp = min(f[n][m][k], tmp);
	//rep(i,1,n) rep(j,1,m) cout <<i<<' '<<j<<' '<<f[i][j][0]<<endl;
	//cout <<a[1][2]<<endl;
	//cout <<t<<' '<<tmp<<endl;
	ans += tmp << t;
}
int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,n)
		rep(j,1,m) scanf("%d",&a[i][j]);
	rep(i,1,n) 
		rep(j,1,m) scanf("%d",&b[i][j]);
	rep(i,1,n)
		rep(j,1,m - 1) scanf("%d",&c1[i][j]);
	rep(i,1,n)
		rep(j,1,m) scanf("%d",&c[i][j]);
	rep(i,0,19) {
		dp(i);
		rep(j,1,n) rep(k,1,m) a[j][k] >>= 1;
	}
	printf("%lld\n",ans);
}