#include <baseline.h>
#include <util.h>

using namespace std;

float BaselineSolver::getAverageVisited() {
    float total = 0, num = 0;
    for(auto cellvaluepair : _visited) {
        total += cellvaluepair.second;
        num += 1;
    }
    return total/num;
}

Cell BaselineSolver::next(const Cell &current) {

    auto average = getAverageVisited();

    PriorityQueue<Cell> pq;
    map<Cell, Cell> parent;
    pq.update(current, 0);

    while(true) {
        auto cellpriopair = pq.findMin();
        auto cell = cellpriopair.first;
        auto prio = cellpriopair.second;

        if(prio < 0)
            break;

        if(cell == _destination)
            break;

        vector<Cell> nbroffs = {{0,1}, {1,0}};
        for(auto nbroff : nbroffs) {
            auto nbr = addDelta(cell, nbroff);
            if(isValid(nbr, _size)) {
                auto nbrval = _visited.count(nbr)?_visited[nbr]:average;

                if(pq.update(nbr, prio + nbrval)) {
                    parent[nbr] = cell;
                }
            }
        }
    }

    Cell cell = _destination;
//    while(parent[cell] != current) {
    while(!_visited.count(parent[cell])) {
        cell = parent[cell];
    }

    return cell;
}
