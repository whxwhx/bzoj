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
	int t; cin >>t;srand(t);
	int n = 5, m = 5, q = 5;
	cout <<n<<' '<<m<<' '<<q<<endl;
	rep(i,1,n) cout <<rand()<<' ';
	cout <<endl;
	rep(i,1,m) cout <<rand() % n + 1 <<' '<<rand() % n + 1<<' '<<rand()<<endl;
	rep(i,1,q) cout <<rand() % n + 1 <<' '<<rand()<<' '<<rand() % n + 1<<endl;
	return 0;
}