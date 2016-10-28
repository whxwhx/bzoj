#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define dep(i,a,b) for(int i = a; i >= b; i--)
#define rep(i,a,b) for(int i = a; i <= b; i++)
const int N = 100010;
char t[N]; 
int l = 0, a[N], b[N], h[3][N], M[3], s[N], inv[3][N];

int get(int a,int b, int t){
	int k = h[t][b] - h[t][a - 1];
	k = 1LL * k * inv[t][a - 1] % M[t];
	if (k < 0) k += M[t];
	return k;
}
bool cp(int a, int b, int c, int d, int t){
	return get(a,b,t) == get(c,d,t);
}
bool cmp(int a, int b, int c, int d){
	return cp(a,b,c,d,0) && cp(a,b,c,d,1) && cp(a,b,c,d,2);
}
void init(){
	M[0] = 999133, M[1] = 996803, M[2] = 996763;
	rep(i,0,2){
		h[i][0] = 0;
		int t = 1;
		rep(j,1,l) h[i][j] = (h[i][j - 1] + 1LL * s[j] * t) % M[i], t = t * 29 % M[i];
	}
	inv[0][0] = inv[1][0] = inv[2][0] = 1;
	inv[0][1] = 757963, inv[1][1] = 928058, inv[2][1] = 240598;
	rep(i,0,2)
		rep(j,2,l) inv[i][j] = (1LL * inv[i][j - 1] * inv[i][1]) % M[i];
}
int n;
int d[210][210];
void build(){
	rep(i,1,n)
		rep(j,1,n) {
			d[i][j] = b[j] - a[j] + 1;
			if (i == j){
				int t = a[j], cnt = b[j] - a[j] + 1;
				dep(k,b[i],a[i] + 1){
					cnt--;
					if (cmp(k, b[i], a[j], t)) d[i][j] = cnt;
					t++;
				}
			}else if (b[i] - a[i] < b[j] - a[j]){
				int t = a[j], cnt = b[j] - a[j] + 1;
				dep(k,b[i],a[i]){
					cnt--;
					if (cmp(k, b[i], a[j], t)) d[i][j] = cnt;
					t++;
				}
			}else{
				int t = b[i], cnt = b[j] - a[j] + 1;
				rep(k,a[j],b[j]){
					cnt--;
					if (cmp(t, b[i], a[j], k)) d[i][j] = cnt;
					t--;
				}
			}
		}
}

int m;
typedef long long LL;
const LL inf = 1LL << 59;
LL f[31][210][210], g1[210][210], g[210][210];
#define min(a,b) ((a) < (b) ? (a) : (b))
LL ans;
void work(){
	rep(i,1,n) rep(j,1,n) f[0][i][j] = d[i][j];
	rep(i,1,30){
		rep(j,1,n) rep(k,1,n){
			f[i][j][k] = inf;
			rep(t,1,n) f[i][j][k] = min(f[i][j][k], f[i - 1][j][t] + f[i - 1][t][k]);
		}
	}

	m--;
	rep(i,1,n) rep(j,1,n) if (i == j) g[i][j] = b[i] - a[i] + 1; else g[i][j] = inf;
	dep(i,30,0)if (m >> i & 1){
		rep(j,1,n) rep(k,1,n) {
			g1[j][k] = inf;
			rep(t,1,n) g1[j][k] = min(g1[j][k], g[j][t] + f[i][t][k]);
		}
		rep(j,1,n) rep(k,1,n) g[j][k] = g1[j][k];
	}

	ans = inf;
	rep(i,1,n) rep(j,1,n) ans = min(ans, g[i][j]);
}

int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,n){
		scanf("%s",t); int tl = strlen(t);
		a[i] = l + 1;
		rep(j,0,tl - 1) s[++l] = t[j] - 'a';
		b[i] = l;
	}
	init();
	build();
	work();
	printf("%lld\n",ans);
}