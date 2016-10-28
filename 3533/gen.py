n = 1000
print n,'E'
import random
L = 0
inf = 100
for i in xrange(n):
	op = random.randint(0,1);
	if (L == 0):
		op = 1;
	if (op == 0):
		l = random.randint(1, L)
		r = random.randint(1, L)
		if (l > r):
			l, r = r, l
		print 'Q', random.randint(-inf, inf), random.randint(-inf,inf), l, r
	else :
		L+=1;
		print 'A', random.randint(-inf, inf), random.randint(-inf, inf)
