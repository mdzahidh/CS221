import util
import random

class Sampler:
    def __init__(self, visited, size, average=30, stdev=20, maxDepth=50):
        self.visited = visited
        self.size = size
        self.average = average
        self.stdev = stdev
        self.boundary = self.getBoundary(self.visited.keys())
        self.maxDepth = maxDepth

    # return the value of the cell if it is sampled or visited, else return None
    def get_or_none(self, cell):
        if cell in self.visited:
            return self.visited[cell]
        elif cell in self.sampled:
            return self.sampled[cell]
        else:
            return None

    def get(self, cell):
        if self.get_or_none(cell) != None:
            return self.get_or_none(cell)
        return self.average

    def getBoundary(self, cells):
        boundary = []

        for cell in cells:
            isBoundary = False
            for nbroff in [(0,1), (0,-1), (1,0), (-1,0)]:
                nbr = tuple([x+i for x,i in zip(cell, nbroff)])
                if nbr not in cells:
                    isBoundary = True
            if isBoundary:
                boundary.append(cell)

        return boundary

    def sample(self):
        # first clear all the sampled cells, we are generating a new sample
        self.sampled = {}

        pq = util.PriorityQueue()

        # push the boundary cells onto the priority queue, this is the base case
        for b in self.boundary:
            pq.update(b, 0)

        while True:
            cell, prio = pq.removeMin()

            # termination conditions
            if cell == None or prio >= self.maxDepth:
                break

            # add all cells to the queue which have not been sampled or visited
            for nbroff in [(0,1), (0,-1), (1,0), (-1,0), (1,1), (-1,-1), (1,-1),
                          (-1,1)]:
                nbr = util.addDelta(cell, nbroff)
                if nbr not in self.sampled and nbr not in self.visited:
                    if util.isValid(nbr, self.size):
                        pq.update(nbr, prio+1)

            # if cell is already visited, no need to sample this cell
            if cell in self.visited:
                continue

            # get all the neighbor values which have been either visited or
            # sampled
            nbrvals = []
            for nbroff in [(0,1), (0,-1), (1,0), (-1,0), (1,1), (-1,-1), (1,-1),
                          (-1,1)]:
                nbr = util.addDelta(cell, nbroff)
                if self.get_or_none(nbr) != None:
                    nbrvals.append(self.get_or_none(nbr))

            assert len(nbrvals) > 0

            # draw a random neighbor and draw my value as a gaussian around that
            nbrval = random.sample(nbrvals, 1)[0]
            cellval = random.gauss(nbrval, self.stdev)
            if cellval < 0:
                cellval = 0

            self.sampled[cell] = cellval


if __name__ == '__main__':
    visited = {
        (0, 0): 0.6,
        (0, 1): 0.6,
        (0, 2): 0.6,
        (0, 3): 0.6,
        (0, 4): 0.6,
        (1, 0): 0.6,
        (1, 1): 0.6,
        (1, 2): 0.6,
        (1, 3): 0.6,
        (1, 4): 0.6,
        (2, 0): 0.6,
        (2, 1): 0.6,
        (2, 2): 0.6,
        (2, 3): 0.6,
        (2, 4): 0.6,
        (3, 0): 0.6,
        (3, 1): 0.6,
        (3, 2): 0.6,
        (3, 3): 0.6,
        (3, 4): 0.6,
        (4, 0): 0.6,
        (4, 1): 0.6,
        (4, 2): 0.6,
        (4, 3): 0.6,
        (4, 4): 0.6,
    }
    sp = Sampler(visited, (100, 100))
    print sp.boundary

    for _ in range(1000):
        sp.sample()
    print sp.sampled
