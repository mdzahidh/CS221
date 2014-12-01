#include <samplingsolver.h>
#include <set>

using namespace std;

float SamplingSolver::getAverageVisited() {
    float total = 0, num = 0;
    for(auto cellvaluepair : _visited) {
        total += cellvaluepair.second;
        num += 1;
    }
    return total/num;
}

Cell SamplingSolver::next(const Cell &current) {
    float average = getAverageVisited();
    Sampler sampler(_visited, _size, average, average/5, 20);

    auto boundary = sampler.getBoundary(_visited);
    auto boundarySet = set<Cell>(boundary.begin(), boundary.end());
    map<Cell, float> distFromSrc;

    // TODO Hack for the case where only actions are 0,1 and 1,0 and
    // destination is a corner
    if(current.first == _destination.first || current.second == _destination.second)
        return _destination;

    // get the distances from source of all boundary cells
    PriorityQueue<Cell> pq;
    pq.update(current, 0);

    while(true) {
        auto cellpriopair = pq.findMin();
        auto cell = cellpriopair.first;
        auto prio = cellpriopair.second;

        if(prio < 0)
            break;

        if(cell == _destination)
            return cell;

        if(boundarySet.count(cell) && cell != current) {
            distFromSrc[cell] = prio;
        }

        vector<Cell> nbroffs = {{0,1}, {1,0}};
        for(auto nbroff : nbroffs) {
            auto nbr = addDelta(cell, nbroff);
            if(_visited.count(nbr)) {
                auto nbrval = _visited[nbr];
                pq.update(nbr, prio + nbrval);
            }
        }
    }

//    for(auto celldistpair : distFromSrc) {
//        printf("(%d,%d) => %.2f\n", celldistpair.first.first,
//                celldistpair.first.second,
//                celldistpair.second);
//    }
//

    map<Cell, float> totaldist;
    for(int i = 0; i < _nsamples; i++) {
        sampler.sample();
        map<Cell, float> distFromDst;

        // get the distances from destination of all boundary
        // cells using sampled distribution
        PriorityQueue<Cell> pq2;
        pq2.update(_destination, 0);

        while(true) {
            auto cellpriopair = pq2.findMin();
            auto cell = cellpriopair.first;
            auto prio = cellpriopair.second;

            if(prio < 0)
                break;

            if(distFromSrc.count(cell)) {
                distFromDst[cell] = prio;
                if(distFromDst.size() == distFromSrc.size())
                    break;
            }

            vector<Cell> nbroffs = {{0,-1}, {-1,0}};
            for(auto nbroff : nbroffs) {
                auto nbr = addDelta(cell, nbroff);
                if(isValid(nbr, _size) && (!_visited.count(nbr) || boundarySet.count(nbr))) {
                    auto nbrval = sampler.get(cell);
                    pq2.update(nbr, prio + nbrval);
                }
            }
        }

        //    for(auto celldistpair : distFromDst) {
        //        printf("(%d,%d) => %.2f\n", celldistpair.first.first,
        //                celldistpair.first.second,
        //                celldistpair.second);
        //    }

        for(auto celldistpair : distFromSrc) {
            auto cell = celldistpair.first;
            auto dist1 = celldistpair.second;
            if(distFromDst.count(cell)) {
                totaldist[cell] += distFromDst[cell] + dist1;
            }
        }
    }

    float minDist = 1e20;
    Cell mincell = {-1, -1};
    for(auto celldistpair : totaldist) {
        auto cell = celldistpair.first;
        auto dist = celldistpair.second;
        if(dist < minDist) {
            minDist = dist;
            mincell = cell;
        }
    }

    assert(mincell != Cell({-1,-1}));
    return mincell;
}
