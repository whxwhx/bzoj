#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define min(a,b) (a < b ? a : b)
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define rek() for(int i = 1,l = 1, r = M;l < m; i++, l = r + 1, r = min(m, l + M - 1))
using namespace std;
const int N = 200010;
int a[N], b[N], t[7], M;
int f[451][N], F[N];
inline int find(int a, int x){
	return f[a][x] == x ? x : f[a][x] = find(a, f[a][x]);
}
inline int find(int x){
	return F[x] == x ? x : F[x] = find(F[x]);
}
int n, m;
inline bool check(int A, int B, int x){
	if (x == 0) return true;
	if (A > B) return false;

	int blockL = (A - 1) / M + 2, blockR = B / M, L = (blockL - 1) * M + 1, R = blockR * M;
	if (B - A <= M) L = B + 1, R = B, blockL = 1, blockR = 0;
	//cout <<A<<' '<<B<<' '<<x<<' '<<L<<' '<<R<<' '<<blockL<<' '<<blockR<<endl; 

	//rep(i,1,n) cout <<F[i]<<endl;
	rep(i,A,L - 1) {
		int fa = find(a[i]), fb = find(b[i]);
		if (fa != fb) F[fa] = fb;
	}
	rep(i,R + 1, B){
		int fa = find(a[i]), fb = find(b[i]);
		if (fa != fb) F[fa] = fb;
	}
	bool flag = false;
	if (find(a[x]) == find(b[x])) flag = true;
	rep(i,A,L - 1) F[a[i]] = a[i], F[b[i]] = b[i];
	rep(i,R + 1,B) F[a[i]] = a[i], F[b[i]] = b[i];
	if (flag) return true;
	rep(i, blockL, blockR)
		if (find(i,a[x]) == find(i, b[x])) return true;
	return false;
}
int main(){
	scanf("%d%d",&n, &m);
	rep(i,1,m) scanf("%d%d",&a[i],&b[i]);
	M = (int)sqrt(m);if (M > m) M = m;
	rek() rep(j,1,n) f[i][j] = j;
	rek() rep(j,l,r){
		int fa = find(i, a[j]), fb = find(i, b[j]);
		if (fa != fb) f[i][fa] = fb;
	}
	rep(i,1,n) F[i] = i;
	int k; scanf("%d",&k);
	rep(i,1,k){
		int c; scanf("%d",&c);
		t[0] = 0, t[c + 1] = m + 1;
		rep(i,1,c) scanf("%d",&t[i]);
		sort(t + 1, t + c + 1);
		rep(i,0,c) {
			rep(j,1,c) if (check(t[i] + 1, t[i + 1] - 1, t[j])) t[j] = 0;
			//cout <<i<<' '<<t[1]<<' '<<t[2]<<' '<<t[3]<<endl;
		}
		//cout <<endl;
		bool flag = true;
		rep(i,1,c) if (t[i]) {flag = false;break;}
		if (flag) printf("Connected\n"); else printf("Disconnected\n");
	}
}