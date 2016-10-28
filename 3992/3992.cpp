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
	int l = 2 * (m - 1) - 1;
	init(l);
	init_p();
	if (X == 0) X = -1; else X = ind[X];
	int cnt0 = 0;
	rep(i,1,s){
		int tmp; scanf("%d",&tmp); tmp %= m;
		if (tmp == 0) cnt0++; else a[ind[tmp]]++;
	}

	if (X != -1){
		w1[0] = 1;
		for(int i = n; i; i >>= 1){
			ntt(a, l, 1);
			if (i & 1){ 
				ntt(w1, l, 1);
				Rep(i,l) w1[i] = 1LL * w1[i] * a[i] % P;
				ntt(w1, l, -1);
				rep(i, m - 1, l - 1) w1[i - (m - 1)] = (w1[i - (m - 1)] + w1[i]) % P, w1[i] = 0;
			}
			Rep(i,l) a[i] = 1LL * a[i] * a[i] % P;
			ntt(a, l, -1);
			rep(i, m - 1 ,l - 1) a[i - (m - 1)] = (a[i - (m - 1)] + a[i]) % P, a[i] = 0;
	}

		w1[X] = (w1[X] + P) % P;
		printf("%d\n",w1[X]);//ans was in w1 not a
	} else {
		int ans = (pow(n, s) - pow(n, s - cnt0)) % P;
		if (ans < 0) ans += P;
		printf("%d\n",ans);
	}
}
/*
	有两个易错点:
		1.答案是w而不是a
		2.不能直接把0~m-2项之外的直接清0, 要mod m-1，也就是把它们加到 i - (m - 1) 上
*/