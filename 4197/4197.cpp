#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b )for(int i = a; i >= b; i--)
using namespace std;
int a[258], p[8], P, f[2][258][258], g[258][258];
int pow(int a, int b){
	int w = 1;
	for(; b; b >>= 1, a = 1LL * a * a % P) if (b & 1) w = 1LL * w * a % P;
	return w;
}
int pri[510], pl = 0, n;
void prim(){
	rep(i,20,n){
		bool flag = 1;
		rep(j,2,i - 1) if (i % j == 0) {flag = 0; break;}
		if (flag) pri[++pl] = i;
	}
}
int fac[510];
int main(){
	scanf("%d%d",&n,&P);
	p[0] = 2, p[1] = 3, p[2] = 5, p[3] = 7, p[4] = 11, p[5] = 13, p[6] = 17, p[7] = 19;
	rep(i,2,n){
		int t = i, t1 = 0;
		rep(j,0,7) if (t % p[j] == 0){
			t1 += 1 << j;
			while (t % p[j] == 0) t /= p[j];
		}
		if (t == 1) a[t1]++;
		fac[i] = t1;
	}
	rep(i,0,7)
		rep(j,0,255) 
			if (j >> i & 1) a[j] += a[j ^ (1 << i)];
	rep(j,0,255) a[j] = pow(2, a[j]);
	rep(i,0,7)
		rep(j,0,255) 
			if (j >> i & 1) a[j] -= a[j ^ (1 << i)], a[j] %= P;
	rep(i,0,255) rep(j,0,255) if ((i & j) == 0) f[0][i][j] = 1LL * a[i] * a[j] % P;
	prim();
	int i = 0, ans = 0;
	rep(t,1,pl){
		int bp = pri[t];
		i ^= 1;
		//A
		rep(j,0,255) rep(k,0,255) g[j][k] = f[i ^ 1][j][k]; 
		rep(j,1,n/bp){
			int z = fac[j];
			dep(i,255,0) {
				int t = 255 ^ (i | z);
				for(int j = t; true; j = (j - 1) & t){
					g[i | z][j] += g[i][j], g[i | z][j] %= P;
					if (j == 0) break;
				}
			}
		}
		rep(j,0,255) rep(k,0,255) f[i][j][k] = g[j][k];
		//B
		rep(j,0,255) rep(k,0,255) g[j][k] = f[i ^ 1][j][k];
		rep(j,1,n/bp){
			int z = fac[j];
			dep(i,255,0){
				int t = 255 ^ (i | z);
				for(int j = t; true; j = (j - 1) & t){
					g[j][i | z] += g[j][i], g[j][i | z] %= P;
					if (j == 0) break;
				}
			}
		}
		rep(j,0,255) rep(k,0,255) f[i][j][k] += g[j][k], f[i][j][k] %= P;
		//neither
		rep(j,0,255) rep(k,0,255) f[i][j][k] -= f[i ^ 1][j][k], f[i][j][k] %= P;
	}
	rep(j,0,255) rep(k,0,255) ans += f[i][j][k], ans %= P;
	if (ans < 0) ans += P;
	printf("%d\n",ans);
}