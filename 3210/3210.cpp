#include <iostream>
#include <cstdio>
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
#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))
#define ab(a) ((a) > 0 ? (a) : -(a))
#define mp(a,b) make_pair(a,b)
#define pb(a) push_back(a)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
const int N = 100010;
int x[N], y[N], x1[N], y1[N], n; 
LL calc(int X, int Y){
	LL ans = 0;
	rep(i,1,n) ans += max(ab(X - x[i]), ab(Y - y[i]));
	return ans;
}
int main(){scanf("%d",&n);
	rep(i,1,n) scanf("%d%d",&x[i],&y[i]), x1[i] = x[i] + y[i], y1[i] = x[i] - y[i];
	nth_element(x1 + 1, x1 + (n >> 1) + 1, x1 + n + 1);
	nth_element(y1 + 1, y1 + (n >> 1) + 1, y1 + n + 1);
	int t1 = x1[(n >> 1) + 1], t2 = y1[(n >> 1) + 1];
	if ((t1 ^ t2) & 1){
		int tx = (t1 + t2) >> 1, ty = (t1 - t2) >> 1;
		printf("%lld\n",min(min(calc(tx, ty), calc(tx + 1, ty)), min(calc(tx, ty + 1), calc(tx + 1, ty + 1))));
	}else{
		int tx = (t1 + t2) >> 1, ty = (t1 - t2) >> 1;
		printf("%lld\n",calc(tx, ty));
	}
}