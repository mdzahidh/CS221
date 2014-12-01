#ifndef __SAMPLING_SOLVER_H__
#define __SAMPLING_SOLVER_H__

#include <partialsolver.h>
#include <sampler.h>

class SamplingSolver : public PartialSolver {
    public:
        SamplingSolver(const Map &map,
                const int &visibility,
                const Cell &destination,
                const int &nsamples)
            : PartialSolver(map, visibility, destination), _nsamples(nsamples) {}

        virtual Cell next(const Cell &current) override;

    private:
        int _nsamples;
        float getAverageVisited();
};

#endif
