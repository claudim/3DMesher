#include <vector>
#include "Evaluator.h"
#include "MeditReader.h"

/**
 * Evaluate provided mesh
 * @param vertices coordinates of vertices in the mesh
 * @return List of metrics relative to provided mesh if valid mesh is provided,
 */
HexMetricVals Evaluator::evaluate(std::vector<std::array<double, 3>> vertices) {

    HexMetricVals vals;
    std::array<double, 3> *pArray = vertices.data();
    v_hex_quality(vertices.size(), reinterpret_cast<const double(*)[3]>(pArray), V_HEX_ALL, &vals);
    return vals;
}
