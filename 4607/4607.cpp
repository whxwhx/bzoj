#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define Rep(i,a) for(int i = 0; i < a; i++)
using namespace std;
typedef long long LL;
const int N = 27;
const LL INF = 1LL << 61;
char a[1000010], b[1000010];
int c[N][N], n, C;
LL ans = INF;

int mn[N], d[N], cnt = 0, cir[N], sz[N];
bool vis[N];
void init(){
	rep(i,1,26){ mn[i] = 0; rep(j,1,26) if (!mn[i] || c[i][mn[i]] > c[i][j]) mn[i] = j; }
	rep(i,1,26) d[ mn[i] ]++; 
	memset(vis, false, sizeof(vis)); vis[0] = true;
	rep(i,1,26) if (!vis[i]) {
		int x = i, mx = 0;
		while (!vis[x]) vis[x] = true, mx = max(mx, d[x]), x = mn[x];
		if (mn[i] != i && x == i && mx == 1) {
			cir[x] = ++cnt; x = mn[x]; sz[cnt] = 1;
			while (x != i) cir[x] = cnt, sz[cnt]++, x = mn[x];
		}
	}
}

LL f[2][1 << 14];
int ct[1 << 14];
void dp(){
	int t = 0; int m = 1 << cnt;
	Rep(i,m) f[t][i] = INF; f[t][0] = 0;
	rep(i,1,26){
		Rep(i,m) f[t^1][i] = INF;
		Rep(s,m) if (f[t][s] < INF) {
			rep(j,1,26) {
				int sta = s;
				if (cir[i] && j != mn[i]){ int t = cir[i]; sta |= 1 << (t - 1); }
				if (cir[j] && j != mn[i]){ int t = cir[j]; sta |= 1 << (t - 1); }
				f[t^1][sta] = min(f[t^1][sta], f[t][s] + c[i][j]);
			}
		}
		t ^= 1;
	}
	Rep(i,m) {
		ct[i] = ct[i >> 1] + (i & 1);
		if (i || cnt != 1 || sz[1] < n) ans = min(ans, f[t][i] + C * (cnt - ct[i]) + n);
	}
}



int main(){
 	scanf("%d%d",&n,&C);
	scanf("%s",a + 1); scanf("%s",b + 1); rep(i,1,n) c[a[i] - 'a' + 1][b[i] - 'a' + 1]--;
	rep(i,1,26) rep(j,1,26) if (i != j) c[i][j] += C;
	init(); dp(); printf("%lld\n",ans); return 0;
}