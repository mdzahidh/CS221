import util

class PartialSolver:
    def __init__(self, sampler, size, destination, nsamples=10):
        self.size = size
        self.sampler = sampler
        self.destination = destination
        self.nsamples = nsamples

    def backtrack(self, parent, cell):
        path = [cell]
        current = cell
        while parent[current] != None:
            current = parent[current]
            path.append(current)
        return path

    def step(self, cell):
        # the steps needed to be followed
        # i) sample the distribution
        # ii) generate the minimum distances from destination for all
        # neighboring cells of the cell
        # iii) repeat i and ii for predefined number of times (say 100), and sum
        # up the minimum distances
        actions = [(0,1), (1,0)]

        actionMinDistances = {}
        for action in actions:
            newcell = util.addDelta(cell, action)
            if util.isValid(newcell, self.size):
                actionMinDistances[newcell] = 0

        for _ in range(self.nsamples):
            self.sampler.sample()

            pq = util.PriorityQueue()
            parent = {}
            found = 0

            pq.update(self.destination, 0)
            parent[self.destination] = None

            while True:
                cell, prio = pq.removeMin()

                if cell == None:
                    break

                if cell in actionMinDistances:
                    actionMinDistances[cell] += prio
#                    print cell, prio, self.sampler.get(cell)
#                    print [(x, self.sampler.get(x)) for x in
#                           self.backtrack(parent, cell)]
                    found += 1
                    if found == len(actionMinDistances):
                        break

                for action in actions:
                    newcell = util.subDelta(cell, action)
                    newvalue = self.sampler.get(newcell)
                    if pq.update(newcell, prio + newvalue):
                        parent[newcell] = cell

#            print actionMinDistances 

        minAction = min(actionMinDistances.keys(), key=actionMinDistances.get)
        return minAction


