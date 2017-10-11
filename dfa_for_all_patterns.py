import sys
from subprocess import Popen, PIPE

k = int(sys.argv[1])
want = int(sys.argv[2])
mod = int(sys.argv[3])

dfas = [None]*50

def combine(a,b):

    p = Popen(["./dfa_intersection", str(k)], stdin=PIPE, stdout=PIPE)
    p.stdin.write(('%s\n%s\n' % (a,b)).encode('utf-8'))
    c = p.stdout.read()
    assert p.wait() == 0

    p = Popen(['../DFA_minimizer'], stdin=PIPE, stdout=PIPE)
    p.stdin.write(c)
    c = p.stdout.read().decode('utf-8')

    sys.stderr.write('%s, %s -> %s\n' % (a.split(' ', 1)[0],
                                         b.split(' ', 1)[0],
                                         c.split(' ', 1)[0]))
    return c

def add(d):
    at = 0
    while dfas[at] is not None:
        d = combine(d, dfas[at])
        dfas[at] = None
        at += 1

    dfas[at] = d

def get_dfa(forb):
    sys.stderr.write('%s\n' % forb)

    p = Popen(['./dfa_for_single_pattern', str(k)], stdin=PIPE, stdout=PIPE)
    p.stdin.write(('%s\n' % forb).encode('utf-8'))
    d = p.stdout.read().decode('utf-8')
    assert p.wait() == 0

    return d

es = []
edge = (1<<k)-1

es.append((0, edge, 1))
es.append((1, edge, 1))
es.append((2, edge, 1))

for t in range(1<<k):
    if t != edge:
        es.append((0, t, 3))
        es.append((1, t, 2))
        es.append((2, t, 2))

    es.append((3, t, 3))

outp = '4 %d 0 1\n%s\n1\n' % (len(es), '\n'.join( '%d %d %d' % v for v in es ))

for lineno, line in enumerate(sys.stdin):
    if lineno % mod != want:
        continue

    line = line.strip()
    for x in '{},':
        line = line.replace(x, ' ')
    line = ' '.join(line.strip().split())
    sys.stderr.write('%d %s\n' % (lineno, line))

    d = get_dfa(line)
    add(d)

for t in dfas:
    if t is not None:
        outp = combine(outp, t)

sys.stdout.write(outp)

