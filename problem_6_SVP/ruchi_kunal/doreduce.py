from svptry import *
import sys

file1=open(sys.argv[1])
#outfile=open(sys.argv[2],'w')
#outfile.write("[");
count=0
for line in file1:
	ls=line.split()
	if(count==0):
		n=int(ls[0])
		d=int(ls[1])
		count=1
		matrix=[[0 for x in xrange(d)] for x in xrange(n)]
	else:
		j=0
		#line=line.strip()
		#line1 = "["+line+"]\n"
		#outfile.write(line1);
		for entry in ls:
			matrix[count-1][j]=int(entry)
			j=j+1
		count=count+1
file1.close()
mat1pass = lll_reduction(matrix)
print n," ",d
print_mat(mat1pass)