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
#define x first
#define y second
typedef pair<int, int> node;
LL operator * (const node &a, const node &b){
	return 1LL * a.x * b.x + 1LL * a.y * b.y;
}
int l = 0;
const int N = 300100;
node a[N];
int main(){
	int n; scanf("%d",&n);
	char c = getchar(); c = getchar();
	rep(i,1,n){
		char c = getchar();
		while (c != 'Q' && c != 'A') c = getchar();
		if (c == 'Q'){
			node d;
			int l, r;
			LL ans = - (1LL << 62);
			scanf("%d%d%d%d",&d.x,&d.y,&l,&r);
			rep(i,l,r) ans = max(ans, d * a[i]);
			printf("%lld\n",ans);
		}else {
			int x, y; scanf("%d%d",&x,&y);
			a[++l] = mp(x,y);
		}
	}
}