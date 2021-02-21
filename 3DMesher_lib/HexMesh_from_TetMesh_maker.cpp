#include "HexMesh_from_TetMesh_maker.h"

void HexMesh_from_TetMesh_maker::split_from_tet(const C3t3 &c3t3, LCC_3 &hex_mesh) {

    //per ogni tetraedro
    for (C3t3::Cells_in_complex_iterator cell_it = c3t3.cells_in_complex_begin();
         cell_it != c3t3.cells_in_complex_end();
         ++cell_it) {
        //tet vertices
        Point p0 = Point(cell_it->vertex(0)->point().x(), cell_it->vertex(0)->point().y(),
                         cell_it->vertex(0)->point().z());
        Point p1 = Point(cell_it->vertex(1)->point().x(), cell_it->vertex(1)->point().y(),
                         cell_it->vertex(1)->point().z());
        Point p2 = Point(cell_it->vertex(2)->point().x(), cell_it->vertex(2)->point().y(),
                         cell_it->vertex(2)->point().z());
        Point p3 = Point(cell_it->vertex(3)->point().x(), cell_it->vertex(3)->point().y(),
                         cell_it->vertex(3)->point().z());

        //tet centroid
        Point tet_centroid = CGAL::centroid(p0, p1, p2, p3);

        // edge midpoints
        Point midPoint_p0p1 = CGAL::midpoint(p0, p1);
        Point midPoint_p0p2 = CGAL::midpoint(p0, p2);
        Point midPoint_p0p3 = CGAL::midpoint(p0, p3);
        Point midPoint_p1p2 = CGAL::midpoint(p1, p2);
        Point midPoint_p1p3 = CGAL::midpoint(p1, p3);
        Point midPoint_p2p3 = CGAL::midpoint(p2, p3);

        //facet midpoints
        Point centroid_p0p1p2 = CGAL::centroid(p0, p1, p2);
        Point centroid_p0p1p3 = CGAL::centroid(p0, p1, p3);
        Point centroid_p0p2p3 = CGAL::centroid(p0, p2, p3);
        Point centroid_p1p2p3 = CGAL::centroid(p1, p2, p3);

        hex_mesh.make_hexahedron(p0, midPoint_p0p1, centroid_p0p1p2, midPoint_p0p2, centroid_p0p2p3,
                                 midPoint_p0p3, centroid_p0p1p3, tet_centroid);
        hex_mesh.make_hexahedron(p1, midPoint_p1p2, centroid_p0p1p2, midPoint_p0p1, centroid_p0p1p3,
                                 midPoint_p1p3, centroid_p1p2p3, tet_centroid);
        hex_mesh.make_hexahedron(p2, midPoint_p0p2, centroid_p0p1p2, midPoint_p1p2, centroid_p1p2p3,
                                 midPoint_p2p3, centroid_p0p2p3, tet_centroid);
        hex_mesh.make_hexahedron(p3, midPoint_p0p3, centroid_p0p2p3, midPoint_p2p3, centroid_p1p2p3,
                                 midPoint_p1p3, centroid_p0p1p3, tet_centroid);

    }
    //sew all the created hexahedra
    hex_mesh.sew3_same_facets();
}