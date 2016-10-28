#include <iostream>
#include <cstdio>
#include <cmath>
#include <set>
#include <map>
#include <queue>
#include <bitset>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define Rep(i,a) for(int i = 0; i < (a); i++)
#define rep(i,a,b) for(int i = (a); i <= (b); i++)//(a)!
#define dep(i,a,b) for(int i = (a); i >= (b); i--)
#define ab(a) ((a) > 0 ? (a) : -(a))
#define mp(a,b) make_pair((a),(b))
#define pb(a) push_back(a)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
const int N = 260;
char s[N][N];
bool a[N][N], ans[N];
bitset<N> equ[N * 2], c[N][N];
void print(bitset<N> &a, int n){
	rep(i,0,n) cout <<a[i]<<' ';cout <<endl;
}
bool solve(int n, int m){
	rep(i,1,n){
		int t = 0;
		rep(j,i,m) if (equ[j][i]) {t = j;break;}
		if (t){
			swap(equ[t], equ[i]);
			rep(j,i + 1,m) if (equ[j][i]) equ[j] ^= equ[i];
		}
	}
	rep(i,n + 1,m) if (equ[i][0]) return false;
	dep(i,n,1){
		if (equ[i][i] == 0 && equ[i][0]) return false;
		ans[i] = equ[i][0];
		if (ans[i])
			rep(j,1,i - 1) if (equ[j][i]) equ[j][0] = equ[j][0] ^ ans[i];
	}
	return true;
}
void work(int t){
	int n, m, k; scanf("%d%d%d",&n,&m,&k);
	rep(i,1,n) scanf("%s",s[i] + 1);
	rep(i,1,n) rep(j,1,m) if (s[i][j] == 'W') a[i][j] = 0; else a[i][j] = 1;

	rep(i,0,n + 1) rep(j,0,m + 1) c[i][j] = 0;
	rep(i,1,m) c[1][i][i] = 1;
	rep(i,2,n)
		rep(j,1,m) 
			c[i][j] = c[i - 1][j] ^ c[i - 1][j - 1] ^ c[i - 1][j + 1] ^ c[i - 2][j], 
			c[i][j][0] = c[i][j][0] ^ a[i - 1][j];

	rep(i,1,m) equ[i] = c[n][i] ^ c[n][i - 1] ^ c[n][i + 1] ^ c[n - 1][i], equ[i][0] = equ[i][0] ^ a[n][i];
	rep(i,1,k) {
		int x, y; scanf("%d%d",&x,&y);
		equ[m + i] = c[x][y];
	}
	printf("Case #%d:\n",t);
	if (solve(m, m + k)) printf("YES\n");
	else printf("NO\n");
}
int main(){
	int T, t = 0; scanf("%d",&T);
	while (T--) work(++t);
}