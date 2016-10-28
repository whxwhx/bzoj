#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
int a[100];
using namespace std;
int main(){
	rep(i,1,51) scanf("%d",&a[i]);
	sort(a + 1, a + 52);
	rep(i,1,51) printf("if (x == %d) return %d;\n",a[i], i);
}