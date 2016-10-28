#include <iostream>
#include <cstdio>
#include <algorithm>
#define min(a,b) ((a) < (b) ? (a) :  (b))
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N = 3000 + 10;
typedef long long LL;
int a[N], b[N], c[N];
LL f[N][N];
int main(){
	int n, T;  scanf("%d%d",&n,&T);
	rep(i,1,n){
		int u, v, d, e;
		scanf("%d%d%d%d",&u,&v,&d,&e);
		a[i] = u + e; 
		b[i] = u + v;
		c[i] = d + e;
	}
	f[1][0] = b[1];
	rep(i,1,n) f[1][i] = a[1] * i;

	rep(i,2,n){
		f[i][n] = f[i - 1][n] + 2 * n * T + min(b[i], c[i]);
		dep(j,n - 1,0) {
			f[i][j] = f[i][j + 1] + a[i];
			f[i][j] = min(f[i][j], f[i - 1][j] + 2 * j * T + b[i]);
			if (j) f[i][j] = min(f[i - 1][j] + 2 * j * T + c[i], f[i][j]);
		}
		rep(j,1,n) {
			f[i][j] = min(f[i][j], f[i][j - 1] + a[i]);
			f[i][j] = min(f[i][j], f[i - 1][j - 1] + a[i]);
		}
	}
	printf("%lld\n",f[n][0] + (n + 1) * T);
	return 0;
}