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

const int N = 200010;
int a[N], b[N], l;

int find(int a){
	int L = 1, R = l + 1;
	while (L + 1 < R){
		int mid = (L + R) >> 1;
		if (b[mid] <= a) L = mid; else R = mid;
	}
	return L;
}

int pre[N], suc[N], pos[N];
bool solve(int l, int r){
	if (l >= r) return true;
	for(int i = l, j = r; i <= j; i++, j--){
		if (pre[i] < l && suc[i] > r) return solve(l, i - 1) && solve(i + 1, r);
		if (pre[j] < l && suc[j] > r) return solve(l, j - 1) && solve(j + 1, r);
	}
	return false;
}

void work(){
	int n; scanf("%d",&n);
	rep(i,1,n) scanf("%d",&a[i]), b[i] = a[i];
	sort(b + 1, b + n + 1);
	l = unique(b + 1, b + n + 1) - b - 1;
	rep(i,1,n) a[i] = find(a[i]);
	rep(i,1,l) pos[i] = 0;
	rep(i,1,n) pre[i] = pos[a[i]], pos[a[i]] = i;
	rep(i,1,l) pos[i] = n + 1;
	dep(i,n,1) suc[i] = pos[a[i]], pos[a[i]] = i;
	printf(solve(1,n) ? "non-boring\n" : "boring\n");
}

int main(){
	int T; scanf("%d",&T);
	while (T--) work();
}