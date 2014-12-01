#include <exactsolver.h>
#include <util.h>
#include <vector>

using namespace std;

ExactSolver::ExactSolver(const Map &map) {
    _map = map;
}

float ExactSolver::solve(const Cell &begin, const Cell &end) {
    PriorityQueue<Cell> pq;
    pq.update(begin, 0);

    while(true) {
        auto cellpriopair = pq.findMin();
        auto cell = cellpriopair.first;
        auto prio = cellpriopair.second;

        if(prio < 0)
            break;

        if(cell == end)
            return prio;

        vector<Cell> nbroffs = {{0,1}, {1,0}};
        for(auto nbroff : nbroffs) {
            auto nbr = addDelta(cell, nbroff);
            if(isValid(nbr, _map.size())) {
                auto nbrval = _map.at(nbr);

                pq.update(nbr, prio + nbrval);
            }
        }
    }

    assert(0);
}
