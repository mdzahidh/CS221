import heapq

class PriorityQueue:
    def  __init__(self):
        self.DONE = -100000
        self.heap = []
        self.priorities = {}  # Map from state to priority

    # Insert |state| into the heap with priority |newPriority| if
    # |state| isn't in the heap or |newPriority| is smaller than the existing
    # priority.
    # Return whether the priority queue was updated.
    def update(self, state, newPriority):
        oldPriority = self.priorities.get(state)
        if oldPriority == None or newPriority < oldPriority:
            self.priorities[state] = newPriority
            heapq.heappush(self.heap, (newPriority, state))
            return True
        return False

    # Returns (state with minimum priority, priority)
    # or (None, None) if the priority queue is empty.
    def removeMin(self):
        while len(self.heap) > 0:
            priority, state = heapq.heappop(self.heap)
            if self.priorities[state] == self.DONE: continue  # Outdated priority, skip
            self.priorities[state] = self.DONE
            return (state, priority)
        return (None, None) # Nothing left...

class OracleSolver:
    def __init__(self, problem):
        self.problem = problem

    def search(self):
        queue = PriorityQueue()

        startState = self.problem.start()
        queue.update(startState, 0)

        backpointers = {}

        while True:
            state, stateCost = queue.removeMin()
            assert state != None, "no path to destination found"

            if self.problem.isEnd(state):
                print 'Reached goal state with cost %s' % (stateCost,)

                path = [state]
                while state != startState:
                    path.append(backpointers[state])
                    state = backpointers[state]

                return stateCost, path

            for nextState, action, txCost in self.problem.nextStates(state):
                if queue.update(nextState, txCost+stateCost):
                    backpointers[nextState] = state


class BaselineSolver:
    def __init__(self, problem, D):
        self.problem = problem
        self.D = D

    def search(self):
        baseState = self.problem.start()
        baseCost = self.problem.heuristic(baseState)

        while True:
            queue = PriorityQueue()
            backpointers = {}

            queue.update(baseState, baseCost)

            # let us do a BFS on the surrounding cells
            minBoundaryCost = float('inf')
            while True:
                state, stateCost = queue.removeMin()
                if state == None:
                    break

                if self.problem.isEnd(state):
                    print '%s' % (stateCost,)
                    return stateCost

                for nextState, action, txCost in self.problem.nextStates(state):
                    # do not explore if distance is more than D
                    if self.problem.distance(baseState, nextState) > self.D:
                        # in this case state is on the boundary, see if its cost is
                        # less than minBoundaryCost
                        if stateCost < minBoundaryCost:
                            minBoundaryState = state
                            minBoundaryCost = stateCost
                        continue

                    h = (self.problem.heuristic(nextState) -
                         self.problem.heuristic(state))
                    if queue.update(nextState, txCost+stateCost+h):
                        backpointers[nextState] = state

#            print 'Moved to %s from %s' % (minBoundaryState, baseState)
            baseState = minBoundaryState
            baseCost = minBoundaryCost


def SamplingSolver:
    def __init__(self, problem, D):
        self.problem = problem
        self.D = D
        self.partialMap = {}

    def seenState
    def search(self):
        baseState = self.problem.start()

        while True:
            queue = PriorityQueue()
            backpointers = {}
