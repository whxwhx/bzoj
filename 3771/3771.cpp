#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define max(a,b) ((a) > (b) ? a : b)
#define Rep(i,a) for(int i = 0; i < a; i++)
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
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
const int N = 131072 + 10;
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
	if (f == -1) Rep(i,l) a[i].r /= l;
}

cp a[N], a2[N], a3[N], b1[N];
int A1[N], A2[N], A3[N], B[N], C[N], ans[N], T[N], mx = 0;
int main(){
	int n; scanf("%d",&n);	
	rep(i,1,n){
		int t; scanf("%d",&t);
		a[t].r++; mx = max(mx, t);
	}
	int l = mx * 3 + 1;
	init(l);

	Rep(i,l) A1[i] = (int)(a[i].r + 0.5);
	Rep(i,mx + 1) B[i * 2] = A1[i] * A1[i], C[i * 3] = A1[i] * A1[i] * A1[i];
	
	fft(a, l, 1);
	Rep(i,l) a2[i] = a[i] * a[i];
	Rep(i,l) a3[i] = a2[i] * a[i];
	fft(a2, l, -1), fft(a3, l, -1);
	Rep(i,l) A2[i] = (int)(a2[i].r + 0.5), A3[i] = (int)(a3[i].r + 0.5);
	//cout <<A2[4]<<endl;

	Rep(i,l) ans[i] = A1[i];
	Rep(i,l) ans[i] += (A2[i] - B[i]) >> 1;

	Rep(i,l) b1[i].r = B[i];
	fft(b1, l, 1);
	Rep(i,l) b1[i] = b1[i] * a[i];
	fft(b1, l, -1);
	Rep(i,l) T[i] = (int)(b1[i].r + 0.5);
	Rep(i,l) ans[i] += (A3[i] - 3 * T[i] + (C[i] << 1)) / 6;
	Rep(i,l) if (ans[i]) printf("%d %d\n",i,ans[i]);
	return 0;
}
//|!A1 AND !A2 AND !A3| = |U| - |A1| - |A2| - |A3| + |A1 AND A2| + |A1 AND A3| + |A2 AND A3| - |A1 AND A2 AND A3|