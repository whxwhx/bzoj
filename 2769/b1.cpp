#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 40010;

typedef pair<int, int> node;
node a[N], q0[N], q1[N];
int s[N], n, l0, l1;

void add(int x, int d){
	for(;x <= n; x += (-x) & x) s[x] += d;
}
int sum(int x){
	int ans = 0;
	for(;x;x -= (-x) & x) ans += s[x];
	return ans;
}

#define mp(a,b) make_pair(a,b)
int suc[N], pre[N], ans[N];

void del(int x){
	suc[pre[x]] = suc[x];
	pre[suc[x]] = pre[x];
}

bool cmp(const pair<int, int> &a, const pair<int, int> &b){
	return a > b;
}

int main(){ 
	scanf("%d",&n);
	rep(i,1,n) scanf("%d",&a[i].first), a[i].second = i, s[i] = 0;
	sort(a + 1, a + n + 1);
	double ans1 = 0, tmp = 0;
	l0 = l1 = 0;
	add(a[1].second, 1);
	rep(i,2,n) {
		tmp += 2.0 / i;
		int t = sum(a[i].second);
		if (i) {
			ans1 += tmp;
			q0[++l0] = mp(a[i].second, i);
		}else q1[++l1] = mp(a[i].second, i);
		add(a[i].second, 1);
	}
	sort(q0 + 1, q0 + l0 + 1, cmp);
	sort(q1 + 1, q1 + l1 + 1);

	rep(i,1,l0) pre[i] = i - 1, suc[i] = i + 1;
	suc[l0] = pre[0] = 0;
	suc[0] = 1;

	rep(i,1,n) ans[i] = 0;
	rep(i,1,n){
		for(int j = suc[0]; j; j = suc[j]) if (a[i].second < q0[j].first){
			if (q0[j].second <= i) del(j); else ans[q0[j].second - i + 1]++;
		}else break;
	}
	rep(i,1,n) ans1 -= 2.0 * ans[i] / i;

	rep(i,1,l1) pre[i] = i - 1, suc[i] = i + 1;
	suc[l1] = pre[0] = 0;
	suc[0] = 1;

	rep(i,1,n) ans[i] = 0;
	rep(i,1,n){
		for(int j = suc[0]; j; j = suc[j]) if (a[i].second > q1[j].first){
			if (q1[j].second <= i) del(j); else ans[q1[j].second - i + 1]++;
		}else break;
	}
	rep(i,1,n) ans1 += 2.0 * ans[i] / i;

	printf("%.6lf\n",ans1);
}