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
const int N = 100000, inf = 1000000001LL;
int f[N], mx;
void upd(int a){
	int l = 0, r = mx + 1;
	while (l + 1 < r){
		int mid = (l + r) >> 1;
		if (f[mid] < a) l = mid; else r = mid;
	}
	if (l + 1 > mx) mx = l + 1;
	f[l + 1] = a;
}
int main(){
	f[0] = -inf;
	mx = 0;
	int n, s = 0; scanf("%d",&n);
	rep(i,1,n){
		char c = getchar();
		while (c != 'K' && c != 'N') c = getchar();
		if (c == 'K'){
			int a; scanf("%d",&a);
			upd(a - s);
		}else s++;
	}
	printf("%d\n",mx + s);
}