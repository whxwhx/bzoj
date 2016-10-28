#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N = 800 + 10, M = 1000000007;
char a[N], b[N];
int A[N], B[N], tmp[N], lena, lenb, t;
void init(){
	scanf("%s%s",a,b);
	lena = strlen(a), lenb = strlen(b);
	int l = max(lena, lenb);
	rep(i,0,l) A[i] = B[i] = 0;
	rep(i,0,lena - 1) A[lena - 1 - i] = a[i] - '0';
	rep(i,0,lenb - 1) B[lenb - 1 - i] = b[i]  - '0';
	int j = 0;
	rep(i,0,lena - 1){
		A[i] += j;
		j = A[i] >> 1;
		A[i] &= 1;
	}
	while (j) A[lena++] = j & 1, j >>= 1;
}
int f[N][11][2];
void work(){
	init();
	rep(i,0,lena) rep(j,0,9) f[i][j][0] = f[i][j][1] = 0;
	if (lenb > lena) 
		f[lena][0][0] = 1;
	else 
		f[lena][0][1] = 1;

	dep(i,lena - 1,0){
		rep(j, 0, 9){
			rep(k, 0, 9){
				int t = j * 2 + A[i] - k;
				if (t < 0) break;
				if (t > 9) t = 9;
				if (k == B[i]) f[i][t][1] += f[i + 1][j][1], f[i][t][1] %= M;
				f[i][t][0] += f[i + 1][j][0], f[i][t][0] %= M;
				if (k < B[i]) f[i][t][0] += f[i + 1][j][1], f[i][t][0] %= M;
			}
		}
		//rep(j,0,9) cout <<i<<' '<<j<<' '<<f[i][j][0]<<' '<<f[i][j][1]<<' '<<endl;cout <<endl;
	}

	int ans = 0;
	rep(i,0,9) ans += f[0][i][0], ans %= M, ans += f[0][i][1], ans %= M;
	printf("Case #%d: %d\n",t,ans);
}
int main(){
	int m;
	scanf("%d",&m);
	while (t < m) t++, work();
}