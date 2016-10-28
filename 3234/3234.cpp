#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N = 210;
short f[N][N][N];
const int inf = 100000;
int ans = 0;
int q[210 * 210 * 210], l, r;
void floodfill(){
	
}
int main(){
	int n; scanf("%d",&n);
	rep(i,0,N - 1) rep(j,0,N - 1) rep(k,0,N - 1) f[i][j][k] = 0;
	rep(i,1,n){
		int x1, y1, z1, x2, y2, z2;
		scanf("%d%d%d%d%d%d",&x1,&y1,&z1,&x2,&y2,&z2);
		x1 += 2, y1 += 2, z1 += 2, x2 += 2, y2 += 2, z2 += 2; 
		f[x2][y2][z2]++;
		f[x1][y2][z2]--;
		f[x2][y1][z2]--;
		f[x2][y2][z1]--;
		f[x1][y1][z2]++;
		f[x1][y2][z1]++;
		f[x2][y1][z1]++;
		f[x1][y1][z1]--;
	}
	dep(i, N - 2, 0)
		dep(j, N - 2, 0)
			dep(k, N - 2, 0)
				f[i][j][k] = f[i][j][k] + (f[i + 1][j][k] + f[i][j + 1][k] + f[i][j][k + 1] - f[i + 1][j + 1][k] - f[i + 1][j][k + 1] - f[i][j + 1][k + 1] + f[i + 1][j + 1][k + 1]); 
	floodfill();
	rep(i, 1, N - 2)
		rep(j, 1, N - 2)
			rep(k, 1, N - 2)
				if (f[i][j][k]){
					if (f[i - 1][j][k] == inf) ans++;
					if (f[i][j - 1][k] == inf) ans++;
					if (f[i][j][k - 1] == inf) ans++;
					if (f[i + 1][j][k] == inf) ans++;
					if (f[i][j + 1][k] == inf) ans++;
					if (f[i][j][k + 1] == inf) ans++;
				}
	printf("%d\n",ans);
	return 0;
}