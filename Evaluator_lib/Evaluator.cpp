#include <string>
#include <vector>
#include "Evaluator.h"
#include "MeditReader.h"


HexMetricVals Evaluator::evaluate(std::string fileName) {

    MeditReader reader;
    std::vector<std::array<double, 3>> vertices;
    reader.readVertices(fileName, vertices);
    const std::array<double, 3>* verticesArray = &vertices[0];
    int request = V_HEX_JACOBIAN | V_HEX_SHAPE;
    HexMetricVals vals;
    v_hex_quality(vertices.size(), verticesArray, request, &vals);
    return HexMetricVals();
}
