#include <iostream>
#include <cstdio>
#include <ctime>
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
#define Rep(i,a) for(int i = 0; i < (a); i++)
#define rep(i,a,b) for(int i = (a); i <= (b); i++)//(a)!
#define dep(i,a,b) for(int i = (a); i >= (b); i--)
#define ab(a) ((a) > 0 ? (a) : -(a))
#define mp(a,b) make_pair((a),(b))
#define pb(a) push_back(a)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
int main(){
	srand(time(NULL));
	int n = 150, m = 150, Q = 100000;
	cout <<n<<' '<<m<<endl;
	rep(i,1,n) { rep(j,1,m - 1) cout <<rand() % 100<<' '; cout <<endl; }
	rep(i,1,n - 1) { rep(j,1,m) cout <<rand() % 100<<' '; cout <<endl; }
	cout <<Q<<endl;
	rep(i,1,Q) cout <<rand() % n + 1<<' '<<rand() % m + 1<<' '<<rand() % n + 1<<' '<<rand() % m + 1<<endl;
	return 0;
}