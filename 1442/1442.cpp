#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
const int N = 55, M = 1000;
#define max(a,b) ((a) > (b) ? a : b);
#define min(a,b) ((a) < (b) ? a : b)
#define ui unsigned int
ui a[N];
struct hugeint{
	int a[201], l;
	void clr(){
		rep(i,1,200) a.a[i] = 0;
		a.l = 0;
	}
};
void add(hugeint &a, const hugeint &b){
	int t = max(a.l, b.l);
	rep(i,1,t) {
		a.a[i] += b.a[i];
		a.a[i + 1] += a.a[i] / M, a.a[i] %= M;
	}
	if (a.a[t + 1]) a.l = t + 1;
}

hugeint t1;
void mult(hugeint &a, const hugeint &b){
	int t = a.l + b.l - 1;
	rep(i,1,t + 1) t1.a[i] = 0;
	rep(i,1,a.l) 
		rep(j,1,b.l) 
			t1.a[i + j - 1] += a.a[i] * b.a[j];
	rep(i,1,t) t1.a[i + 1] += t1.a[i] / M, t1.a[i] %= M;
	if (t1.a[t + 1]) t1.l = t + 1;
	a = t1;
}

void mul(hugeint &a, ui b){
	rep(i,1,a.l) {
		long long t = a.a[i] + a.a[i] * b;
		a.a[i + 1] += t / M;
		a.a[i] = t % M;
	}
	if (a.a[a.l + 1]) a.l++;
}


hugeint f[N][2], tmp1, ans, tmp2;
int t0[N], t1[N];

void print(){
	dep(i,ans.l,1) printf("%d",ans.a[i]);
	printf("\n");
}

int main(){
	int n; scanf("%d",&n);
	rep(i,1,n) scanf("%ud",&a[i]);
	ans.clr();

	dep(i,31,0){
		int l0 = 0, l1 = 0;
		rep(j,1,n) if (a[j] >> i & 1) t1[++l1] = a[j] & ((1 << i) - 1); else t0[++l0] = a[j];
		int l = 0;
		rep(j,1,l1) a[++l] = t1[j];
		rep(j,1,l0) a[++l] = t0[j];
		
		f[n + 1][0].clr(), f[n + 1][1].clr();
		f[n + 1][0].l = 1, f[n + 1][0].a[1] = 1;
		dep(j,n,l1 + 1){
			f[j][0] = f[j + 1][0], f[j][1].clr();
			mul(f[j][0], a[j]);
		}
		dep(j,l1,1){
			f[j][0] = f[j + 1][0], f[j][1] = f[j + 1][1];
			mul(f[j][0], ((1 << i) - 1)), mul(f[j][1], ((1 << i) - 1));
			tmp1 = f[j + 1][1], mul(tmp1, a[j]), add(f[j][0], tmp1);
			tmp1 = f[j + 1][0], mul(tmp1, a[j]), add(f[j][1], tmp1);
		}

		tmp2.clr(), tmp2.l = 1, tmp2.a[1] = 1;
		rep(j,1,l1){
			tmp1 = tmp2;
			mult(tmp1, f[j + 1][(j - 1）& 1)])
			add(ans, tmp1);
		}
		if (l1 & 1) break;
	}
	print(ans);
}