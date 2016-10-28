#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N = 4210;
int n, p, f[2][N][2], s[N][2];
int main(){
	scanf("%d%d",&n,&p);
	int t = 1;
	f[1][1][0] = f[1][1][1] = 1;
	rep(i,2,n){
		t^=1;
		s[0][0] = s[0][1] = 0;
		rep(j,1,i - 1) 
			s[j][0] = s[j - 1][0] + f[t^1][j][0], s[j][1] = s[j - 1][1] + f[t^1][j][1],
			s[j][0]%= p,							s[j][1]%= p;
		rep(j,1,i)
			f[t][j][0] = (s[i - 1][1] - s[j - 1][1]) % p, 
			f[t][j][1] = s[j - 1][0];
	}
	int ans = 0;
	rep(i,1,n) ans += f[t][i][0], ans %= p, ans += f[t][i][1], ans %= p;
	if (ans < 0) ans += p;
	printf("%d\n",ans);
	return 0;
}