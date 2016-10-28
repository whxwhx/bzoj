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
const int M = 1000000000 + 7;
int main(){
	int n, mod; scanf("%d%d",&n,&mod);
	int s = 0, ans = 1;
	rep(i,1,n){
		char c = getchar(); while (c < '0' || c > '9') c = getchar(); int a = c - '0';
		s = (s * 10 + a) % mod;
		if (s == 0 && i != n) ans = ans * 2LL % M;
	}
	if (s != 0) printf("0\n"); else printf("%d\n",ans);
}