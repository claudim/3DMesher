#define CATCH_CONFIG_MAIN

#include "../Include/catch.hpp"
#include "test_config.h"
#include "OFF_Reader.h"

typedef Polyhedron::Vertex_const_iterator Vertex_iterator;
typedef Polyhedron::Facet_const_iterator Facet_iterator;

int get_polyhedron_vertices_number(const Polyhedron &polyhedron);
int get_polyhedron_facet_number(const Polyhedron &polyhedron);

TEST_CASE("read_a_pyramid_from_off_file", "[Reader_test]")
{
    std::string fileName = data_path + "/pyramid.off";

    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);

    int number_of_vertices = get_polyhedron_vertices_number(polyhedron);
    int number_of_facet = get_polyhedron_facet_number(polyhedron);

    REQUIRE(number_of_vertices == 5);
    REQUIRE(number_of_facet == 6); // 6 facet because 2 triangular facet make 1 quadrilateral facet

}

TEST_CASE("will_throw_failureException_when_file_is_not_found", "[Reader_test]")
{
    std::string fileName = data_path + "/ciao.off";
    OFF_Reader reader = OFF_Reader();
    REQUIRE_THROWS_AS( reader.read(fileName), std::ios_base::failure); //Expects that an exception of the specified type(2argument) is thrown during evaluation of the expression(1 argument).
}

int get_polyhedron_facet_number(const Polyhedron &polyhedron) {
    int number_of_facet = 0;
    for (Facet_iterator pyramid_facet_iterator = polyhedron.facets_begin(),
            pyramid_facet_end_iterator = polyhedron.facets_end();
            pyramid_facet_iterator != pyramid_facet_end_iterator;
            ++pyramid_facet_iterator)
    {
        number_of_facet++;
    }
    return number_of_facet;
}

int get_polyhedron_vertices_number(const Polyhedron &polyhedron) {
    int number_of_vertices = 0;
    for( Vertex_iterator pyramid_vertex_iterator = polyhedron.vertices_begin(),
            pyramid_vertex_end_iterator = polyhedron.vertices_end();
            pyramid_vertex_iterator != pyramid_vertex_end_iterator;
            ++pyramid_vertex_iterator){
        number_of_vertices++;
    }
    return number_of_vertices;
}


