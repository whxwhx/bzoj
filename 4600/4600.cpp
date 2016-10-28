#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a, _b = b; i <= _b; i++)
using namespace std;
int f[21][19][12];
bool vis[100000];
void init(){
	rep(t,1,20){
		rep(i,0,18)
			rep(j,0,11) if (i >= t || j >= t){
				//case1
				rep(p,1,i) {
					int mx = min(t, i / p), sg = 0;
					rep(q,1,mx) sg ^= f[t][i - p * q][j], vis[sg] = true;
				}
				//case2
				rep(p,1,j) {
					int mx = min(t, j / p), sg = 0;
					rep(q,1,mx) sg ^= f[t][i][j - p * q], vis[sg] = true;
				}
				rep(k,0,100000) if (!vis[k]) { f[t][i][j] = k; break; }
				//case1
				rep(p,1,i) {
					int mx = min(t, i / p), sg = 0;
					rep(q,1,mx) sg ^= f[t][i - p * q][j], vis[sg] = false;
				}
				//case2
				rep(p,1,j) {
					int mx = min(t, j / p), sg = 0;
					rep(q,1,mx) sg ^= f[t][i][j - p * q], vis[sg] = false;
				}

		} else f[t][i][j] = f[t - 1][i][j];
	}
}

int a[300100];
void work(){
	int n, mxq; scanf("%d%d",&n,&mxq);
	rep(i,1,n) scanf("%d",&a[i]);
	int ans = 0;
	rep(i,1,n) if (!a[i]){
		int t = i, t1 = 0, t2 = 0;
		while (t % 2 == 0) t >>= 1, t1++;
		while (t % 3 == 0) t /= 3, t2++;
		ans ^= f[mxq][t1][t2];
	}
	if (ans) printf("win\n"); else printf("lose\n");
}

int main(){
	init(); int T; scanf("%d",&T);
	while (T--) work();
}