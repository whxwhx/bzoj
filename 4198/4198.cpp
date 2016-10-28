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
#define max(a,b) ((a) > (b) ? (a) : (b))
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
const int N = 101010;
typedef pair<long long, int> node;
#define mp(a,b) make_pair(a,b)
priority_queue<node> q;
long long w[N];
int main(){
	int n, k; scanf("%d%d",&n,&k);
	rep(i,1,n) scanf("%lld",&w[i]);
	long long ans = 0;
	if (k > 2) while (n % (k - 1) != 1) w[++n] = 0;
	rep(i,1,n) q.push(mp(-w[i], 0));
	while (!q.empty()){
		long long s = 0;
		int d = 0;
		rep(i,1,k) s += q.top().first, d = max(d, -q.top().second), q.pop();
		d++;
		ans += -s;
		if (q.empty()){
			printf("%lld\n",ans);
			printf("%d\n",d);
			break;
		}else q.push(mp(s, -d));
	}
	return 0;
}