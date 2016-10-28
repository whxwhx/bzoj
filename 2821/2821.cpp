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
const int N = 100010, M = 320;
int a[N], f[M][M], s[M][N], n, c, Q, m, C[N];
void init(){
	rep(i,1,c) s[0][i] = 0;
	int cnt = 0;
	for(int i = 1; i <= n; i += m){
		cnt++;
		int ed = min(i + m - 1, n);
		rep(j,1,c) s[cnt][j] = s[cnt - 1][j];
		rep(j,i,ed) s[cnt][a[j]]++;
	}

	int c0 = 0;
	for(int i = 1; i <= n; i += m){
		c0++; int c1 = c0 - 1;
		rep(j,1,c) C[j] = 0;
		int ans = 0;
		for(int j = i; j <= n; j += m){
			c1++;
			int ed = min(j + m - 1, n);
			rep(k,j,ed) {
				C[a[k]]++;
				if (C[a[k]] > 1){
					if (C[a[k]] & 1) ans--; else ans++;
				}
			}
			f[c0][c1] = ans;
		}
	}
	rep(i,1,c) C[i] = 0;
}
int qry(int l, int r){
	int t1 = (l - 1) / m + 2, t2 = r / m;
	if (t1 > t2){
		int ans = 0;
		rep(i,l,r){
			C[a[i]]++;
			if (C[a[i]] > 1){
				if (C[a[i]] & 1) ans--; else ans++;
			}
		}
		rep(i,l,r) C[a[i]] = 0;
		return ans;
	}else {
		int ans = f[t1][t2];
		int st = (t1 - 1) * m;
		int ed = t2 * m + 1;
		rep(i,l,st) {
			C[a[i]]++; 
			if (C[a[i]] == 1) C[a[i]] += s[t2][a[i]] - s[t1 - 1][a[i]];
			if (C[a[i]] > 1){
				if (C[a[i]] & 1) ans--; else ans++;
			}
		}
		rep(i,ed,r){
			C[a[i]]++; 
			if (C[a[i]] == 1) C[a[i]] += s[t2][a[i]] - s[t1 - 1][a[i]];
			if (C[a[i]] > 1){
				if (C[a[i]] & 1) ans--; else ans++;
			}
		}
		rep(i,l,st) C[a[i]] = 0;
		rep(i,ed,r) C[a[i]] = 0;
		return ans;
	}
}
int main(){
	scanf("%d%d%d",&n,&c,&Q);
	m = sqrt(n);
	if (m < 1) m = 1;
	rep(i,1,n) scanf("%d",&a[i]);
	init();
	int ans = 0;
	rep(i,1,Q){
		int a, b; scanf("%d%d",&a,&b);
		//int L = a, R = b;
		int L = (a + ans) % n + 1, R = (b + ans) % n + 1;
		if (L > R) swap(L, R);
		printf("%d\n",ans = qry(L,R));
	}
	return 0;
}