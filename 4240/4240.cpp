#include <iostream>
#include <cstdio>
#include <algorithm>
#define min(a,b) ((a) < (b) ? (a) : (b))
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N = 300000 + 10;
typedef pair<int, int> node;
#define h first
#define num second
int s[N], n;
void add(int x){
	for(; x <= n; x += (-x) & x) s[x]++;
}
int sum(int x){
	int ans = 0;
	for(; x; x -= (-x) & x) ans += s[x];
	return ans;
}
node a[N];
typedef long long LL;
int main(){
	LL ans = 0;
	scanf("%d",&n);
	rep(i,1,n) scanf("%d",&a[i].h), a[i].h = -a[i].h, a[i].num = i;
	sort(a + 1, a + n + 1);
	a[n + 1].h = 0;
	int tt = 0;
	rep(i,1,n){
		int t = sum(a[i].num);
		ans += min(t, tt - t);
		if (a[i + 1].h != a[i].h) {
			dep(j,i,1) {if (a[j].h == a[i].h) add(a[j].num); else break;}
			tt = i;
		}
	}
	printf("%lld\n",ans);
	return 0;
}