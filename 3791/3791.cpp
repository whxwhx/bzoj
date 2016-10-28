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
const int N = 100010, M = 110;
#define max(a,b) ((a) > (b) ? (a) : (b))
int a[N], f[N][M], g[N][M];
int main(){
	int n, k; scanf("%d%d",&n,&k);
	if (k == 0) {cout <<0<<endl; return 0;}
	int m = (k << 1) - 1;
	rep(i,1,n) scanf("%d",&a[i]);
	rep(i,1,n){
		if (a[i]){
			rep(j,1,m) {
				f[i][j] = max(f[i - 1][j], g[i - 1][j - 1]) + 1;
				g[i][j] = max(g[i - 1][j], f[i - 1][j - 1]);
			}
		}else {
			rep(j,1,m){
				f[i][j] = max(f[i - 1][j], g[i - 1][j - 1]);
				g[i][j] = max(g[i - 1][j], f[i - 1][j - 1]) + 1;
			}
		}
	}
	printf("%d\n",max(f[n][m], g[n][m]));
}