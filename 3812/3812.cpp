#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N = 15, M = 1000000000 + 7;
int e_in[1 << 15], e_out[1 << 15], a[N * N], b[N * N];
int f[1 << 15], g[1 << 15], ways[1 << 15], h[1 << 15], pow[N * N], cnt[1 << 15];
int main(){
	int n, m; scanf("%d%d",&n,&m);
	rep(i,1,m){
		scanf("%d%d",&a[i],&b[i]);
		a[i]--, b[i]--;
		e_out[1 << a[i]] |= 1 << b[i];
		e_in [1 << b[i]] |= 1 << a[i];
	}
	
	pow[0] = 1;
	rep(i,1,N * N) pow[i] = (pow[i - 1] << 1) % M;

	int l = (1 << n) - 1;
	cnt[0] = 0;
	rep(i,1,l) cnt[i] = cnt[i ^ (i & (-i))] + 1;

	h[0] = 0;
	rep(i,1,l){
		
		int u = i & (-i), v = i ^ u;
		h[i] = h[v] + cnt[e_in[u] & i] + cnt[e_out[u] & i];

		g[i] = 0;
		for(int j = v; j; j = (j - 1) & v)
			g[i] -= 1LL * f[i ^ j] * g[j] % M, g[i] %= M;

		ways[i] = 0;
		for(int j = i - 1; j; j = (j - 1) & i){
			int u = (i ^ j) & (-(i ^ j)), v = j ^ u;
			ways[j] = ways[v] + cnt[e_out[u] & j] - cnt[e_in[u] & (i ^ j)];
		}

		f[i] = pow[h[i]];
		for(int j = i; j; j = (j - 1) & i){
			f[i] -= 1LL * pow[ways[j]] * pow[h[i ^ j]] % M * g[j] % M, f[i] %= M;
		}
		
		g[i] += f[i], g[i] %= M;
	}
	if (f[l] < 0) f[l] += M;
	printf("%d\n",f[l]);
	return 0;
}