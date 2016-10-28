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
#define Rep(i,a) for(int i = 0; i < a; i++)
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
#define ab(a) ((a) > 0 ? (a) : -(a))
#define mp(a,b) make_pair(a,b)
#define pb(a) push_back(a)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
const int N = 2000 + 10;
int la, lb;
char a[N], b[N];

int f1[N][N], p1[N], ans1 = -1;
void work1(){	
	rep(i,1,la) rep(j,1,lb) if (a[i] == b[j]) f1[i][j] = f1[i - 1][j - 1] + 1; else f1[i][j] = 0;
	rep(i,1,la){
		p1[i] = 0;
		rep(j,1,lb) p1[i] = max(p1[i], f1[i][j]);
		if (p1[i] < i && (ans1 == -1 || ans1 > p1[i] + 1)) ans1 = p1[i] + 1;
	}
	printf("%d\n",ans1);
}

int f2[N][N], p2[N], ans2 = -1;
void work2(){
	rep(i,1,la) 
		rep(j,1,lb) if (a[i] == b[j]) f2[i][j] = f2[i - 1][j - 1] + 1; else f2[i][j] = f2[i][j - 1];
	rep(i,1,la){
		p2[i] = 0;
		rep(j,1,lb) p2[i] = max(p2[i], f2[i][j]);
		if (p2[i] < i && (ans2 == -1 || ans2 > p2[i] + 1)) ans2 = p2[i] + 1;
	}
	printf("%d\n",ans2);
}
int f3[N][N], p3[N], ans3 = -1;
void work(){
}
int main(){
	scanf("%s",a + 1);
	scanf("%s",b + 1);
	la = strlen(a + 1), lb = strlen(b + 1);
	work1();
	work2();
	work3();
	work4();
}