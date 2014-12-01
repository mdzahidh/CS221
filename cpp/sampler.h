#ifndef __SAMPLER_H__
#define __SAMPLER_H__

#include <map>
#include <vector>
#include <common.h>
#include <util.h>

class Sampler {
    public:
        Sampler(const std::map<Cell, float> &visited,
                const Size &size,
                const float &average,
                const int &stdev,
                const int &maxDepth);
        float get(Cell cell);
        void sample();
        std::vector<Cell> getBoundary(const std::map<Cell, float> &cells);

    private:
        constexpr static float INF = 10000;
        float get_or_inf(Cell cell);

        std::map<Cell, float> _sampled;
        std::map<Cell, float> _visited;
        std::vector<Cell> _boundary;
        Size _size;
        int _maxDepth;
        float _average;
        int _stdev;
};

#endif
