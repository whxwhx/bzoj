#include <iostream>
#include <cstdio>
#include <camth> 
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
struct point{
	int x, y;
};
const int N = 3000 + 10;
const double pi = 3.141592653589793;
inline point operator +(const point &a, const point &b){
	return (point){a.x + b.x, a.y + b.y};
}
inline point operator -(const point &a, const point &b){
	return (point){a.x - b.x, a.y - b.y};
}
inline point operator *(const point &a, const point &b){
	return (point){a.x * b.y - a.y * b.x};
}
inline double att(const point &a){
	double ans = atan2(a.y, a.x);
	if (ans < 0) ans += 2 * pi;
	return ans;
}
node a[3][N], l[3];
bool cmp(const point &a, const point &b){
	return att(a) < att(b);
}
typedef long long LL;
LL ans;
void calc(int x){
	rep(i,1,l[x]){
		rep(j,0,2) if (x != j){
			rep(k,1,l[j]) a[j][k] = a[j][k] - a[x][i];
			int t = 3 - x - j;
			rep(k,1,l[t]) a[t][k] = a[t][k] - a[x][i];
			sort(a[j] + l[j], a[j] + l[j] + 1,cmp);
			
			int b1 = 0 , b2;
			rep(k,1,)

			rep(k,1,l[j]){

			}

			rep(k,1,l[j]) a[j][k] = a[j][k] + a[x][i];
			rep(k,1,l[t]) a[t][k] = a[t][k] + a[x][i];
		}
	}
}
int main(){
	int n;scanf("%d",&n);
	rep(i,1,n){
		int A, B, C; scanf("%d%d%d",&A,&B,&C);
		a[C][++l[C]] = (point){A, B};
	}
	calc(1);
	calc(2);
	calc(3);
	pritnf("%d\n",ans >> 2);
	return 0;
}
