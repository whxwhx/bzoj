#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 100010;
typedef pair<int, int> node;
node a[N];
int a1[N];
int main(){
    int n; scanf("%d",&n);
    rep(i,1,n) scanf("%d",&a[i].first), a[i].second = i;
    sort(a + 1, a + n + 1);
	double ans = 0;
    rep(i,1,n) 
		rep(j,i + 1,n) if (a[i].second > a[j].second) a1[j - i + 1]++;
	rep(i,1,n) ans += 2.0 * a1[i] / i;
    printf("%.6lf\n",ans);
}