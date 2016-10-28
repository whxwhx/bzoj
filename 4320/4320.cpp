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
const int M = 550, N = 300010;
int ans[M];
#define min(a,b) ((a) < (b) ? (a) : (b))
int f[N];
int find(int x){
	return f[x] == x ? x : f[x] = find(f[x]);
}
bool vis[N];

pair<int, int> q[100010];
int l = 0;
int main(){
	int n; scanf("%d",&n);
	rep(i,1,M - 1) ans[i] = i - 1;
	rep(i,0,N - 1) f[i] = i;
	rep(i,1,n){
		char c = getchar(); while (c != 'A' && c != 'B') c = getchar();
		if (c == 'A'){
			int x; scanf("%d",&x);
			if(!vis[x]) {
				vis[x] = 1;
				q[++l] = mp(0, x);
			}
			rep(j,1,M - 1) ans[j] = min(ans[j], x % j);
		}else {
			int x; scanf("%d",&x);
			if (x < M) q[++l] = mp(2, ans[x]);
			else q[++l] = mp(1, x);
		}
	}
	rep(i,0,N - 10) if (!vis[i]) f[i] = i + 1;
	dep(i,l,1) if (!q[i].first){
		int x = q[i].second;
		f[x] = x + 1;
	}else if (q[i].first == 1){
		int y = q[i].second, ans = y;
		for(int i = 0; i < N; i += y){
			int t = find(i);
			if (t <= N - 10) ans = min(ans, t % y);
		}
		q[i].second = ans;
	};
	rep(i,1,l) if (q[i].first) printf("%d\n",q[i].second);
}

//窝以前以为>sqrt(n)的办法是要BIT或者线段树的结构上二分一下的。。现在才知道可以直接并查集。。