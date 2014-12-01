#ifndef __EXACT_SOLVER_H__
#define __EXACT_SOLVER_H__

#include <util.h>
#include <common.h>
#include <map.h>

class ExactSolver {
    public:
        ExactSolver(const Map &map);
        float solve(const Cell &begin, const Cell &end);

    private:
        Map _map;
};

#endif
