#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
#define id(x,y) (x * n + y)
const int N = 52;
const int inf = 250000000;
int a[N][N], b[N][N];
int main(){
	int n, m; scanf("%d%d",&n,&m);
	rep(i,1,n) rep(j,1,m) scanf("%d",&a[i][j]);
	rep(i,1,n) a[i][0] = a[i][n + 1] = -inf;
	rep(i,1,m) a[0][i] = a[n + 1][i] = -inf;
	
}