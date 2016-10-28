#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define Rep(i,a) for(int i = 0; i < a; i++)
const int N = 262144 + 10;
using namespace std;
const double pi = acos(-1.0);
struct cp{
	double r, i;
};
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
void init(int &n){
	int m = 1, l = 0;
	while (m < n) m <<= 1, l++;
	n = m;
	Rep(i,n){
		int t = 0, k = i;
		rep(j,1,l) t = (t << 1) | (k & 1), k >>= 1;
		rev[i] = t;
	}
}
void fft(cp *a, int l, int f){
	Rep(i,l) if (rev[i] < i) swap(a[rev[i]], a[i]);
	for(int n = 2; n <= l; n <<= 1){
		int mid = n >> 1;
		cp wn = (cp){cos(2.0 * pi * f / n), sin(2.0 * pi * f / n)};
		for(int i = 0; i < l; i += n){
			cp w = (cp){1, 0};
			Rep(j,mid){
				cp t1 = a[i + j], t2 = a[i + j + mid] * w;
				a[i + j] = t1 + t2;
				a[i + j + mid] = t1 - t2;
				w = w * wn;
			}
		}
	}
	if (f == -1) Rep(i,l) a[i].r /= l;
}
cp a[N], b[N], q[N];
double ans[N];
int main(){	
	int n; scanf("%d",&n);int t1 = n;
	Rep(i,n) scanf("%lf",&q[i].r), b[i] = q[i];
	
	n = n * 2 - 1;
	init(n);
	rep(i, 1, t1 - 1) a[i].r = (double)1.0 / i / i, a[i].i = 0;
	fft(a, n, 1);fft(q, n, 1);
	Rep(i,n) a[i] = a[i] * q[i];
	fft(a, n, -1);
	Rep(i,t1) ans[i] = a[i].r;

	Rep(i,n) a[i].r = a[i].i = 0;
	Rep(i,n) q[i].r = q[i].i = 0;

	Rep(i,t1) q[i] = b[i];
	Rep(i,t1) if (t1 - 1 - i < i) swap(q[i], q[t1 - 1 - i]);
	rep(i, 1, t1 - 1) a[i].r = (double)1.0 / i / i, a[i].i = 0;
	fft(a, n, 1); fft(q, n, 1);
	Rep(i,n) a[i] = a[i] * q[i];
	fft(a, n, -1);
	Rep(i,t1) if (t1 - 1 - i < i) swap(a[i], a[t1 - 1 - i]);

	Rep(i,t1) ans[i] -= a[i].r;
	Rep(i,t1) printf("%.3lf\n",ans[i]);
	return 0;
}