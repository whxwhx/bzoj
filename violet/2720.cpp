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
const int N = 310;
int a[N];
double ans = 0;
int main(){
	int n; scanf("%d",&n);
	rep(i,1,n) scanf("%d",&a[i]);
	sort(a + 1, a + n + 1);
	int t, j;
	rep(i,1,n){
		rep(k,1,n){
			if (a[i] != a[i - 1]) j = t = i; else  j = t;
			j--;
			int t1 = n - 1;
			double tmp = 1.0/n;
			ans += tmp;
			dep(t,k - 1,1){
				tmp *= double(j) / t1;
				ans += tmp;
				t1--, j--;
				if (j == 0) break;
			}
		}
	}
	printf("%.2lf\n",ans);
}