import numpy as np

rng = np.random.default_rng(9894213)

c = 25
f = open("inputs/path.in", "w")
f.write(str(c) + '\n')

#for i in np.logspace(start=1, stop=3, num=c, base=10, dtype='int'):
for i in np.linspace(start=10, stop=1000, num=c,  dtype='int'):
    n = i
    r = rng.integers(1, 1000, 1)[0]
    w = 1#rng.integers(1, n+1, 1)[0]
    u = rng.integers(1, 11, 1)[0]
    v = rng.integers(u, 11, 1)[0]
    f.write(str(n) + " " + str(r) + " " + str(w) + " " + str(u) + " " + str(v) + '\n')
    for j in range(n):
        f.write(str(rng.integers(1, 10000, 1)[0]) + " " + str(1) + " ")

    f.write('\n')

f.close()
