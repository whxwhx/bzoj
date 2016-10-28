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
const int N = 100010;
double p[N], f1[N], f2[N];
int main(){
	double ans = 0;
	int n; scanf("%d",&n);
	rep(i,1,n) scanf("%lf",&p[i]);
	rep(i,1,n){
		ans += (3 * f2[i - 1] + 3 * f1[i - 1] + 1) * p[i];
		f2[i] = p[i] * (f2[i - 1] + 2 * f1[i - 1] + 1);
		f1[i] = p[i] * (f1[i - 1] + 1);
	}
	printf("%.1lf\n",ans);
}