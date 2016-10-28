#include <iostream>
#include <cstdio>
#include <algorithm>
#define Rep(i,a) for(int i=0;i<a;i++)
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N = 32768 + 10, P = 1004535809;
int rev[N], w[2][N];
int pow(int a, int b){
	int w = 1;
	for(;b;b >>= 1, a = 1LL * a * a % P) if (b & 1) w = 1LL * w * a % P;
	return w;
}
void init(int &n){
	int m = 1, l = 0;
	while (m < n) m <<= 1, l++;
	n = m;
	Rep(i,n){
		int t = 0, k = i;
		rep(j,1,l) t = (t << 1) | (k & 1), k >>= 1;
		rev[i] = t;
	}
	w[1][n] = pow(3, (P - 1) >> l);
	dep(i,l - 1,1) w[1][1 << i] = (1LL * w[1][1 << (i + 1)] * w[1][1 << (i + 1)]) % P;
	w[0][n] = pow(w[1][n], P - 2);
	dep(i,l - 1,1) w[0][1 << i] = (1LL * w[0][1 << (i + 1)] * w[0][1 << (i + 1)]) % P;
	rep(i, 1, l) cout <<w[0][1 << i]<<endl;
}
void ntt(int *a, int l, int f){
	if (f == -1) f = 0;
	Rep(i,l) if (rev[i] < i) swap(a[i], a[rev[i]]);
	for(int n = 2; n <= l; n <<= 1){
		int mid = n >> 1, wn = w[f][n];
		for(int i = 0; i < l; i += n){
			int w = 1;
			Rep(j,mid){
				int t1 = a[i + j], t2 = 1LL * a[i + j + mid] * w % P;
				a[i + j] = (t1 + t2) % P;
				a[i + j + mid] = (t1 - t2) % P;
				w = 1LL * w * wn % P;
			}
		}
	}
	int invl = pow(l, P - 2);
	if (!f) Rep(i,l) a[i] = 1LL * a[i] * invl % P;
}


int n, m, X, s, ind[N], d[N], dl = 0;
int powm(int a, int b){
	int w = 1;
	for(;b;b >>= 1, a = 1LL * a * a % m) if (b & 1) w = 1LL * w * a % m;
	return w;
}
void init_p(){
	int g, t = m - 1;
	for(int i = 2; i * i <= t; i++) if (t % i == 0){
		d[++dl] = (m - 1) / i;
		while (t % i == 0) t /= i;
	}
	if (t > 1) d[++dl] = t;
	rep(i,2,m - 1){
		bool flag = true;
		rep(j,1,dl) if (powm(i, d[j]) == 1) {flag = false;break;}
		if (flag) {g = i; break;}
	}
	int k = 1;
	ind[1] = 0;
	rep(i,1,m - 2) k = k * g % m, ind[k] = i;
}
int a[N], w1[N];
int main(){
	scanf("%d%d%d%d",&n,&m,&X,&s);
	int l = 2 * n - 1;
	init(n);
	
}