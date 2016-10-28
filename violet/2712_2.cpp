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
int n;
double r;
LL x, y;
LL cl(LL a, LL b){
	return a / b + (a % b ? 1 : 0);
}
void solve(LL a, LL b, LL c, LL d){
	if (a == 0){
		x = 1, y = d / c + 1;
	}else{
		LL t = a / b;
		a -= b * t, c -= d * t;
		if (a % b == 0){
			x = 1, y = d / c + 1;
		}else solve(d, c, b, a), swap(x, y), x += t * y;
	}
	cout <<a<<' '<<b<<' '<<c<<' '<<d<<endl;
}
LL gcd(LL a, LL b){
	if (a == 0) return b;
	return b ? gcd(b, a % b) : a;
}
void work(){
	rep(i,1,n + 1) r *= 10;
	LL a, b, c, d;
	a = (LL)r - 5, c = (LL)r + 5;if (a < 0) a = 0;
	b = 1; rep(i,1,n + 1) b *= 10;
	d = b;
	LL t = gcd(a, b); a /= t, b /= t;
	solve(c,d,b,a); swap(x,y);
	printf("%lld\n",b < y ? b : y);
}
int main(){
	while (scanf("%d%lf",&n,&r) == 2) work();
}