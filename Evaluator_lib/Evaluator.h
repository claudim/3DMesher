#ifndef INC_3DMESHER_EVALUATOR_H
#define INC_3DMESHER_EVALUATOR_H

#include "verdict.h"
#include "array"


class Evaluator {

public:
    HexMetricVals evaluate(std::vector<std::array<double, 3>> vertices);

};


#endif //INC_3DMESHER_EVALUATOR_H
