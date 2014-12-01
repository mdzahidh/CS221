import csv
import sys

for filename in sys.argv[1:]:
    filedes = open(filename)

    total = 0
    num = 0
    totalsq = 0
    reader = csv.reader(filedes)

    values = {}

    for i,row in enumerate(reader):
        for j,val in enumerate(row):
            values[(i,j)] = int(val)

    for cell in values.keys():
        for nbroff in [(0,1), (0,-1), (1,0), (-1,0)]:
            nbr = tuple([x+i for x,i in zip(cell, nbroff)])
            if nbr not in values:
                continue

            delta = values[nbr] - values[cell]
            totalsq += delta*delta
            num += 1

    win = [values[(i,j)] for i in range(50) for j in range(50)]
    print sum(win)/2500.0, (totalsq/float(num))**0.5
