import mapreader
import solver
import problem
import sys

from matplotlib import pyplot as plt
import numpy as np

mapfile = open(sys.argv[1])
reader = mapreader.mapreader(mapfile)

mapvals = reader.read()

prob = problem.problem(mapvals)
prob.setSrc(0, 0)
prob.setDst(len(mapvals)-1, len(mapvals[0])-1)

oracle = solver.OracleSolver(prob)
cost, path = oracle.search()

plt.pcolormesh(np.array(mapvals))

for i in range(len(path)-1):
    x1,y1 = path[i+1]
    x2,y2 = path[i]
    plt.plot([x1,x2], [y1,y2], 'w-', lw=5)

plt.savefig('test.png')

for visibility in [5,10,20,50,100,200,500,1000,2000]:
    baseline = solver.BaselineSolver(prob, visibility)
    baseline.search()
