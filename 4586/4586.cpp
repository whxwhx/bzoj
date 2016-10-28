/*
	a的代价是X，b的代价是Y
	配对之后把左边的看成买入，右边的看成卖出
	我们让它可以和自己匹配，这样的话就相当于什么不做
	那么我们就是要维护两个堆：
		一个维护：ab、bb
		一个维护：ba、aa
	那么我们如果取出了一个ba，
		如果是变成了ba'和aa，那么肯定不如ba优，我们是不会这么做的
		肯定是变成了ab'和bb，那么我们等于把一个卖出变成了什么不做
	 取出来之后是会把前面一整段都取反的
*/

#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
typedef long long LL;

priority_queue<int> q1, q2;

LL ans = 0;
int main(){
	int n, x, y, z; scanf("%d%d%d%d",&n,&x,&y,&z);
	rep(i,1,n) {
		int a, b; scanf("%d%d",&a,&b);
		//a
		rep(j,a + 1,b){
			int c = x;
			if (!q2.empty() && z * i - q2.top() < c) c = z * i - q2.top(), q2.pop();
			ans += c; q1.push(z * i + c);
		}
		//b
		rep(j,b + 1,a){
			int c = y;
			if (!q1.empty() && z * i - q1.top() < c) c = z * i - q1.top(), q1.pop();
			ans += c; q2.push(z * i + c);
		}
	}
	printf("%lld\n",ans); return 0;
}