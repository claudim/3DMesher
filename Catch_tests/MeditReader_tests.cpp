#include "../Include/catch.hpp"
#include "test_config.h"
#include "../Evaluator_lib/MeditReader.h"

TEST_CASE("Read vertices in an empty medit file"){

    MeditReader meditReader;
    std::string fileName = data_path + "/empty.mesh";

    std::vector<std::array<double, 3>> nodes;
    meditReader.readVertices(fileName, nodes);
    REQUIRE(nodes.empty());

}

TEST_CASE("Read vertices in a medit file containing a cube"){

    MeditReader meditReader;
    std::string fileName = data_path + "/cube.mesh";

    std::vector<std::array<double, 3>> nodes;
    meditReader.readVertices(fileName, nodes);
    REQUIRE(nodes.size() == 8);

}