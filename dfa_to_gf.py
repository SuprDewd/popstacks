from collections import defaultdict
import sys

n,m,v0,term = map(int,sys.stdin.readline().strip().split())

x = 'x'
v = [ 'v%d' % d for d in range(n) ]

es = defaultdict(lambda: [])
for i in range(m):
    a,b,c = map(int,sys.stdin.readline().strip().split())
    es[a].append((b,c))

final = set()
for i in range(term):
    final.add(int(sys.stdin.readline().strip()))

eqs = []
for i in range(n):
    eq = '-' + v[i]
    if i in final:
        eq += '+1'
    for (l,j) in es[i]:
        eq += '+' + x + '*' + v[j]
    eqs.append(eq)

sys.stdout.write('x = var("x");')
sys.stdout.write('R.<x> = PolynomialRing(QQ, "x");')
for i in range(n):
    sys.stdout.write('v%d = var("v%d");' % (i,i))
sys.stdout.write('args=[[')
for i,eq in enumerate(eqs):
    if i != 0:
        sys.stdout.write(',')
    sys.stdout.write('%s == 0' % eq)
sys.stdout.write(']')
for i in range(n):
    sys.stdout.write(',v%d' % i)
sys.stdout.write('];')

sys.stdout.write('print((v%d.subs(solve(*args)[0])/x).full_simplify())\n' % v0)

