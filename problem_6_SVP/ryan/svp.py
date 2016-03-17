#!/usr/bin/python2.6 

import sys
from fractions import gcd
from random import randint
from random import random
import os

outfilename = ''
outfilename_t = ''
evalf = None

def lcm(a, b):
    return a * b // gcd(a, b)

def dist(row):
    return sum(map(lambda x: x * x, row))

def dump(row, val):
    global evalf
    if evalf is None or val < evalf:
        evalf = val
        with open(outfilename_t, 'w') as f:
            for r in row:
                f.write('%s\n' % r)
        os.rename(outfilename_t, outfilename)
        print "wrote to %s: %d" % (outfilename, evalf)
    

# usage
if len(sys.argv) < 3:
    print "usage: %s infile outfile" % sys.argv[0]
    exit()

# load data
infile = open(sys.argv[1], 'r')
outfilename = sys.argv[2]
outfilename_t = outfilename + '.t'
header = infile.readline().split(' ')
n = int(header[0])
d = int(header[1])
vals = []
vals_o = []
for line in infile:
    vals.append([int(x) for x in line.split(' ')])
    vals_o.append([int(x) for x in line.split(' ')])
infile.close()

# setup
print "n = %d, d = %d" % (n, d)

#TODO: separate n and d

s1mults = [[None]*d for i in range(n)]
s1coeff = [[0]*d for i in range(n)]

s1gcd = [None]*n
s2gcd = [None]*n

#vals = [[x // 100 for x in r] for r in vals]

# stage 0: output shortest vector in file
print "min:"
mino = dist(vals_o[0])
minoc = vals_o
minores = [0]*n
minores[0] = 1
for i in range(1, n):
    if dist(vals_o[i]) < mino:
        mino = dist(vals_o[i])
        minoc = vals_o[i]
        minores = [0]*n
        minores[i] = 1

print mino
print minoc
print minores

dump(minores, mino)

# stage 1: create upper triangular matrix
print "stage 1"
print "start matrix 1"
for i in range(n):
    s1coeff[i][i] = 1
for i in range(1, n):
    for j in range(i):
        a = vals[i][j]
        b = vals[j][j]
        #if a == 0 or b == 0:
        #    continue
        if a == 0:
            a = 1
        if b == 0:
            b = 1
        l = lcm(a, b)
        da = l / a
        db = l / b
        db *= -1
        for k in range(n):
            vals[i][k] = vals[i][k] * da + vals[j][k] * db
            s1coeff[i][k] = s1coeff[i][k] * da + s1coeff[j][k] * db

        s1mults[i][j] = (da, db)
        #if i <= 2:
        #print "i=%d j=%d a=%d b=%d l=%d da=%d db=%d" % (i, j, a, b, l, da, db)
        #print vals[i][:i+1]

    #re-add in for optimization?
    #g = vals[i][i]
    #for k in range(i+1, d):
    #    g = gcd(g, vals[i][k])
    #if g < 0:
    #    g *= -1
    #for k in range(d):
    #    vals[i][k] /= g
    #s1gcd[i] = g

    zcount = [1 for v in vals[i] if v != 0]
    #print "i=%d, len=%d, vals=%d" % (i, len(vals[i]), len(zcount))
    #print "g=%d" % g

print "stage 1 check:"
#vv = 0
for i in range(n):
    row = []
    for j in range(n):
        v = 0
        for k in range(i+1):
            v += vals_o[k][j] * s1coeff[i][k]

        row.append(v)

    #print row
    zcount = [1 for rr in row if rr != 0]
    if len(zcount) + i > n:
        print "red 1 error: i=%d, len=%d, vals=%d" % (i, len(row), len(zcount))
print "stage 1 check done"

s2coeff = [[0]*d for i in range(n)]
for i in range(n):
    for j in range(d):
        s2coeff[i][j] = s1coeff[i][j]


# stage 2: create diagonal matrix
print "stage 2"
print "start matrix 2"
for i in range(n-1):
    print "s2 i=%d" % i
    for j in range(i+1, n):
        a = vals[i][j]
        b = vals[j][j]
        #if a == 0 or b == 0:
        #    continue
        if a == 0:
            a = 1
        if b == 0:
            b = 1
        l = lcm(a, b)
        da = l / a
        db = l / b
        db *= -1
        for k in range(d):
            vals[i][k] = vals[i][k] * da + vals[j][k] * db
            s2coeff[i][k] = s2coeff[i][k] * da + s2coeff[j][k] * db

    #g = vals[i][i]
    #vals[i][i] = 1
    #s2gcd[i] = g

    #zcount = [1 for v in vals[i] if v != 0] #hack
    #print "i=%d, len=%d, vals=%d" % (i, len(vals[i]), len(zcount))

#s2gcd[n-1] = vals[n-1][n-1]
#print vals[n-1][n-1]
#vals[n-1][n-1] = 1

print "start stage 2 check:"
for i in range(n):
    row = []
    for j in range(n):
        v = 0
        for k in range(n):#(i+1):
            v += vals_o[k][j] * s2coeff[i][k]

        row.append(v)

    #print row
    zcount = [1 for rr in row if rr != 0]
    if len(zcount) != 1:
        print "red 2 error: i=%d, len=%d, vals=%d" % (i, len(row), len(zcount))
print "stage 2 check done"

redcoeff = [[0]*d for i in range(n)]
redc = [0]*n
redg = [0]*n

redval = [[0]*d for i in range(n)]
for i in range(n):
    for j in range(d):
        redval[i][j] = vals[i][j]

for i in range(n):
    g = vals[i][i]
    for v in s2coeff[i]:
        g = gcd(g, v)

    redc[i] = vals[i][i] // g
    redg[i] = g
    #if redc[i] < 0: # messes up other transformations
    #    redc[i] *= -1
    #    redg[i] *= -1
    for k in range(d):
        redcoeff[i][k] = s2coeff[i][k] // g
        redval[i][k] = redval[i][k] // g


########################################

mindex = 0
minval = redc[0]
for i in range(1, n):
    if redc[i] < minval:
        mindex = i
        minval = redc[i]

minmap = map(lambda x: x / float(minval), redc)

fcoeff = []
for r, c in zip(redcoeff, redc):
    fcoeff.append(map(lambda v: v / float(c), r))

def adj_consts(consts):
    rf = [0]*d
    cf = [0]*d
    for i in range(n):
        row = []
        for j in range(d):
            v = 0
            for k in range(n):#(i+1):
                v += vals_o[k][j] * fcoeff[i][k] * consts[i]
            row.append(v)
        crow = []
        for k in range(d):
            crow.append(fcoeff[i][k] * consts[i])
        for k in range(d):
            rf[k] += row[k]
            cf[k] += crow[k]

    crf = map(lambda x: int(round(x)), cf)
    res = [0]*d
    for i in range(n):
        ifact = crf[i]
        for k in range(d):
            res[k] += vals_o[i][k] * ifact
    return (crf, dist(res), res)
    #return (crf, dist(res), crf)
    #return (res, dist(res), crf)

def counts_to_vector(crf):
    res = [0]*d
    for i in range(n):
        ifact = crf[i]
        for k in range(d):
            res[k] += vals_o[i][k] * ifact
    return res

def mod_by_target_v2(startmap):
    ## modify by target -> fix
    #print "min:"
    mino = dist(vals_o[0])
    minoc = vals_o
    minores = [0]*n
    minores[0] = 1
    for i in range(1, n):
        if dist(vals_o[i]) < mino:
            mino = dist(vals_o[i])
            minoc = vals_o[i]
            minores = [0]*n
            minores[i] = 1

    #print mino
    #print minoc
    #print minores
    #mino, minoc = min([(dist(i), i) for i in vals_o], key = lambda t: t[0])

    #print "start:"
    oldc = [v for v in startmap]
    while True:
        #olddist = dist(counts_to_vector(oldc))
        (tempc, olddist, vvvv) = adj_consts(oldc)
        #print olddist
        if olddist > 0:
            oldc = tempc
            break
        oldc = [v*2 for v in oldc]

    #print olddist
    #print oldc
    #print vvvv
    

    #olddist = mino
    #oldc = [i for i in minoc]
    
    #print "new:"
    distf = 100
    T = 2 ** 25
    Tb = 2 ** 5
    scale = 5
    minv = olddist
    minc = [i for i in oldc]
    minres = None
    #minv = mino
    #minc = [i for i in minoc]
    it = 100 - int(0.5 * d)
    it0 = 20
    while True:
        print "start T = %d:" % T
        minround = olddist
        for i in range(it0):
            guessc = [v for v in oldc]
            dist1f = randint(-distf, distf)
            ind0 = randint(0, d-1)
            guessc[ind0] += dist1f
            #newdist = dist(guessc)
            #newc = []
            #newres = []
            (newc, newdist, newres) = adj_consts(guessc)
            for j in range(it):
                if newdist < olddist and newdist > 0:
                    break
                distc = randint(-distf, distf)
                ind = randint(0, d-1)
                guessc[ind] += distc
                (newc, newdist, newres) = adj_consts(guessc)
                #if newdist < olddist and newdist > 0:
                #    break

            if newdist > 0 and (
                    newdist < olddist or (
                        newdist != olddist and
                        scale * T / float(newdist - olddist) > random())
                    ):
                    #float(T - newdist - olddist) / T * scale > random()):
                #if newdist > olddist:
                #    print "-----------------            [!!!]"
                #print "%d -> %d" % (olddist, newdist)
                #print newc
                #print newres
                oldc = newc
                olddist = newdist
                if newdist < minv:
                    minv = newdist
                    minc = [v for v in newc]
                    minres = [v for v in newres]
                    #dump(minres, minv)
                    dump(minc, minv)
                if newdist < minround:
                    minround = newdist
            #elif newdist > 0 and newdist != olddist:
            #    print "%d, %d, %f" % (newdist, olddist, scale * T / (float(newdist - olddist)))
        #print olddist
        oldT = T
        T = T // 2
        print "  --> [min=%d] (T %d -> %d)" % (minv, oldT, T)
        print "  --> [olddist=%d] [newdist=%d]" % (olddist, newdist)
        print "  --> minv: %d minround: %d" % (minv, minround)
        if minround > minv:
            #print "**** end of T: minv is smaller: correcting"
            oldc = [v for v in minc] 
            olddist = minv
            print "  --> [olddist=%d]" % (olddist)
        #print minres
        if T < Tb:
            break;

    print "done"
    print "min:"
    print minv
    print "shortest vector values:"
    print minc
    print "shortest vector coefficients:"
    print minres

    if mino < minv:
        print "found better option in starting list:"
        print mino
        print minoc
        print minores

print 'calculation:'
mod_by_target_v2(minmap)

