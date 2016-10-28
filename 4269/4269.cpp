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
const int N = 100000 + 10;
int a[N], h[32];
int main(){
	int n; scanf("%d",&n);
	rep(i,1,n){
		int a; scanf("%d",&a);
		dep(i,30,0) if (a >> i & 1) {
			if (h[i]) a ^= h[i]; else {h[i] = a; break;}
		}
	}
	//calc max
	int tmp = 0;
	dep(i,30,0) if (h[i] && (tmp >> i & 1) == 0) tmp ^= h[i];
	int t = 0;
	rep(i,0,30) if (h[i]) {t = i;break;}
	int t1 = tmp ^ h[t];
	printf("%d %d\n",tmp,t1);
}