#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = (a); i <= (b); i++)
using namespace std;
typedef long long LL;
const int N = 500100;
char s[N];

int p[N], a[N];
LL d[N], d1[N];
const LL inf = 1LL << 60;
bool vis[N];
int b[N];
void trans(int &m, int m1){
	int n = m; m = m1;
	rep(i,0,m - 1) d1[i] = inf;
	rep(i,0,n - 1) d1[d[i] % m] = min(d1[d[i] % m], d[i]);
	rep(i,0,m - 1) vis[i] = false;
	rep(i,0,m - 1) if (!vis[i]){
		int j = i, bl = 0;
		while (!vis[j]){
			vis[j] = true; b[++bl] = j;
			j = (j + n) % m;
		}
		LL mn = inf;
		rep(i,1,bl){
			int x = b[i];
			mn = min(mn, d1[x]), d1[x] = mn;
			mn += n;
		}
		rep(i,1,bl){
			int x = b[i];
			mn = min(mn, d1[x]), d1[x] = mn;
			mn += n;
		}
	}
	rep(i,0,m - 1) d[i] = d1[i];
}

typedef pair<LL, int> node;
node q[N * 2];
#define mp(a,b) make_pair(a,b)
void solve(int det, int n, int m){
	rep(i,0,m - 1) vis[i] = false;
	rep(i,0,m - 1) if (!vis[i]){
		int j = i, bl = 0;
		while (!vis[j]){
			vis[j] = true; b[++bl] = j;
			j = (j + det) % m;
		}
		int l = 0, r = 0;
		rep(i,1,bl){
			int x = b[i];
			while (l < r && i - q[l].second >= n) l++;
			if (l < r) d[x] = min(d[x], q[l].first + 1LL * i * det + m);
			
			LL F = d[x] - 1LL * i * det;
			while (l < r && q[r - 1].first >= F) r--;
			q[r++] = mp(F, i);
		}
		rep(i,bl + 1, bl + bl){
			int x = b[i - bl];
			while (l < r && i - q[l].second >= n) l++;
			if (l < r) d[x] = min(d[x], q[l].first + 1LL * i * det + m);
			
			LL F = d[x] - 1LL * i * det;
			while (l < r && q[r - 1].first >= F) r--;
			q[r++] = mp(F, i);
		}
	}
}

void work(){
	int n; LL w; scanf("%d%lld",&n,&w);
	scanf("%s",s + 1);
	int j; p[1] = 0;
	rep(i,2,n){
		j = p[i - 1];
		while (j && s[j + 1] != s[i]) j = p[j];
		if (s[j + 1] == s[i]) p[i] = j + 1; else p[i] = 0;
	}

	int m, al = 0;	
	j = p[n];
	while (j) a[++al] = n - j, j = p[j];
	a[++al] = n;
	m = a[1];

	rep(i,0,m - 1) d[i] = inf;
	d[n % m] = n;

	for(int i = 2; i <= al; i++){
		trans(m, a[i]);
		if (i == al) break;
		int det = a[i + 1] - a[i];
		i++;
		int cnt = 2;
		while (i < al && a[i + 1] - a[i] == det) i++, cnt++;
		solve(det, cnt, m);
	}
	
	LL ans = 0;
	rep(i,0,m - 1) if (w >= d[i]) ans += (w - d[i]) / m + 1;
	printf("%lld\n",ans);
}
int main(){
	int T; scanf("%d",&T);
	while (T--) work();	
}