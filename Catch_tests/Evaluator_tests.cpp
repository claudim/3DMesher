#include <iostream>
#include "../Include/catch.hpp"
#include "test_config.h"
#include "../Evaluator_lib/Evaluator.h"
#include "../Evaluator_lib/MeditReader.h"

TEST_CASE("Evaluating empty mesh"){
//TODO what if is provided an empty mesh?

//    Evaluator evaluator;
//
//    std::string fileName = data_path + "/empty.mesh";
//
//    MeditReader meditReader;
//    std::vector<std::array<double, 3>> vertices;
//    meditReader.readVertices(fileName, vertices);
//
//    HexMetricVals vals = evaluator.evaluate(vertices);
//    double d = 0;
//    REQUIRE(vals.volume == 0);
}

TEST_CASE("Evaluating unitary cube "){

    Evaluator evaluator;
    std::string fileName = data_path + "/cube.mesh";
    MeditReader meditReader;
    std::vector<std::array<double, 3>> vertices;
    meditReader.readVertices(fileName, vertices);

    HexMetricVals vals = evaluator.evaluate(vertices);

    std::cout << vals.volume << std::endl;
    std::cout << vals.jacobian << std::endl;
    std::cout << vals.scaled_jacobian << std::endl;
    std::cout << vals.condition << std::endl;
    std::cout << vals.diagonal << std::endl;
    std::cout << vals.dimension << std::endl;
    std::cout << vals.distortion << std::endl;
    std::cout << vals.edge_ratio << std::endl;
    std::cout << vals.max_aspect_frobenius << std::endl;
    std::cout << vals.med_aspect_frobenius << std::endl;
    std::cout << vals.oddy << std::endl;
    std::cout << vals.max_edge_ratio << std::endl;
    std::cout << vals.shape << std::endl;
    std::cout << vals.relative_size_squared << std::endl;
    std::cout << vals.taper << std::endl;
    std::cout << vals.skew << std::endl;
    std::cout << vals.shear << std::endl;
    std::cout << vals.shape_and_size << std::endl;
    std::cout << vals.shear_and_size << std::endl;
    REQUIRE(vals.volume == 1);
    REQUIRE(vals.jacobian == 1);

}
//
//TEST_CASE("Evaluating mesh of a sphere "){
//
//    Evaluator evaluator;
//    std::string fileName = data_path + "/sphere.mesh";
//    MeditReader meditReader;
//    std::vector<std::array<double, 3>> vertices;
//    meditReader.readVertices(fileName, vertices);
//
//    HexMetricVals vals = evaluator.evaluate(vertices);
//    std::cout << vals.volume << std::endl;
//    std::cout << vals.jacobian << std::endl;
//    std::cout << vals.scaled_jacobian << std::endl;
//    std::cout << vals.condition << std::endl;
//    std::cout << vals.diagonal << std::endl;
//    std::cout << vals.dimension << std::endl;
//    std::cout << vals.distortion << std::endl;
//    std::cout << vals.edge_ratio << std::endl;
//    std::cout << vals.max_aspect_frobenius << std::endl;
//    std::cout << vals.med_aspect_frobenius << std::endl;
//    std::cout << vals.oddy << std::endl;
//    std::cout << vals.max_edge_ratio << std::endl;
//    std::cout << vals.shape << std::endl;
//    std::cout << vals.relative_size_squared << std::endl;
//    std::cout << vals.taper << std::endl;
//    std::cout << vals.skew << std::endl;
//    std::cout << vals.shear << std::endl;
//    std::cout << vals.shape_and_size << std::endl;
//    std::cout << vals.shear_and_size << std::endl;
////    REQUIRE(vals.volume == 1);
////    REQUIRE(vals.jacobian == 1);
//
//}