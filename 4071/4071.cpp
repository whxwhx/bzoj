#include <iostream>
#include <cstdio>
#include <algorithm>
#define min(a,b) ((a) < (b) ? (a) : (b))
#define ab(a) ((a) < 0 ? -(a) : (a))
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N = 200000 + 10;
typedef long long LL;

char p[N], q[N];
int a[N], b[N], ans0 = 0, c[N], cl = 0, k, n;
void work1(){
	int t1 = 0;
	LL ans = ans0;
	//rep(i,1,cl) cout <<c[a[i]]<<' '<<c[b[i]]<<endl;
	rep(i,1,n) ans += c[a[i]] + c[b[i]];
	LL mn = ans;
	sort(a + 1, a + n + 1), sort(b + 1, b + n + 1);

	int a1 = 1, b1 = 1;
	a[n + 1] = b[n + 1] = c[cl] + 1;
	rep(i,1,cl){
		ans += 1LL * t1 * (c[i] - c[i - 1]), ans -= 1LL * (2 * n - t1) * (c[i] - c[i - 1]);
		while (a[a1] <= c[i]) a1++, t1++;
		while (b[b1] <= c[i]) b1++, t1++;
		mn = min(ans, mn);
	}

	printf("%lld\n",mn);
}
void work2(){

}
void work3(){

}
int find(int x){
	int l = 0, r = cl;
	while (l + 1 < r){
		int mid = (l + r) >> 1;
		if (c[mid] < x) l = mid; else r = mid;
	}
	return r;
}
int main(){
	scanf("%d%d",&k,&n);
	rep(i,1,n) {
		p[i] = getchar();
		while (p[i] != 'A' && p[i] != 'B') p[i] = getchar();
		scanf("%d",&a[i]);
		q[i] = getchar();
		while (q[i] != 'A' && q[i] != 'B') q[i] = getchar();
		scanf("%d",&b[i]);
		c[++cl] = a[i], c[++cl] = b[i];
	}
	
	sort(c + 1, c + n + 1);
	cl = (int)(unique(c + 1, c + n + 1) - c) - 1;


	int l = 0;
	rep(i,1,n) cout <<a[i]<<' '<<b[i]<<endl;
	rep(i,1,n) 
		if (p[i] == q[i]) ans0 += ab(a[i] - b[i]); else {if (p[i] == 'B') swap(a[i], b[i]); a[++l] = a[i], b[++ l] = b[i];}
	n = l;
	rep(i,1,n) a[i] = find(a[i]), b[i] = find(b[i]);

	if (k == 1) work1(); else if (n <= 1000) work2(); else work3();
} 