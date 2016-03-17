import sys

file1=open(sys.argv[1])
outfile=open(sys.argv[2],'w')
startline = int(sys.argv[3])
endline = int(sys.argv[4])
outfile.write("[");
count=1
for line in file1:
	ls=line.split()
	if(count==1):
		n=int(ls[0])
		d=int(ls[1])
		count=2
		matrix=[[0 for x in xrange(d)] for x in xrange(n)]
	elif(count >= startline and count <= endline):
		#line=line.strip()
		#line1 = "["+line+"]\n"
		#change starts here
		line1 = "["
		for j in range(0, endline-startline+1):
			line1 = line1 + ls[j]
			if(j!=endline-2):
				line1 = line1 + " "
		line1 = line1 + "]\n"
		outfile.write(line1)
		count = count + 1
	else:
		count = count + 1
file1.close()
outfile.write("]")
