#include <iostream>
#include <cstdio>
#include <cmath>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define Rep(i,a) for(int i = 0; i < a; i++)
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
#define ab(a) ((a) > 0 ? (a) : -(a))
#define mp(a,b) make_pair(a,b)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
const int N = 800000 + 10, M = 1000000000 + 7;
char s[N];
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
	if (f == -1) Rep(i,l) a[i].r /= l;//!
}
int p[N], n;
#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) (b))
void manachar(){
	dep(i,n,1) s[i << 1] = s[i];
	n = n * 2 + 1;
	rep(i,1,n) if (i & 1) s[i] = '#';
	s[0] = '-', s[n + 1] = '+';
	int mx, j;
	p[0] = mx = j = 0;
	rep(i,1,n) {
		if (mx > i) p[i] = min(p[j - (i - j)], mx - i); else p[i] = 1;
		while (s[i - p[i]] == s[i + p[i]]) p[i]++;
		if (i + p[i] > mx) mx = i + p[i], j = i;
	}
}
LL ans = 0;
cp a[N];
LL f[N], pw[N];
void work(){
	int m = n * 2 - 1;
	Rep(i,m) a[i].r = a[i].i = 0;
	Rep(i,n) if (s[i + 1] == 'a') a[i].r = 1;
	init(m);
	fft(a, m, 1);
	Rep(i,m) a[i] = a[i] * a[i];
	fft(a, m, -1);
	Rep(i,m) f[i] = (LL)(a[i].r + 0.5);

	Rep(i,m) a[i].r = a[i].i = 0;
	Rep(i,n) if (s[i + 1] == 'b') a[i].r = 1;
	fft(a, m, 1);
	Rep(i,m) a[i] = a[i] * a[i];
	fft(a, m, -1);
	Rep(i,m) f[i] += (LL)(a[i].r + 0.5);

	pw[0] = 1;
	rep(i,1,n) pw[i] = pw[i - 1] * 2 % M;
	Rep(i,n) f[i] = f[i << 1];
	dep(i,n,1) f[i] = f[i - 1];
	rep(i,1,n) if (!(i & 1)) f[i]--;
	rep(i,1,n) f[i] >>= 1;
	rep(i,1,n) if (!(i & 1)) ans += (pw[f[i]] - 1) * 2; else ans += pw[f[i]] - 1, ans %= M;

	rep(i,1,n) ans -= (p[i] - 1) >> 1, ans %= M;
	if (ans < 0) ans += M;
}
int main(){
	scanf("%s",s + 1); n = strlen(s + 1);
	manachar();
	work();
	printf("%lld\n",ans);
}
/*
	启示：
		1.fft之前一定要init（多么sb。。）
		2.字符串中间有#。。在算最后连续回文子串个数啊的时候要除以2 : (p[i] - 1) >> 1
		3.fft之后如果i==j 那么 a[i]和自己的要减去，先减去这个之后。。考虑到a[i]a[j]和a[j]a[i]对c[i + j]分别贡献一次。。也就是一对数被算了两次。。所以我们还要除以2
		4.然后再选的时候不光是2^f[i]，在i这里s[i]!='#'时，有第i个选/不选两个情况要*2
	所以说字符串题如果填充了#，就一定要小心各种乘2除2的问题
	同时fft来做平方的时候要注意{i,j}在i!=j时(i,j)(j,i)贡献了两次，在i==j时贡献了一次
*/