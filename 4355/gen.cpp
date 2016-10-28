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
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
//===========================SegmentTree===============
      
const int STmaxn = 8000005;
const int STinf = 0x7fffffff;
 
struct ST_node
{
  int min, max, sum, lazy_sum, lazy_is_b, lazy_is;  
  ST_node(int _min = 0, int _max = 0, int _sum = 0, 
          int _lazy_sum = 0, int _lazy_is_b = 0, int _lazy_is = 0)
          : min(_min), max(_max), sum(_sum), lazy_sum(_lazy_sum),
            lazy_is_b(_lazy_is_b), lazy_is(_lazy_is) {};  
};
 
struct Segment_Tree
{
  private:
  ST_node t[STmaxn];
  int L, R, num[STmaxn];
   
  void is(int now, int v)
  {
    if (t[now].lazy_is_b) t[now].lazy_is = v;
    else
    {
      t[now].lazy_sum = 0;
      t[now].lazy_is_b = 1;
      t[now].lazy_is = v;  
    }  
    t[now].min = t[now].max = v;
    t[now].sum = num[now] * v;
  }
   
  void sum(int now, int v)
  {
    if (t[now].lazy_is_b) t[now].lazy_is += v;
    else t[now].lazy_sum += v;
    t[now].max += v;
    t[now].min += v;
    t[now].sum += num[now] * v;  
  }
   
  void lazy(int now)
  {
    if (now * 2 + 1 >= STmaxn) return;
    int l = now * 2, r = now * 2 + 1;
    if (t[now].lazy_sum)
    {
      sum(l, t[now].lazy_sum);
      sum(r, t[now].lazy_sum);
      t[now].lazy_sum = 0;
    }
    if (t[now].lazy_is_b)
    {
      is(l, t[now].lazy_is);
      is(r, t[now].lazy_is);
      t[now].lazy_is_b = 0;
    }
  }
   
  void up(int now)
  {
    if (now * 2 + 1 >= STmaxn) return;
    int l = now * 2, r = now * 2 + 1;
    lazy(l), lazy(r);
    t[now].min = min(t[l].min, t[r].min);
    t[now].max = max(t[l].max, t[r].max);
    t[now].sum = t[l].sum + t[r].sum;
  }
   
  void mk_tree(int l, int r, int now, int a[])
  {
    num[now] = r - l + 1;
    if (l == r)
    {
      t[now] = ST_node(a[l], a[l], a[l]);
      return;
    } 
    int mid = (l + r) / 2;
    mk_tree(l, mid, now * 2, a), mk_tree(mid + 1, r, now * 2 + 1, a);
    up(now);
  }
   
  void my_is(int l, int r, int now, int lf, int rt, int v)
  {
    lazy(now);
    if (l >= lf && r <= rt)
    {
      is(now, v);
      return;  
    }
    int mid = (l + r) / 2;
    if (lf <= mid) my_is(l, mid, now * 2, lf, rt, v);
    if (rt >= mid + 1) my_is(mid + 1, r, now * 2 + 1, lf, rt, v);
    up(now);
  }
     
  void my_sum(int l, int r, int now, int lf, int rt, int v)
  {
    lazy(now);
    if (l >= lf && r <= rt)
    {
      sum(now, v);
      return;
    }
    int mid = (l + r) / 2;
    if (lf <= mid) my_sum(l, mid, now * 2, lf, rt, v);
    if (rt >= mid + 1) my_sum(mid + 1, r, now * 2 + 1, lf, rt, v);
    up(now);
  }
   
  int qy_max(int l, int r, int now, int lf, int rt)
  {
    lazy(now);
    if (l >= lf && r <= rt) return t[now].max;
    int mid = (l + r) / 2, ans = -STinf;
    if (lf <= mid) ans = max(ans, qy_max(l, mid, now * 2, lf, rt));
    if (rt >= mid + 1) ans = max(ans, qy_max(mid + 1, r, now * 2 + 1, lf, rt));
    return ans;
  }
   
  int qy_min(int l, int r, int now, int lf, int rt)
  {
    lazy(now);
    if (l >= lf && r <= rt) return t[now].min;
    int mid = (l + r) / 2, ans = STinf;
    if (lf <= mid) ans = min(ans, qy_min(l, mid, now * 2, lf, rt));
    if (rt >= mid + 1) ans = min(ans, qy_min(mid + 1, r, now * 2 + 1, lf, rt));
    return ans;
  }
   
  int qy_sum(int l, int r, int now, int lf, int rt)
  {
    lazy(now);
    if (l >= lf && r <= rt) return t[now].sum;
    int mid = (l + r) / 2, ans = 0;
    if (lf <= mid) ans += qy_sum(l, mid, now * 2, lf, rt);
    if (rt >= mid + 1) ans += qy_sum(mid + 1, r, now * 2 + 1, lf, rt);
    return ans;
  }
   
  public:
  void modify_is(int l, int r, int v)
  {
    my_is(L, R, 1, l, r, v);
  }
   
  void modify_sum(int l, int r, int v)
  {
    my_sum(L, R, 1, l, r, v);
  }
   
  int query_max(int l, int r)
  {
    return qy_max(L, R, 1, l, r);
  }
   
  int query_min(int l, int r)
  {
    return qy_min(L, R, 1, l, r);
  }
   
  int query_sum(int l, int r)
  {
    return qy_sum(L, R, 1, l, r);
  }
   
  void create(int l, int r, int a[])
  {
    L = l;
    R = r;
    mk_tree(L, R, 1, a);
  }
   
  void clear()
  {
    L = R = 0;
    memset(t, 0, sizeof(t));  
  }
}num;
 
//===========================SegmentTree===============

#define rep(i,a,b) for(int i = a , _ = b;i <= _;i ++)

int n , m;

int a[200001];

struct node {
	int type , l , r , v;
}q[200001];

inline int rnd() { return (rand() << 15) | rand(); }

inline void gen_lr(int&l , int&r) {
	l = rnd() % n + 1 , r = rnd() % n + 1;
	if (l > r) swap(l , r);
}

const int mx = 1000000001;

inline int rnd_lr(int l , int r) {
	if (l > r) return mx - 1;
	return rnd() % (r - l + 1) + l;
}

int main() {
	srand(time(0));
	freopen("data.txt" ,  "w" , stdout);
	n = 1000 , m = 1000;
	rep (i , 1 , n) if (i & 1)
		a[i] = rnd() % mx;
	num.create(1 , n , a);
	rep (i , 1 , m) {
		int t = q[i].type = rand() % 3 + 1;
		if (t == 1) {
			int l = rand() % n + 1 , r = rand() % n + 1;
			if (l > r) swap(l , r);
			while (1) {
				if (num.query_min(l , r) != 0) {
					if (rand() % 4) continue;
					break;
				}
				gen_lr(l , r);
			}
			q[i].l = l , q[i].r = r;
			q[i].v = rnd_lr(num.query_min(l , r) , num.query_max(l , r));
			if (rand() % 5) continue;
			q[i].v = rnd_lr(q[i].v , mx - 1);
		 	num.modify_is(q[i].l , q[i].r , q[i].v);
		} else if (t == 2) {
			int l , r;gen_lr(l , r);
			int v = rnd_lr(num.query_min(l , r) , num.query_max(l , r));
			if (rand() % 4) v *= -1;
			num.modify_sum(l , r , v);
			q[i].l = l , q[i].r = r , q[i].v = v;
		} else if (t == 3) {
			int l , r;gen_lr(l , r);
			while (1) {
				if (num.query_min(l , r) != 0) {
					if (rand() % 4) continue;
					break;
				}
				gen_lr(l , r);
			}
			q[i].l = l , q[i].r = r;
		}
	}
	printf("%d %d\n" , n , m);
	printf("%d" , a[1]);
	rep (i , 2 , n) printf(" %d" , a[i]);puts("");
	rep (i , 1 , m) {
		printf("%d %d %d" , q[i].type , q[i].l , q[i].r);
		if (q[i].type < 3) printf(" %d" , q[i].v);
		puts("");
	}
	fclose(stdout);
	return 0;
}