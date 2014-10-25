class problem:
    def __init__(self, mapvals):
        self.mapvals = mapvals
        self.minval = min([min(row) for row in mapvals])

    def setSrc(self, x, y):
        self.srcx = x
        self.srcy = y

    def setDst(self, x, y):
        self.dstx = x
        self.dsty = y

    def start(self):
        return (self.srcx, self.srcy)

    def isEnd(self, state):
        return state == (self.dstx, self.dsty)

    def nextStates(self, state):
        x,y = state
        actions = []
        for i,j in [(0,1),(1,0)]:
            if x+i > self.dstx or y+j > self.dsty:
                continue
            if x+i < 0 or y+j < 0:
                continue
            nextState = (x+i, y+j)
            action = (i, j)
            cost = self.cost(state, nextState)
            actions.append((nextState, action, cost))
        return actions

    def distance(self, state1, state2):
        x1,y1 = state1
        x2,y2 = state2
        return ((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2))**0.5

    def heuristic(self, state):
        return self.distance(state, (self.dstx, self.dsty))*self.minval

    def cost(self, state1, state2):
        # TODO: to incorporate other cost metrics here
        return self.mapvals[state2[0]][state2[1]]
