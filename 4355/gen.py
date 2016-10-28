import random
n = 8000
m = 8000
inf = 1000000000
print n, m
for i in xrange(n):
	print random.randint(0,inf / 2),
print
for i in xrange(m):
	op = random.randint(1,3)
	print op, 
	if op == 1:
		l = random.randint(1,n)
		r = random.randint(1,n)
		if l > r :
			l, r = r, l
		print l, r, random.randint(0,inf / 2)
	if op == 2:
		l = random.randint(1,n)
		r = random.randint(1,n)
		if l > r :
			l, r = r, l
		print l, r, random.randint(-inf,inf)
	if op == 3:
		l = random.randint(1,n)
		r = random.randint(1,n)
		if l > r :
			l, r = r, l
		print l, r