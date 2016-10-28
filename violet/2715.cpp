//poj 3609
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
#define Rep(i,a) for(int i = 0; i < a; i++)
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
#define ab(a) ((a) > 0 ? (a) : -(a))
#define mp(a,b) make_pair(a,b)
#define pb(a) push_back(a)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
int a[17][17], b[65537][17];
int f[65537], q[65537], f1[65537], f2[65537];
int main(){
	int n, m; scanf("%d%d",&n,&m);
	rep(i,1,n) rep(j,1,m) scanf("%d",&a[i][j]);
	int M = (1 << n) - 1;
	rep(i,0,M)
		rep(j,1,m){
			b[i][j] = 0;
			rep(k,1,n) if (i >> (k - 1) & 1) b[i][j] |= 1 << a[k][j];
		}
	rep(i,0,M) f[i] = -1;
	int l = 0, r = 1; q[f[M] = 0] = M;
	while (l < r){
		int i = q[l++];
		rep(j,1,m) if (f[b[i][j]] == -1) f[b[i][j]] = f[i] + 1, f1[b[i][j]] = j, f2[b[i][j]] = i, q[r++] = b[i][j];
	}
	if (f[1] == -1) printf("*\n"); else {
		l = 0;
		for(int i = 1; i != M; i = f2[i]) q[++l] = f1[i] - 1;
		dep(i,l,1) if (q[i] <= 9) printf("%c",'0' + q[i]); else printf("%c", 'a' + q[i] - 10);
		printf("\n");
	}
}