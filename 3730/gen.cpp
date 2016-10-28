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
int main(){
	int t; cin >>t; srand(t);
	int n = 10;
	cout <<n<<' '<<n<<endl;
	rep(i,1,n) cout <<rand() % 1000<<' '; cout <<endl;
	rep(i,2,n) cout <<rand() % (i - 1) + 1<<' '<<i<<endl;
	rep(i,1,n / 2) 
		cout <<1<<' '<<i<<' '<<rand() % 1000<<endl,
		cout <<0<<' '<<i<<' '<<rand() % (n + 1)<<endl;
}