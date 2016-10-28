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
const int N = 10;
int L[N][N], R[N][N];
double ans = 0;
bool vis[N];
int n; 
/*
void dfs(int x, double p){
	if (x > n) ans += p;
	else{
		if (!(x & 1)) p = -p;
		rep(i,1,n) if (!vis[i]){
			vis[i] = true;
			dfs(x + 1, p * (L[x][i] + R[x][i]) / 2.0);
			vis[i] = false;
		}else p = -p;
	}
}
int main(){
	scanf("%d",&n);
	rep(i,1,n) rep(j,1,n) scanf("%d",&L[i][j]);
	rep(i,1,n) rep(j,1,n) scanf("%d",&R[i][j]);
	dfs(1, 1);
	int t = (int)ans;
	while (t > ans) t--;
	while (t + 1 < ans) t++;
	printf("%d\n",t);
	return 0;
}*/
const int M = 1 << 9;
double f[M];
int cnt[M];
int main(){
	scanf("%d",&n);
	rep(i,1,n) rep(j,1,n) scanf("%d",&L[i][j]);
	rep(i,1,n) rep(j,1,n) scanf("%d",&R[i][j]);
	int m = (1 << n) - 1;
	cnt[0] = 0;
	f[0] = 1;
	rep(i,0,m){
		if (i) cnt[i] = cnt[i - ((-i) & i)] + 1;
		int F = 1;
		if (cnt[i] & 1) F = -1;
		rep(j,1,n) if ((i >> (j - 1) & 1) == 0) 
			f[i | (1 << (j - 1))] += f[i] * (R[cnt[i] + 1][j] + L[cnt[i] + 1][j]) / 2.0 * F;
		else F = -F;
	}
	int t = f[m];
	while (t + 1 < f[m]) t++;
	while (t > f[m]) t--;
	printf("%d\n",t);
	return 0;
}