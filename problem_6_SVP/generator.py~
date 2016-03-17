from random import *
import numpy

dimension = int(input())
vectors = int(input())

print ("{:d} {:d}".format(vectors, dimension))

def length(l):
	lgt = 0
	for i in range(len(l)):
		lgt+=l[i]**2
	return lgt**0.5

def random_vector(d):
	l=[]
	for i in range(d):
		if(random()<0.5):
			l.append(randint(-300,-250))
		else:
			l.append(randint(250,300))
	return l

avglgt = length(random_vector(dimension))

l=[]

while(len(l)<vectors):
	x = random_vector(dimension)
	factor = avglgt/length(x)
	for i in range(len(x)):
		x[i] = int(x[i]*factor)
	l.append(x)
	A=numpy.matrix(l)
	if (numpy.linalg.matrix_rank(A) != len(l)):
		l.pop()

k=[]
for i in range(vectors):
	k.append(map(str, l[i]))

for i in range(vectors):
	print(" ".join(k[i]))
	continue

