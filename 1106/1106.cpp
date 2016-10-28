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
const int N = 100010;
struct BIT{
	int s[N];
	void add(int x, int d){for(;x < N; x += (-x) & x) s[x] += d;}
	int sum(int x){int ans = 0; for(;x;x -= (-x) & x) ans += s[x];return ans;}
}b;
int pos[N], sum = 0;
int main(){
	int n, ans = 0; scanf("%d",&n), n <<= 1;
	rep(i,1,n){
		int a; scanf("%d",&a);
		if (!pos[a]) pos[a] = i, b.add(i, 1),sum++; else{
			ans += sum - b.sum(pos[a]);
			sum--, b.add(pos[a], -1);
		}
	}
	printf("%d\n",ans);
}