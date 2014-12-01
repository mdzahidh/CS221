#include <partialsolver.h>
#include <util.h>

using namespace std;

PartialSolver::PartialSolver(const Map &map,
        const int &visibility,
        const Cell &destination) {
    _map = map;
    _destination = destination;
    _visibility = visibility;
    _size = map.size();
}

void PartialSolver::visit(const Cell &cell) {
    for(int i = -_visibility; i < _visibility; i++) {
        for(int j = -_visibility; j < _visibility; j++) {

            Cell nbr = addDelta(cell, Cell(i, j));

            if(isValid(nbr, _size)) {
                _visited[nbr] = _map.at(nbr);
            }
        }
    }
}
