#ifndef __MAP_H__
#define __MAP_H__

#include <vector>
#include <common.h>

class Map {
    public:
        float at(const Cell &cell) const;
        Size size() const;

        void read(char *name);

    private:
        std::vector<std::vector<float>> _values;
};

#endif
