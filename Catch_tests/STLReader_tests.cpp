#include "../Include/catch.hpp"
#include "test_config.h"
#include "STL_reader.h"
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;

typedef Polyhedron::Vertex_const_iterator Vertex_iterator;
typedef Polyhedron::Facet_const_iterator Facet_iterator;
typedef Polyhedron::Edge_const_iterator Edge_iterator;

int get_polyhedron_facets_number_stl(const Polyhedron &polyhedron) {
    int number_of_facet = 0;
    for (Facet_iterator facet_iterator = polyhedron.facets_begin(),
                 facet_end_iterator = polyhedron.facets_end();
         facet_iterator != facet_end_iterator;
         ++facet_iterator)
    {
        number_of_facet++;
    }
    return number_of_facet;
}

int get_polyhedron_vertices_number_stl(const Polyhedron &polyhedron) {
    int number_of_vertices = 0;
    for(Vertex_iterator vertex_iterator = polyhedron.vertices_begin(),
                 vertex_end_iterator = polyhedron.vertices_end();
        vertex_iterator != vertex_end_iterator;
        ++vertex_iterator){
        number_of_vertices++;
    }
    return number_of_vertices;
}

int get_polyhedron_edges_number_stl(const Polyhedron &polyhedron) {
    int number_of_edges = 0;
    for( Edge_iterator  edge_iterator = polyhedron.edges_begin(),
                 edge_end_iterator = polyhedron.edges_end();
         edge_iterator != edge_end_iterator;
         ++edge_iterator){
        number_of_edges++;
    }
    return number_of_edges;
}

TEST_CASE("read_a_pyramid_from_STL_file", "[STLReader_test]")
{
        std::string fileName = data_path + "/pyramid.stl";

        STL_reader reader = STL_reader();

        Polyhedron polyhedron = reader.read<Polyhedron>(fileName);

        int number_of_vertices = get_polyhedron_vertices_number_stl(polyhedron);
        int number_of_facets = get_polyhedron_facets_number_stl(polyhedron);
        int number_of_edges = get_polyhedron_edges_number_stl(polyhedron);

        REQUIRE(number_of_vertices == 5);
        REQUIRE(number_of_facets == 6); // 6 facet because 2 triangular facet make 1 quadrilateral facet
        REQUIRE(number_of_edges == 9);// 9 eges because 2 2 triangular facet make 1 quadrilateral facet(base)
}

TEST_CASE("read_a_cube_from_STL_file", "[STLReader_test]")
{
    std::string fileName = data_path + "/cubeTest.stl";

    STL_reader reader = STL_reader();

    Polyhedron polyhedron = reader.read<Polyhedron>(fileName);

    int number_of_vertices = get_polyhedron_vertices_number_stl(polyhedron);
    int number_of_facets = get_polyhedron_facets_number_stl(polyhedron);
    int number_of_edges = get_polyhedron_edges_number_stl(polyhedron);

    REQUIRE(number_of_vertices == 8);
    REQUIRE(number_of_facets == 12); // 6 facet because 2 triangular facet make 1 quadrilateral facet
    REQUIRE(number_of_edges == 18);
}


