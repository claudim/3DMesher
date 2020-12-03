#include "Hexahedron_fitter.h"

//void Hexahedron_fitter::fix( LCC& lcc, Dart_handle& block_to_fix, std::vector<Dart_handle> intersecting_facets, const Polyhedron& polyhedron) {
//
//    std::vector<Dart_handle> external_facets;
//    External_facet_finder externalFacetFinder;
//    external_facets = externalFacetFinder.find(lcc, block_to_fix);
//    if (external_facets.size() > 1)// there is only a single external facet
//    //if (external_facets.size() == 1)// there is only a single external facet
//    {
//        Dart_handle external_facet = external_facets.at(0);
//        std::vector<Point> points;
//        for (LCC::One_dart_per_incident_cell_range<0, 2, 3>::iterator vertex_it = lcc.one_dart_per_incident_cell<0, 2, 3>(
//                external_facet).begin(),
//                     vertex_end_it = lcc.one_dart_per_incident_cell<0, 2, 3>(external_facet).end();
//             vertex_it != vertex_end_it; ++vertex_it) {
//            points.emplace_back(lcc.point(vertex_it));
//            std::cout << lcc.point(vertex_it) << std::endl;
//        }
//        std::vector<Point> points_to_sort = points;
//        std::vector<Point> sorted_points;
//        Point_sorter pointSorter;
//        pointSorter.sort_northest_points_facet(points_to_sort, sorted_points);
//
//        for (int i = 0; i < sorted_points.size(); i++) {
//            std::cout<< sorted_points.at(i) <<std::endl;
//            if (sorted_points.at(i) != points.at(i)) {
//
//            }
//        }
//    }
//}