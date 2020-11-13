#include "../Include/catch.hpp"
#include "test_config.h"
#include "../Evaluator_lib/Evaluator.h"
#include "../Evaluator_lib/MeditReader.h"

TEST_CASE("Evaluating unitary cube "){

    Evaluator evaluator;
    std::string fileName = data_path + "/cube.mesh";

    HexMetricVals vals = evaluator.evaluate(fileName);
//    REQUIRE(vals.volume == 1);

}