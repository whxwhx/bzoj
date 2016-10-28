#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i = a, _b = b; i <= _b; i++)
#define dep(i,a,b) for(int i = a, _b = b; i >= _b; i--)
using namespace std;
typedef long long LL;
const int N = 110, L = 1010, M = N * L * 2;

char s[M], a[M * 6]; 
int len[N], S[N], n;

namespace SA{
	int sa[M], x[M], y[M], c[M], m, l;
	
	void calc(int *x, int *y){
		rep(i,0,m) c[i] = 0;
		rep(i,1,l) c[x[y[i]]]++;
		rep(i,1,m) c[i] += c[i - 1];
		dep(i,l,1) sa[ c[x[y[i]]]-- ] = y[i];
	}
	void buildsa(int *x, int *y){
		m = 30; rep(i,1,l) x[i] = s[i] - 'a', y[i] = i; calc(x, y);
		for(int k = 1; k <= l; k <<= 1){
			int p = 0;
			rep(i,l - k + 1,l) y[++p] = i;
			rep(i,1,l) if (sa[i] - k > 0) y[++p] = sa[i] - k;
			calc(x, y); swap(x, y);
			x[sa[1]] = p = 1;
			rep(i,2,l) 
				x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? p : ++p;
			m = p; if (m >= l) break;
		}
	}

	int rk[M], h[M], mn[M][19], bin[1 << 19];

	void geth(){
		rep(i,1,l) rk[sa[i]] = i;
		int k = 0;
		rep(i,1,l) {
			if (k) k--;
			if (rk[i] > 1){
				int j = sa[ rk[i] - 1 ];
				while (s[i + k] == s[j + k]) k++;
				h[ rk[i] ] = k;
			}
		}

		rep(i,1,l) mn[i][0] = h[i];
		rep(j,1,18) rep(i,1,l) if (i + (1 << j) - 1 <= l) mn[i][j] = min(mn[i][j - 1], mn[i + (1<<(j-1))][j - 1]);
		rep(j,0,17) rep(i,(1<<j),(1<<(j+1))) bin[i] = j;
	}

	int lcp(int a, int b){
		if (a == b) return (l - a + 1);
		a = rk[a], b = rk[b]; if (a > b) swap(a, b); a++; //注意查的时候a > b的时候要交换a和b！
		int j = bin[ b - a + 1 ]; return min(mn[a][j], mn[b - (1 << j) + 1][j]);
		/*int mn = L;
		rep(i,a,b) mn = min(mn, h[i]);
		return mn; */
	}

	int LCP;
	bool same(int x1, int x2, int a, int b, int L){
		x1 = S[x1 - 1] + len[x1] + 1 + (len[x1] - a + 1); x2 = S[x2 - 1] + b;
		LCP = lcp(x1, x2);
		if ( LCP >= L) return true; else return false;
	}
}

namespace G{
	struct edge{ int to, pre, c; }e[M * N]; int u[M], l = 0, d[M];
	void ins(int a, int b, int c){ e[++l] = (edge){b, u[a], c}, u[a] = l; /*cout <<a<<' '<<b<<' '<<c<<endl;*/}
	#define v e[i].to
	#define ec e[i].c
	#define reg(i,x) for(int i = u[x]; i; i = e[i].pre)

	inline int id(int a, int b, bool f) { return a * L * 2 + b * 2 + f + 1; }

	int T;
	void buildgraph(){
		T = id(n, len[n], 1) + 1;
		rep(i,1,n) {
			rep(j,1,len[i]){
				int x = id(i, j, 0);
				rep(k,1,n){
					int t = min(j, len[k]);
					if (SA::same(i, k, j, 1, t)) {
						if (j < len[k]) ins(x, id(k, len[k] - t, 1), t << 1);
						else if (j == len[k]) ins(x, 1, t << 1);
						else ins(x, id(i, j - t, 0), t << 1);
					} else { int t = SA::LCP; ins(x, T, t << 1); }
				}

				x = id(i, j, 1);
				rep(k,1,n){
					int t = min(j, len[k]);
					if (SA::same(k, i, len[k], len[i] - j + 1, t)){
						if (j < len[k]) ins(x, id(k, len[k] - t, 0), t << 1);
						else if (j == len[k]) ins(x, 1, t << 1);
						else ins(x, id(i, j - t, 1), t << 1);
					}else { int t = SA::LCP; ins(x, T, t << 1); }
				}
			}
		}

		rep(i,1,n) ins(1, id(i, len[i], 0), 0), ins(1, id(i, len[i], 1), 0);
		rep(i,1,n) {
			if (SA::same(i, i, len[i], 1, len[i])) ins(0, 1, len[i]);
			rep(j,1,len[i]) {
				//f == 0
				if (SA::same(i, i, len[i], j + 1, len[i] - j)) ins(0, id(i, j, 0), len[i] - j);
				//f == 1
				if (SA::same(i, i, len[i] - j, 1, len[i] - j)) ins(0, id(i, j, 1), len[i] - j);
			}
		}
	}

	int q[M]; LL f[M];

	void print(int x){ rep(i,1,n) rep(j,1,len[i]) rep(f,0,1) if (id(i,j,f) == x) cout <<i<<' '<<j<<' '<<f<<endl; }

	void bfs(){
		int l = 0, r = 0; q[r++] = 0;
		while (l < r){
			int x = q[l++];
			reg(i,x) { d[v] ++; if (d[v] == 1) q[r++] = v; } //bfs的时候应该用inq判而不能用vis！
		}
		l = 0, r = 0; q[r++] = 0;
		while (l < r){
			int x = q[l++];
			reg(i,x) { d[v]--; if (!d[v]) q[r++] = v; }
		}
		dep(i,r - 1,0) {
			int x = q[i]; 
			reg(i,x) if (d[v]) { printf("Infinity\n"); return; } else f[x] = max(f[x], f[v] + ec);
		}
		//print(5051);
		printf("%lld\n",f[0]);
	}
}

int p[M * 6];

int main(){
	scanf("%d",&n);
	if (n == 1){
		scanf("%s",a+1); int l = strlen(a + 1), mx = 0, j = 0;
		rep(i,1,l) a[l + i] = a[i], a[2 * l + i] = a[i];
		l *= 3;
		dep(i,l,1) a[i << 1] = a[i]; l <<= 1;
		rep(i,1,l) if (i & 1) a[i] = '#';

		int ans = 0;
		rep(i,1,l){
			if (i < mx) p[i] = min(mx - i, p[2 * j - i]); else p[i] = 0;
			while (a[i - p[i]] == a[i + p[i]]) p[i]++;
			if (i + p[i] > mx) mx = i + p[i], j = i;
			if (p[i] - 1 > ans) ans = p[i] - 1;
		}

		if (ans >= l / 3) printf("Infinity\n"); else printf("%d\n",ans);
		return 0;
	}
	rep(i,1,n){
		scanf("%s",a + 1); len[i] = strlen(a + 1);
		rep(j,1,len[i]) s[++SA::l] = a[j]; s[++SA::l] = 'z' + 1;
		dep(j,len[i],1) s[++SA::l] = a[j]; s[++SA::l] = 'z' + 1;
		S[i] = SA::l;
	}
	SA::buildsa(SA::x, SA::y);  SA::geth();
	G::buildgraph();
	G::bfs();
	return 0;
}