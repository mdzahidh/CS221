#include <baseline.h>
#include <map.h>
#include <common.h>
#include <util.h>
#include <exactsolver.h>
#include <samplingsolver.h>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {

    Map map;
    map.read(argv[1]);

    ExactSolver exactsolver(map);

    Cell destination = map.size();
    destination = subDelta(destination, {1,1});
    Cell source = {0, 0};

    fprintf(stderr, "dest = (%d, %d)\n", destination.first, destination.second);

    string solverType = argv[2];
    PartialSolver *solver;
    if(solverType == "baseline") {
        solver = new BaselineSolver(map, atoi(argv[3]), destination);
    } else {
        solver = new SamplingSolver(map, atoi(argv[3]), destination, 10);
    }

    Cell current = source;

    float baselineDistance = 0;

    while(true) {
        solver->visit(current);
        auto next = solver->next(current);
        baselineDistance += exactsolver.solve(current, next);

        current = next;

        fprintf(stderr, "location: (%d, %d)\n", current.first, current.second);

        if(current == destination) {
            break;
        }
    }

    auto oracleDistance = exactsolver.solve(source, destination);
    printf("oracle = %.2f baseline = %.2f\n", oracleDistance, baselineDistance);
}
