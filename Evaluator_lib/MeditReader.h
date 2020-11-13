#ifndef INC_3DMESHER_MEDITREADER_H
#define INC_3DMESHER_MEDITREADER_H

#include <array>

class MeditReader {

public:
    void readVertices(std::string aFileName, std::vector<std::array<double, 3>> &vertices);
};


#endif //INC_3DMESHER_MEDITREADER_H
