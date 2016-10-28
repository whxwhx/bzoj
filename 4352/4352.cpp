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
const int N = 700000, mod = 998244353;
int a[N], ans;
int main(){
	int n, D; scanf("%d%d",&n,&D);
	rep(i,1,n) scanf("%d",&a[i]);
	sort(a + 1, a + n + 1);
	int j = n, ans = 1;
	dep(i,n,1){
		while (j && a[j] + D >= a[i]) j--;
		ans = 1LL * ans * (i - j) % mod;
	}
	printf("%d\n",ans);
}