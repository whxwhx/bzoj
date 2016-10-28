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
#define min(a,b) ((a) < (b) ? (a) : (b))
#define pb(a) push_back(a)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
const int N = 100010;
const int inf = N + 10;
vector<int> a[N];
typedef vector<int>::iterator vit;
int f[N], n, t[N];
int find(int x){
	int l = 0, r = n;
	while (l + 1 < r){
		int mid = (l + r) >> 1;
		if (f[mid] <= x) l = mid; else r = mid; 
	}
	return l;
}
int main(){
	scanf("%d",&n);
	rep(i,1,n) {
		int t; scanf("%d",&t);
		if (1 <= t && t <= i) a[t].push_back(i - t);
	}
	f[0] = 0;
	rep(i,1,n) f[i] = inf;
	int ans = 0;
	rep(i,1,n){
		int cnt = 0;
		for(vit j = a[i].begin(); j != a[i].end(); j++) t[++cnt] = find(*j);
		cnt = 0;
		for(vit j = a[i].begin(); j != a[i].end(); j++) {
			cnt++;
			f[t[cnt] + 1] = min(f[t[cnt] + 1], *j);
		}
	}
	rep(i,1,n) if (f[i] < inf) ans = i;
	printf("%d\n",ans);
}