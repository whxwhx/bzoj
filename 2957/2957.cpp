#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = (a); i <= (b); i++)//(a)!
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
class frac{ int a, b; };// a / b
inline operator < (const frac &a, const frac &b) { return 1LL * a.a * b.b < 1LL * b.a * a.b; }
int s[N], a; frac b, mx[N];
bool modi(int x, int l, int r){
	if (!s[x]) s[x] = 1; if (l == r) { mx[x] = b; return true; }
	frac t = 
}
int main(){
	int n, m; scanf("%d%d",&n,&m);
	rep(i,1,m){
		int x, y; scanf("%d%d",&x,&y); a = x; b = (frac){y, x};
		modi(1, 1, n); printf("%d\n",s[1]);
	}
	return 0;
}