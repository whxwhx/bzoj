#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
const int N = 2010;
int n;

struct point{ double x, y; point(double _x = 0, double _y = 0) { x = _x, y = _y; }}a[N];
inline bool operator < (const point &a, const point &b) { return a.x < b.x || (a.x == b.x && a.y < b.y); }
inline point operator - (const point &a, const point &b) { return point(a.x - b.x, a.y - b.y); }
inline double operator * (const point &a, const point &b) { return a.x * b.y - a.y * b.x; }

int st[N], top;
void convex(){
	st[top = 1] = 1;
	rep(i,2,n){
		while (top >= 2 && (a[st[top]] - a[st[top - 1]]) * (a[i] - a[st[top]]) >= 0 ) top--; 
		st[++top] = i;
	}
}

int c1[N], c2[N], c[N], cl;

double ans = 0;

double ab(double x) { return x < 0 ? -x : x; }

#define ac(x) a[c[x]]
#define add(t2) ((t2 + 1 > cl) ? 1 : (t2 + 1))
int main(){
	scanf("%d",&n); rep(i,1,n) scanf("%lf%lf",&a[i].x,&a[i].y);
	sort(a + 1, a + n + 1);  //rep(i,1,n) cout <<a[i].x<<' '<<a[i].y<<endl; cout <<endl;
	convex(); c1[0] = top; rep(i,1,top) c1[i] = st[i];
 	
 	rep(i,1,n) a[i].y = -a[i].y;
 	convex(); c2[0] = top; rep(i,1,top) c2[i] = st[i];
 	rep(i,1,n) a[i].y = -a[i].y;

 	int cl = 0;
 	rep(i,1,c1[0]) c[++cl] = c1[i];
 	dep(i,c2[0] - 1,2) c[++cl] = c2[i];

 	rep(i,1,cl - 2){
 		int t1 = i + 1, t2 = i + 3; if (t2 > cl) t2 = 1;
 		rep(j,i + 2,cl){
 			while (t1 + 1 != j &&  ab((ac(i) - ac(t1) ) * (ac(j) - ac(t1))) <= ab((ac(i) - ac(t1 + 1)) * (ac(j) - ac(t1 + 1)))) t1++;
 			while (add(t2) != i && ab((ac(i) - ac(t2) ) * (ac(j) - ac(t2))) <= ab((ac(i) - ac(add(t2)))* (ac(j) - ac(add(t2))))) t2 = add(t2);
 			if (t1 != i && t2 != j) 
 			ans = max(ans, ab ( ( ac(i) - ac(t1) ) * (ac(j) - ac(t1)) ) + ab( (ac(i) - ac(t2) ) * (ac(j) - ac(t2))) );
 		}	
 	}

 	printf("%.3lf\n",ans / 2.0);
 	return 0;
}