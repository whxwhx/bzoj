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
const int N = 2005, inf = 2000000000;
int a[N], f[N][N], n, tl = 1, L[N], R[N];
int main(){
	scanf("%d",&n); rep(i,1,n) scanf("%d",&a[i]);
	dep(i,n,1){
		rep(j,i,n){
			f[i][j] = inf;
			rep(k,i,j) f[i][j] = min(f[i][j], max(f[i][k - 1], f[k + 1][j]) + a[k]);
		}
	}
	printf("%d\n",f[1][n]);
	return 0;
}