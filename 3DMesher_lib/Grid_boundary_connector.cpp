#include "Grid_boundary_connector.h"
#include "Vertex_location_finder.h"

typedef CGAL::Vertex_location_finder Vertex_location_finder ;

//template<typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits>
//void CGAL::Grid_boundary_connector::connect(LCC_3 &lcc, const Polyhedron &polyhedron) {
void Grid_boundary_connector::connect(LCC_3 &lcc, const Polyhedron &polyhedron) {
//    // constructs AABB tree and computes internal KD-tree
//    // data structure to accelerate distance queries
//    Tree tree(faces(polyhedron).first, faces(polyhedron).second, polyhedron);
    Vertex_location_finder vertexLocationFinder = Vertex_location_finder(polyhedron);
    for(LCC_3::One_dart_per_cell_range<3,3>::iterator block_iterator = lcc.one_dart_per_cell<3,3>().begin(),
                end_iterator = lcc.one_dart_per_cell<3,3>().end(); block_iterator!=end_iterator; ++block_iterator){
        for(LCC_3::One_dart_per_incident_cell_range<0,3>::iterator vertex_iterator = lcc.one_dart_per_incident_cell<0,3>(block_iterator).begin(),
                    end_it = lcc.one_dart_per_incident_cell<0,3>(block_iterator).end(); vertex_iterator != end_it; ++vertex_iterator)
        {
            Point p = lcc.point(vertex_iterator);
            if(!vertexLocationFinder.is_point_inside_polyhedron(p) &&
               !vertexLocationFinder.is_point_onBoundary_polyhedron(p)){
                const Tree &tree = vertexLocationFinder.getAabbTree();
                Point closest_point = tree.closest_point_and_primitive(p).first;
                lcc.point(vertex_iterator) = closest_point;
            }
        }
    }


}
