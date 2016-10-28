#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define Rep(i,a) for(int i = 0; i < a; i++)
using namespace std;
typedef long long LL;
const int N = 100010, M = 65536;
int a[N], cnt[M], c0[M], c1[M];
LL ans = 0;

struct cp{
	double r, i;
}dl[M], dr[M];
cp operator + (const cp &a, const cp &b){
	return (cp){a.r + b.r, a.i + b.i};
}
cp operator - (const cp &a, const cp &b){
	return (cp){a.r - b.r, a.i - b.i};
}
cp operator * (const cp &a, const cp &b){
	return (cp){a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r};
}
int rev[N];
void init(){
	int l = 16;
	rep(i,1,M - 1) 
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (l - 1));
}
const double pi = acos(-1.0);
void fft(cp *a, int l, int f){
	Rep(i,l) if (rev[i] < i) swap(a[i], a[rev[i]]);
	for(int n = 2; n <= l; n <<= 1){
		int mid = n >> 1;
		cp wn = (cp){cos(2 * pi * f / n), sin(2 * pi * f / n)};
		for(int i = 0; i < l; i += n){
			cp w = (cp){1, 0};
			Rep(j,mid){
				cp t0 = a[i + j], t1 = w * a[i + j + mid];
				a[i + j] = t0 + t1;
				a[i + j + mid] = t0 - t1;
				w = w * wn;
			}
		}
	}
	if (f == -1) Rep(i,l) a[i].r /= l;
}

int main(){
	int n; scanf("%d",&n);
	rep(i,1,n) scanf("%d",&a[i]);
	int m = sqrt(n) * (log(n) / log(2))+ 1;
	if (m <= 0) m = 1;
	if (m > n) m = n;
	init();
	for (int t = 1; t <= n; t += m){
		Rep(i,M) dl[i].i = dr[i].i = dl[i].r = dr[i].r = 0, c0[i] = c1[i] = 0;
		rep(i,1,t - 1) dl[a[i]].r += 1, c0[a[i]]++;
		rep(i, t + m, n) dr[a[i]].r += 1, c1[a[i]]++;
		
		fft(dl, M, 1), fft(dr, M, 1);
		Rep(i,M) dl[i] = dl[i] * dr[i];
		fft(dl, M, -1);
		
		Rep(i,M) cnt[i] = (int)(dl[i].r + 0.5);
		int ed = min(t + m - 1, n);
		rep(i,t,ed) ans += cnt[a[i] << 1];

		rep(i,t,ed){
			rep(j,i + 1, ed){
				int k = (a[i] << 1) - a[j];
				if (0 <= k && k < M) ans += c0[k];
				k = (a[j] << 1) - a[i];
				if (0 <= k && k < M) ans += c1[k];
			}
			c0[a[i]]++;
		}
	}
	printf("%lld\n",ans);
	return 0;
}