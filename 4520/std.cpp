#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a, _b = b; i <= _b; i++)
#define dep(i,a,b) for(int i = a, _b = b; i >= _b; i--)
using namespace std;
const int N = 100010;
typedef long long LL;

struct point{ int x, y; point(int _x = 0, int _y = 0){ x = _x, y = _y; }}a[N];
inline bool operator < (const point &a, const point &b) { return a.x < b.x || (a.x == b.x && a.y < b.y); }
inline point operator + (const point &a, const point &b) { return point(a.x + b.x, a.y + b.y); }
inline point operator - (const point &a, const point &b) { return point(a.x - b.x, a.y - b.y); }
inline LL operator * (const point &a, const point &b) { return 1LL * a.x * b.y - 1LL * a.y * b.x; }

LL Dis(const point &a, const point &b) { return 1LL * (a.x - b.x) * (a.x - b.x) + 1LL * (a.y - b.y) * (a.y - b.y); }

int n, k, l, t1, t2;
LL d[N * 210]; int dl = 0;
int st[N], top;
int c1[N], c2[N], c[N], cl;

void convex(){
	st[top = 1] = 1;
	rep(i,2,l){
		while (top >= 2 && (a[st[top]] - a[st[top - 1]]) * (a[i] - a[st[top]]) >= 0) top--;
		st[++top] = i;
	}
}

LL ab(LL x) { return x < 0 ? -x : x; }

#define add(x) ( (x + 1 > cl) ? 1 : (x + 1) )
#define S(a, b, c) ab( (c - a) * (c - b) )
#define ac(x) a[c[x]]
void findmx(){
	//cout <<1<<endl;
	convex(); c1[0] = top; rep(i,1,top) c1[i] = st[i];

	rep(i,1,l) a[i].y = -a[i].y;
	convex(); c2[0] = top; rep(i,1,top) c2[i] = st[i];
	rep(i,1,l) a[i].y = -a[i].y;
	//cout <<2<<endl;

	t1 = 1, t2 = 2, cl = 0; 
	rep(i,1,c1[0]) c[++cl] = c1[i];
	dep(i,c2[0] - 1,2) c[++cl] = c2[i];
	//cout <<c1[0] + c2[0] - 2<<' '<<cl<<endl;

	int j = add(2);
	rep(i,1,cl){
		//cout <<c[i]<<' ';
		while ( S(ac(i), ac(add(i)), ac(j)) < S( ac(i), ac(add(i)), ac(add(j)) ) ) j = add(j);//<=的话共线会狗带，会一直转圈
		if ( Dis(ac(i), ac(j)) > Dis(a[ t1 ], a[ t2 ]) ) t1 = c[i], t2 = c[j];
		if ( Dis(ac(add(i)), ac(j)) > Dis(a[ t1 ], a[ t2 ]) ) t1 = c[add(i)], t2 = c[j];
	}
	//cout <<endl; 
}

int main(){
 	scanf("%d%d",&n,&k);
	rep(i,1,n) scanf("%d%d",&a[i].x,&a[i].y);
	if (n <= 1){
		rep(i,1,n) rep(j,i + 1,n) d[++dl] = -Dis(a[i], a[j]);
		nth_element(d + 1, d + k, d + dl + 1);
		printf("%lld\n",-d[k]);
	}else{
		sort(a + 1, a + n + 1); l = n;
		rep(i,1,k){
			//cout <<i<<endl;
			findmx(); if (t1 > t2) swap(t1, t2); 
			//cout <<i<<endl;
			//cout <<Dis(a[t1], a[t2])<<endl;
			//cout <<t1<<' '<<t2<<endl;

			point tmp1 = a[t1], tmp2 = a[t2];
			rep(j,t1,t2 - 2) a[j] = a[j + 1];
			rep(j,t2 - 1, l - 2) a[j] = a[j + 2];
			a[l - 1] = tmp1, a[l] = tmp2;
			l -= 2;
			//cout <<t1<<' '<<t2<<' '<<l<<endl;
			//rep(i,1,n) cout <<a[i].x<<' '<<a[i].y<<endl; cout <<endl;
		}

		rep(i,1,(k << 1)){
			int x = n - i + 1;
			rep(j,1,n) if (j < x) d[++dl] = -Dis(a[x], a[j]);
		}
		nth_element(d + 1, d + k, d + dl + 1);
		printf("%lld\n",-d[k]);
	}
	return 0;
}