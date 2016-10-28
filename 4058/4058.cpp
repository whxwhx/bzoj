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

char s[N];
bool a[N], t1[N], t2[N];

bool check(int l, int r){
	bool flag = true;
	rep(i,l,r) if (a[i]) {flag = false;break;}
	if (flag) return true;

	if ((r- l) & 1) return false;
	if (l >= r) return true;

	int l1 = 0, l2 = 0;
	for(int i = l + 1; i <= r; i += 2) t2[++l2] = a[i];
	for(int i = l + 1; i <  r; i += 2) t1[++l1] = a[i - 1] ^ a[i + 1];
	
	int tt = l;
	rep(i,1,l1) a[tt++] = t1[i];
	int mid = tt - 1;
	rep(i,1,l2) a[tt++] = t2[i];

	return check(l, mid) && check(mid + 1, tt - 1); 
}

void work(){
	scanf("%s",s + 1); int n = strlen(s + 1);
	rep(i,1,n) a[i] = s[i] - '0';
	printf(check(1,n) ? "DIES\n" : "LIVES\n");
}

int main(){
	int T; scanf("%d",&T);
	while (T--) work();
}