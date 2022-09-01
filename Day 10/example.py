from collections import OrderedDict as odict, Counter

jolts = sorted(int(x) for x in open("input.txt").read().strip().split("\n"))
jolts = [0] + jolts + [jolts[-1] + 3]

# Part 1.
counter = Counter(jolts[i+1] - jolt for i, jolt in enumerate(jolts[:-1]))
print counter[1] * counter[3]

# Part 2.
dag = odict([(x, {y for y in range(x+1, x+4) if y in jolts}) for x in jolts])

def dfc(D, v, M={}):
    "Memoized depth first counter"
    if v in M:
        return M[v]
    elif D[v]:
        M[v] = sum(dfc(D, x, M) for x in D[v])
        return M[v]
    else:
        return 1

print dfc(dag, 0)
