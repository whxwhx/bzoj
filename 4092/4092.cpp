#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
typedef pair<int, int> point;
const int N = 110;
point a[N], b[N];
int c[N];
#define x first
#define y second
#define mp(a,b) make_pair(a,b)
int f[N][N][N], s[N];
const int inf = 1000000000;

int R;
bool check(point a, point b){
	return 1LL * (a.x - b.x) * (a.x - b.x) + 1LL * (a.y - b.y) * (a.y - b.y) <= 1LL * R * R;
}
bool d(int x){
	return b[x].y > R;
}
#define min(a,b) ((a) < (b) ? (a) : (b))
int main(){
	int n, m; scanf("%d%d%d",&n,&m,&R);
	rep(i,1,n) scanf("%d%d",&a[i].x,&a[i].y);
	sort(a + 1, a + n + 1);
	rep(i,1,m) scanf("%d%d%d",&b[i].x,&b[i].y,&c[i]);
	
	rep(j,0,m) rep(k,0,m) f[0][j][k] = inf; f[0][0][0] = 0;
	int ans0 = n;
	rep(i,1,n){
		rep(j,0,m) rep(k,0,m) f[i][j][k] = inf;

		rep(j,1,m){
			s[j] = inf;
			if (d(j))
				rep(k,0,m) s[j] = min(s[j], f[i - 1][j][k]);
			if (!d(j))
				rep(k,0,m) s[j] = min(s[j], f[i - 1][k][j]);
		
		}

		bool flag = true;
		rep(j,1,m) if (check(a[i], b[j])){
			flag = false;
			if (d(j)){
				f[i][j][0] = min(f[i][j][0], f[i - 1][j][0]);
				rep(k,0,m) f[i][j][0] = min(f[i][j][0], f[i - 1][k][0] + c[j]);
				
				rep(k,1,m) if (!d(k))
					f[i][j][k] = min(f[i][j][k], f[i - 1][j][k]),
					f[i][j][k] = min(f[i][j][k], s[k] + c[j]);
			}else{
				f[i][0][j] = min(f[i][0][j], f[i - 1][0][j]);
				rep(k,0,m) f[i][0][j] = min(f[i][0][j], f[i - 1][0][k] + c[j]);

				rep(k,1,m) if (d(k))
					f[i][k][j] = min(f[i][k][j], f[i - 1][k][j]),
					f[i][k][j] = min(f[i][k][j], s[k] + c[j]);
			}
		}

		if (flag) {
			ans0--; 
			rep(j,0,m) rep(k,0,m) f[i][j][k] = f[i - 1][j][k];
		}
	}

	int ans = inf;
	rep(i,0,m) rep(j,0,m) ans = min(ans, f[n][i][j]);
	printf("%d\n",ans0);
	printf("%d\n",ans);
	return 0;
}