#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#define Rep(i,a) for(int i = 0; i < a; i++)
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 262144 + 10;
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
		rep(i,1,l) t = (t << 1) | (k & 1), k >>= 1;
		rev[i] = t;
	}
}
const double pi = acos(-1.0);
void fft(cp *a, int l, int f){
	Rep(i,l) if (rev[i] < i) swap(a[rev[i]], a[i]);
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
	//!
	if (f == -1) Rep(i,l) a[i].r /= l;
}
double a[N], b[N], c[N];
cp A[N], B[N];
int main(){
	int n; scanf("%d",&n);
	int m = 2 * n - 1;
	Rep(i,n) scanf("%lf%lf",&a[i],&b[i]);
	Rep(i,n) if (n - 1 - i < i) swap(a[i], a[n - 1 - i]);

	Rep(i,n) A[i].r = a[i], A[i].i = 0;
	Rep(i,n) B[i].r = b[i], B[i].i = 0;
	init(m);
	fft(A, m, 1), fft(B, m, 1);
	Rep(i,m) A[i] = A[i] * B[i];
	fft(A, m, -1);

	Rep(i,n) c[i] = A[i].r;
	Rep(i,n) if (n - 1 - i < i) swap(c[i], c[n - 1 - i]);
	Rep(i,n) printf("%d\n",(int)(c[i]+0.5));
}