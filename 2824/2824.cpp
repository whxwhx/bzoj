#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N = 51;
int n, ans = 0, a[N], b[N];
void rev(int x){
	rep(i,1,x / 2) swap(a[i], a[x - i + 1]);
}
void init(){
	rep(i,1,n) b[i] = a[i];
	dep(i,n,1) if(a[i] != i){
		int pos;
		rep(j,1,i) if (a[j] == i) pos = j;
		if (pos != 1) rev(pos), ans++;
		rev(i), ans++;
	}
	rep(i,1,n) a[i] = b[i];
}
inline int cnt(){
	int ans = 0;
	rep(i,2,n) if (a[i] != a[i - 1] + 1 && a[i] != a[i - 1] - 1) ans++;
	return ans;
}
#define mp(a,b) make_pair(a,b)
typedef pair<int, int> node;
node q[N * 3][N];
inline void calc(int t){
	//cout <<t<<' '<<cnt()<<endl;
	if (t + cnt() >= ans) return;
	int flag = 1;
	rep(i,1,n - 1) if (a[i] + 1 != a[i + 1]) {flag = 0; break;} 
	if (flag) {ans = t; return;}

	rep(i,2,n){
		rev(i);
		q[t][i] = mp(cnt(), i);
		rev(i);
	}
	sort(q[t] + 2, q[t] + n + 1);
	
	rep(i,2,n){
		int x = q[t][i].second;
		rev(x);
		calc(t + 1);
		rev(x);
	}
}
int main(){
	scanf("%d",&n);
	rep(i,1,n) scanf("%d",&a[i]);
	rep(i,1,n) b[i] = a[i];
	sort(b + 1, b + n + 1);
	rep(i,1,n) rep(j,1,n) if (a[i] == b[j]) a[i] = j;
	init();
	calc(0);
	printf("%d\n",ans);
}