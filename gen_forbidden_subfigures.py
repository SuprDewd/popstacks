import sys

k = int(sys.argv[1])

def reverse(b, bl, x):
    return bl + b-(x-bl)-1

def gen_up(h, l, r):
    if h == -1:
        yield {}
    else:
        for b1 in range(1,3+1):
            for b2 in range(1,3+1):
                for i in range(b1):
                    for j in range(b2):
                        l1 = l-i
                        l2 = r-j
                        if l1+b1 > l2:
                            continue
                        for rest in gen_up(h-1, reverse(b1, l1, l), reverse(b2, l2, r)):

                            rest[(h,l1)] = '|'
                            for t in range(1,b1):
                                rest[(h,l1+t)] = ' '
                            rest[(h,l1+b1)] = '|'

                            rest[(h,l2)] = '|'
                            for t in range(1,b2):
                                rest[(h,l2+t)] = ' '
                            rest[(h,l2+b2)] = '|'

                            yield rest

def gen_down(h, l, r):
    if h == k:
        pass
    else:
        for b1 in range(1,3+1):
            for b2 in range(1,3+1):
                for i in range(b1):
                    for j in range(b2):
                        l1 = l-i
                        l2 = r-j
                        if l1+b1 > l2:
                            continue

                        # if they're adjacent after the swap, then invalid
                        if reverse(b1, l1, l) + 1 == reverse(b2, l2, r):
                            rest = {}

                            rest[(h,l1)] = '|'
                            for t in range(1,b1):
                                rest[(h,l1+t)] = ' '
                            rest[(h,l1+b1)] = '|'

                            rest[(h,l2)] = '|'
                            for t in range(1,b2):
                                rest[(h,l2+t)] = ' '
                            rest[(h,l2+b2)] = '|'

                            yield rest

                        for rest in gen_down(h+1, reverse(b1, l1, l), reverse(b2, l2, r)):

                            rest[(h,l1)] = '|'
                            for t in range(1,b1):
                                rest[(h,l1+t)] = ' '
                            rest[(h,l1+b1)] = '|'

                            rest[(h,l2)] = '|'
                            for t in range(1,b2):
                                rest[(h,l2+t)] = ' '
                            rest[(h,l2+b2)] = '|'

                            yield rest
                            # ans.append(rest)
        # if they're swapped (can be arbitrarily long if h=k-1, otherwise <= 3)
        if r-l+1 <= 3 or h == k-1:
            res = {}
            for t in range(l+1,r+1):
                res[(h,t)] = ' '
            yield res

        # if they're adjacent after the final swap, then invalid
        if h == k-1:
            for i in range(l+1,r+1):
                res = {}
                for j in range(l,r+2):
                    res[(h,j)] = '|' if j in {l,i,r+1} else ' '
                yield res

patts = []

# patterns to disallow partitions longer than 3 in the top k-1 rows
for r in range(k-1):
    cur = []
    for i in range(k):
        if i == r:
            cur.append('|   ')
        else:
            cur.append('****')
    patts.append(cur)

for i in range(k-1):
    for b in range(2,3+1):
        for l in range(b):
            for r in range(l+1,b):
                for above in gen_up(i-1, l, r):
                    for below in gen_down(i+1, l, r):

                        res = {}
                        for u,v in above.items(): res[u] = v
                        for u,v in below.items(): res[u] = v
                        res[(i,0)] = '|'
                        for t in range(1,b): res[(i,t)] = ' '
                        res[(i,b)] = '|'

                        # res[(i,j)] denotes height i, left of cell j

                        mny = min( y for (x,y) in res )
                        mxy = max( y for (x,y) in res )
                        arr = []
                        for x in range(k):
                            row = ''
                            for y in range(mny, mxy+1):
                                if (x,y) in res:
                                    row += res[(x,y)]
                                    # sys.stdout.write(res[(x,y)])
                                else:
                                    row += '*'
                                    # sys.stdout.write('*')
                                # if y != mxy:
                                #     if x == i and y == l:
                                #         sys.stdout.write('l')
                                #     elif x == i and y == r:
                                #         sys.stdout.write('r')
                                #     else:
                                #         sys.stdout.write('o')
                            # sys.stdout.write('\n')
                            arr.append(row)
                        # sys.stdout.write('\n')
                        patts.append(arr)

def contains(p, q):
    # check if p contains q
    for start in range(len(p[0])-len(q[0])+1):
        ok = True
        for i in range(k):
            for j in range(len(q[i])):
                if q[i][j] == '*':
                    continue
                if p[i][start+j] != q[i][j]:
                    ok = False
                    break
            if not ok:
                break
        if ok:
            return True
    return False

# patts2 = []
# for p in sorted(patts, key=lambda x: len(x[0])):
#     found = False
#     for q in patts2:
#         if contains(p,q):
#             found = True
#             break
#     if not found:
#         patts2.append(p)

patts2 = patts

sm = 0
mx = 0
for p in patts2:

    sys.stdout.write('{')
    cnt = 0
    for i in range(k):
        mask = 0
        num = 0
        mx = max(mx, len(p[i]))
        for j in range(len(p[i])):
            if p[i][j] != '*':
                mask |= 1<<j
                if p[i][j] == '|':
                    num |= 1<<j
            else:
                cnt += 1
        if i != 0:
            sys.stdout.write(',')
        sys.stdout.write('{%d,%d}' % (mask,num))
    sys.stdout.write('},\n')
    sm += 2**cnt

