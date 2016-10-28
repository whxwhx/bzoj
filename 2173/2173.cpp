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
const int N = 1000000 + 10, M = 1000000000 + 7;
int f[N], F[N];
int main(){
	F[1] = F[2] = 1;
	f[1] = 1, f[2] = 2;
	int n; scanf("%d",&n);
	rep(i,3,n) f[i] = 2 * f[i - 1] % M + f[i - 2], f[i] %= M;
	printf("%d\n", f[n]);
}