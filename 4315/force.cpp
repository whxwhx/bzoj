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
const int N = 100010, mod = 1000000000 + 7;
using namespace std;
int a[N];
int n;
int ans = 0;
void dfs(int x, int t1, int t2){
	if (a[x] && a[x] != t1 && a[x] != t2) return;
	if (x == n) {ans++; ans %= mod; return;}
	if (a[x] && a[x] == t1) {dfs(x + 1, t1 + 1, t2);return;}
	if (a[x] && a[x] == t2) {dfs(x + 1, t1, t2 - 1);return;}
	dfs(x + 1, t1 + 1, t2);
	dfs(x + 1, t1, t2 - 1);
}
int main(){
	int k; scanf("%d%d",&n,&k);
	rep(i,1,k) {
		int y, x; scanf("%d%d",&y,&x);
		if (a[x]) {printf("0\n");return 0;}
		a[x] = y;
	}
	dfs(1, 1, n);
	printf("%d\n",ans);
}