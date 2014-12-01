#include <sampler.h>

using namespace std;

Sampler::Sampler(const map<Cell, float> &visited,
        const Size &size,
        const float &average,
        const int &stdev,
        const int &maxDepth) :
    _visited(visited), _size(size),
    _average(average), _stdev(stdev), _maxDepth(maxDepth) {
    _boundary = getBoundary(visited);
}

float Sampler::get_or_inf(Cell cell) {
    if(_visited.count(cell)) {
        return _visited[cell];
    } else if(_sampled.count(cell)) {
        return _sampled[cell];
    } else
        return -INF;
}

float Sampler::get(Cell cell) {
    if(_visited.count(cell)) {
        return _visited[cell];
    } else if(_sampled.count(cell)) {
        return _sampled[cell];
    } else
        return _average;
}

vector<Cell> Sampler::getBoundary(const map<Cell, float> &cells) {
    vector<Cell> boundary;

    for(auto cellvalpair : cells) {
        auto cell= cellvalpair.first;

        bool isBoundary = false;

        vector<Cell> nbroffs = {{0,1}, {0,-1}, {1,0}, {-1,0}};
        for(auto nbroff : nbroffs) {
            auto nbr = addDelta(cell, nbroff);
            if(cells.count(nbr) == 0) {
                isBoundary = true;
                break;
            }
        }

        if(isBoundary) {
            boundary.push_back(cell);
        }
    }

    return boundary;
}

void Sampler::sample() {

    _sampled.clear();

    PriorityQueue<Cell> pq;

    for(auto cell : _boundary) {
        pq.update(cell, 0);
    }

    while(true) {
        auto cellpriopair = pq.findMin();
        auto cell = cellpriopair.first;
        auto prio = cellpriopair.second;

        if(prio < 0 || prio >= _maxDepth) {
            break;
        }

        vector<Cell> nbroffs = {{0,1}, {0,-1}, {1,0}, {-1,0}};
        for(auto nbroff : nbroffs) {
            auto nbr = addDelta(cell, nbroff);
            if(_visited.count(nbr) == 0 && _sampled.count(nbr) == 0) {
                if(isValid(nbr, _size)) {
                    pq.update(nbr, prio+1);
                }
            }
        }

        if(_visited.count(cell))
            continue;

        vector<float> nbrvals;

        for(auto nbroff : nbroffs) {
            auto nbr = addDelta(cell, nbroff);
            if(get_or_inf(nbr) >= 0) {
                nbrvals.push_back(get_or_inf(nbr));
            }
        }

        assert(nbrvals.size() > 0);

        random_shuffle(nbrvals.begin(), nbrvals.end());
        auto randomnbrval = nbrvals[0];

        float randomnoise = (drand48() - 0.5)*_stdev;
        auto cellval = randomnbrval + randomnoise;
        if(cellval < 0)
            cellval = 0;

        _sampled[cell] = cellval;
    }
}
