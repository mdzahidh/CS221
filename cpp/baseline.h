#ifndef __BASELINE_H__
#define __BASELINE_H__

#include <map>
#include <partialsolver.h>
#include <common.h>

class BaselineSolver : public PartialSolver {
    public:
        BaselineSolver(const Map &map,
                const int &visibility,
                const Cell &destination)
            : PartialSolver(map, visibility, destination) {}

        virtual Cell next(const Cell &current) override;

    private:
        float getAverageVisited();
};

#endif
