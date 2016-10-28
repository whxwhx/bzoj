/*
	考虑每个等价类里挑一个出来统计
	如果知道每个数字的个数，构造就是奇数和偶数分别排序，间隔着穿插。。
	应该可以证明如果这样构造都不行，那么这个等价类就没有可行的方案了
	那么考虑统计这样的数列的个数
	从奇数和偶数排序的角度不好考虑。。我们考虑如何生成这样的一个数列
	1~max每个数字各一个之后，我们每次往里加一个i同时加一个i-1（在i前）
	也就是1 2 ..i (i - 1) (i) i + 1.. max
	对任何一个这样的数列，和这样的（不分顺序）的操作序列一定对应
	证明：
		任何一个这样的数列，每个数字i第一次出现的位置一定是原来的1~max那max个数字
		然后后面的每次在i+1出现前这个数字出现都是+(i-1,i)的操作
		所以存在一一对应关系
	所以等于x_1 + x_2 + ... x_{max} = (n - max) / 2 (x_i >= 0)
	注意长度是小于等于n，所以x_1表示不选
	解的个数是C((n - max) / 2 + max, max - 1)
*/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <set>
#include <map>
#include <queue>
#include <bitset>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define Rep(i,a) for(int i = 0; i < (a); i++)
#define rep(i,a,b) for(int i = (a); i <= (b); i++)//(a)!
#define dep(i,a,b) for(int i = (a); i >= (b); i--)
#define ab(a) ((a) > 0 ? (a) : -(a))
#define mp(a,b) make_pair((a),(b))
#define pb(a) push_back(a)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
const int N = 2000010, mod = 1000000000 + 7;
int fac[N], inv[N];
int C(int n, int m){
	if (n < m) return 0;
	return 1LL * fac[n] * inv[m] % mod * inv[n - m] % mod;
}
int pow(int a, int b){
	int w = 1;
	for(;b;b >>= 1, a = 1LL * a * a % mod) if (b & 1) w = 1LL * w * a % mod;
	return w;
}
int main(){ 
	int n, m; scanf("%d%d",&n,&m); if (m > n) m = n;
	fac[0] = 1; rep(i,1,n) fac[i] = 1LL * fac[i - 1] * i % mod;
	inv[n] = pow(fac[n], mod - 2);
	dep(i,n - 1,0) inv[i] = 1LL * inv[i + 1] * (i + 1) % mod;

	int ans = 1;
	rep(i,2,m){
		int t = (n - i) / 2;
		ans = (ans + C(t + i - 1, i - 1)) % mod;
		if (n >= i + 1) {
			t = (n - 1 - i) / 2;
			ans = (ans + C(t + i - 1, i - 1)) % mod;
		}
	}
	if (ans < 0) ans += mod;
	printf("%d\n",ans);
}