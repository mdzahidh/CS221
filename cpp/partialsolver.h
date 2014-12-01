#ifndef __PARTIAL_SOLVER_H__
#define __PARTIAL_SOLVER_H__

#include <map>
#include <map.h>
#include <common.h>

class PartialSolver {
    public:
        PartialSolver(const Map &map,
                const int &visibility,
                const Cell &destination);
        void visit(const Cell &cell);

        virtual Cell next(const Cell &current) =0;

    protected:
        std::map<Cell, float> _visited;
        Cell _destination;

        int _visibility;
        Size _size;

    private:
        Map _map;
};

#endif
