#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
int main(){
	int t; scanf("%d",&t);
	srand(t);
	int n = rand() % 100 + 1, d = rand() % 30 + 1, k = rand() % 2 + 2;
	cout <<n<<' '<<d<<' '<<k<<endl;
	rep(i,1,n) cout <<rand() % k<<' ';
	cout <<endl;
	rep(i,1,n){
		rep(j,1,d) cout <<rand() % k<<' ';
		cout <<endl;
	}
}