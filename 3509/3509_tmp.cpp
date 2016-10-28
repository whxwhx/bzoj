#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define Rep(i,a) for(int i = 0; i < a; i++)
using namespace std;
typedef long long LL;
const int N = 100010, M = 65536;
int a[N], cnt[M], c0[M];
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
int rev[M];
void init(int n){
	int m = 1, l = 0;
	while (m < n) m <<= 1, l++;
	n = m;
	rep(i,1,n - 1)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (l - 1));
}
const double pi = acos(-1.0);


void fft(cp *a, int l, int f){
 	Rep(i,l) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for(int n = 2; n <= l; n <<= 1){
		int mid = n >> 1;
		cp wn = (cp){cos(2.0 * pi * f / n), sin(2.0 * pi * f / n)};
		for(int i = 0; i < l; i += n){
			cp w = (cp){1,0};
			Rep(j,mid){
				cp t1 = a[i + j], t2 = a[i + j + mid] * w;
				a[i + j] = t1 + t2;
				a[i + j + mid] = t1 - t2;
				w = w * wn;
			}
		}
	}
	if (f == -1) Rep(i,l) a[i].r /= l;//!
}
int main(){
	int n; scanf("%d",&n);
	rep(i,1,n) scanf("%d",&a[i]);
	int m = 1;
	//int m = sqrt(n) * (log(n) / log(2)) + 1;
	if (m <= 0) m = 1;
	init(M);
	for (int t = 1; t <= n; t += m){
		Rep(i,M) dl[i].i = dr[i].i = dl[i].r = dr[i].r = 0;
		rep(i,1,t - 1) dl[a[i]].r += 1;
		rep(i, t + m, n) dr[a[i]].r += 1;
		
		if (t == 3) cout <<dl[3].r<<' '<<dr[3].r<<endl;
		fft(dl, M, 1), fft(dr, M, 1);
		Rep(i,M) dl[i] = dl[i] * dr[i];
		fft(dl, M, -1);
		if (t == 3) cout <<dl[6].r<<endl;
		
		Rep(i,M) cnt[i] = (int)(dl[i].r + 0.5);
		rep(i,t,t + m - 1) ans += cnt[a[i] << 1];
		
		Rep(i,M - 1) c0[i] = 0; 
		rep(i,t,t + m - 1){
			rep(j,i + 1, t + m - 1){
				int k = (a[i] << 1) - a[j];
				if (0 <= k && k < M) ans += c0[k];
			}
			c0[a[i]]++;
		}
	}
	printf("%lld\n",ans);
	return 0;
}