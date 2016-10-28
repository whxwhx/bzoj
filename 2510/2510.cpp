#include <iostream>
#include <algorithm>
#include <cstdio>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 1010;
int n, a[N];
struct ply{
	double a[N];
}f, g;
ply c;
ply operator * (const ply &a, const ply &b){
	rep(i,0,n - 1) c.a[i] = 0;
	rep(i,0,n - 1) rep(j,0,n - 1) c.a[(i + j) % n] += a.a[i] * b.a[j];
	return c;
}
ply w, a1;
ply pow(const ply &A, int b){
	rep(i,0,n - 1) w.a[i] = 0;
	w.a[0] = 1, a1 = A;
	for(;b;b >>= 1, a1 = a1 * a1) if (b & 1) w = w * a1;
	return w;
}
double ans[N];
int main(){
	int m, k; scanf("%d%d%d",&n,&m,&k);
	rep(i,0,n - 1) scanf("%d",&a[i]);
	f.a[0] = 1 - (double)1/ (double)m, f.a[1] = (double)1  / (double)m;
	f = pow(f, k);
	rep(i,0,n - 1) rep(j,0,n - 1) ans[(i + j) % n] += a[i] * f.a[j];
	rep(i,0,n - 1) printf("%.3lf\n",ans[i]);
}