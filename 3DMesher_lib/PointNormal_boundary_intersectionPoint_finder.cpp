#include "PointNormal_boundary_intersectionPoint_finder.h"

//template<typename Point, typename Linear_cell_complex_traits, typename allocator, typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits>
boost::optional<Point> PointNormal_boundary_intersectionPoint_finder::findIntersecionPoint(LCC_3 &lcc,
                                                                          const Dart_const_handle &vertex_handle,
                                                                          const Polyhedron &polyhedron) {
    boost::optional<Point> intersectionPoint = boost::none;
    //Point poi = lcc.point(vertex_handle);
    double d = CGAL::Polygon_mesh_processing::is_outward_oriented(polyhedron)?-1:1;
    Tree tree(faces(polyhedron).begin(), faces(polyhedron).end(), polyhedron);

    //Vector v = this->my_compute_normal_of_cell_0(lcc, vertex_handle);
    Point p1 = lcc.point(vertex_handle);
    Point_normal_finder<LCC_3> pointNormalFinder;
    Vector v = pointNormalFinder.compute(lcc,p1);
    if( v.squared_length() != 0) {
        v = v / (CGAL::sqrt(v * v));

        Ray ray = Ray(p1, d * v);

        auto intersection = tree.first_intersection(ray);
        if (intersection) {
            if (boost::get<Point>(&(intersection->first))) {
                intersectionPoint = boost::get<Point>(intersection->first);
            }
        }
    }
    return intersectionPoint;
}
