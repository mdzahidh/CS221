import partialsolver
import sampler
import mapreader
import sys

reader = mapreader.mapreader(open(sys.argv[1]))
values = reader.read()

size = (len(values), len(values[0]))
print size

source = (0,0)
dest = ((size[0]-1)/3, (size[1]-1)/3)

current = source
visited = {}

while current != dest:
    # add additional cells to the visited set
    newvisited = {(i,j): values[current[0]+i][current[1]+j] for i in range(20)
                  for j in range(20)}
    visited.update(newvisited)

    # create the sampling and partial solving objects
    smpl = sampler.Sampler(visited, size)
    solver = partialsolver.PartialSolver(smpl, size, dest)

    # take a step
    current = solver.step(current)
    print current
