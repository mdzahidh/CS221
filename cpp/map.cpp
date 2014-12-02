#include <map.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace std;

float Map::at(const Cell &cell) const {
    return _values[cell.first][cell.second];
}

Size Map::size() const {
    return Size {_values.size(), _values[0].size()};
}

void Map::read(char *name) {
    FILE *fp = fopen(name, "r");

    char *line = NULL;
    size_t cap = 0;

    while(getline(&line, &cap, fp) != -1) {
        char *token;
        vector<float> row;
        while((token = strsep(&line, ",")) != NULL) {
            float val = atof(token);
            row.push_back(val);
        }
        _values.push_back(row);
    }
}
