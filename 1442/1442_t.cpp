#include <iostream>
#include <cstdio>
#include <algorithm>
#define max(a,b) ((a) > (b) ? (a) : (b))
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef unsigned int ui;
typedef long long LL;
const int N = 55;
ui a[N], t0[N], t1[N];
int l0, l1;

const int M = 100000000;
struct hugeint{
	int a[210], l;
	hugeint operator = (int num){
		l = 0;
		while (num) a[++l] = num % M, num /= M;
		return *this;
	}
};
hugeint c;
hugeint operator + (const hugeint &a, const hugeint &b){
	c = 0;
	c.l = max(a.l, b.l);
	int j = 0;
	rep(i,1,c.l) c.a[i] = (i > a.l ? 0 : a.a[i]) + (i > b.l ? 0 : b.a[i]) + j, j = c.a[i] / M, c.a[i] %= M;
	if (j) c.a[++c.l] = j;
	return c;
}
hugeint operator * (const hugeint &a, int b){
	c = 0; c.l = a.l;
	LL j = 0;
	rep(i,1,c.l)
		j += 1LL * a.a[i] * b, c.a[i] = j % M, j /= M;
	while (j) c.a[++c.l] = j % M, j = j / M;
	return c;
}
LL tmp[210];
hugeint operator * (const hugeint &a, const hugeint &b){
	c = 0;
	c.l = a.l + b.l + 1;
	rep(i,0,c.l) tmp[i] = 0;
	rep(i,1,a.l)
		rep(j,1,b.l)
			tmp[i + j - 1] += 1LL * a.a[i] * b.a[j];
	LL j = 0;
	rep(i,1,c.l) j += tmp[i], c.a[i] = j % M, j /= M;
	while (j) c.a[++c.l] = j % M, j /= M;
	return c;
}
void dec(hugeint &a){
	a.a[1]--;int i = 1;
	while (a.a[i] < 0) a.a[i] += M, a.a[i + 1]--, i++;
	while (!a.a[a.l] && a.l) a.l--;
}
void print(hugeint &a){
	while (!a.a[a.l] && a.l) a.l--;
	if (a.l == 0) {printf("0\n");return;}
	printf("%d",a.a[a.l]);
	dep(i,a.l - 1,1) printf("%08d",a.a[i]);
	printf("\n");
}
hugeint f[N][2], ans, tmp2;
int main(){
    int n; scanf("%d",&n);
    rep(i,1,n) scanf("%ud",&a[i]);
   	ans = 0;
    dep(i,31,0){
        ui t = ui(1) << i;
        l0 = l1 = 0;
        rep(i,1,n) if (a[i] & t) t1[++l1] = a[i] ^ t; else t0[++l0] = a[i];
        int l = 0;
        rep(i,1,l1) a[++l] = t1[i];
        rep(i,1,l0) a[++l] = t0[i];
        f[n + 1][0] = 1, f[n + 1][1] = 0;
        dep(i, n, l1 + 1)
            f[i][0] = f[i + 1][0] * (a[i] + 1), 
            f[i][1] = f[i + 1][1] * (a[i] + 1);
        dep(i, l1, 1)
            f[i][0] = f[i + 1][0] * t + f[i + 1][1] * (a[i] + 1),
            f[i][1] = f[i + 1][1] * t + f[i + 1][0] * (a[i] + 1);
        tmp2 = 1;
        rep(i,1,l1){
        	hugeint tt = f[i + 1][(i - 1) & 1] * tmp2;
            ans = ans + f[i + 1][(i - 1) & 1] * tmp2;
            tmp2 = tmp2 * (a[i] + 1);
        }
        if (l1 & 1) {
        	dec(ans);
        	break;
        }
    }
    print(ans);
}