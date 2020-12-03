#include "InitialMesh_boundary_connector.h"
#include "Hexahedron_fitter.h"


//template<typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits>
void InitialMesh_boundary_connector::connect(LCC_3 &lcc, const Polyhedron &polyhedron) {
    std::vector<Dart_handle> hexahedra_built;
    External_facet_finder externalFacetFinder;

    const std::vector<Dart_handle> &externalFacets = externalFacetFinder.findFacets(lcc);

    PointNormal_boundary_intersectionPoint_finder pointNormalBoundaryIntersectionPointFinder;
    std::vector< std::vector<Point> > hexahedraToCreate;
    LCC_3 newHexahedraLcc;
    for( Dart_handle facet : externalFacets){

        std::vector< Point > hexahedronPoints;
        Point rounded_point;
        bool jumpToAnotherFacet = false;
        LCC_3::Dart_of_orbit_range<1>::iterator vertexIt = lcc.darts_of_orbit<1>(facet).begin(),
                vertexItEnd = lcc.darts_of_orbit<1>(facet).end();
        while(!jumpToAnotherFacet && vertexIt != vertexItEnd) {
            boost::optional<Point> boostIntersectionPoint = boost::none;
            if(is_the_isomorphic_point_computed(lcc,vertexIt))
            {//get the computed isomorphic point
                boostIntersectionPoint = lcc.info<0>(vertexIt);
                rounded_point = boostIntersectionPoint.get();
            }
            else{//compute the isomorphic point
                boostIntersectionPoint = pointNormalBoundaryIntersectionPointFinder.findIntersecionPoint(
                        lcc, vertexIt,
                        polyhedron);

                if (boostIntersectionPoint.is_initialized()) // if boostIntersectionPoint is null point
                {
                    Point intersectionPoint = boostIntersectionPoint.get();

                    float rounded_down_x = 0;
                    float rounded_down_y = 0;
                    float rounded_down_z = 0;
                    if (!(intersectionPoint.x() > -0.001 && intersectionPoint.x() < 0.001))
                        rounded_down_x = intersectionPoint.x();

                    if (!(intersectionPoint.y() > -0.001 && intersectionPoint.y() < 0.001))
                        rounded_down_y = intersectionPoint.y();

                    if (!(intersectionPoint.z() > -0.001 && intersectionPoint.z() < 0.001))
                        rounded_down_z = intersectionPoint.z();

                    rounded_point = Point(rounded_down_x, rounded_down_y, rounded_down_z);
                    lcc.info<0>(vertexIt) = rounded_point;
                }
            }
            //const Point p = lcc.point(vertexIt);
            if (boostIntersectionPoint.is_initialized()) // if boostIntersectionPoint is null point
            {

                hexahedronPoints.emplace_back(lcc.point(vertexIt));
                hexahedronPoints.emplace_back(rounded_point);
                ++vertexIt;
            } else {
                jumpToAnotherFacet = true;
            }
        }
        if(!jumpToAnotherFacet) {
            std::vector<Point> newHexahedron;
            newHexahedron.emplace_back(hexahedronPoints[0]);
            newHexahedron.emplace_back(hexahedronPoints[6]);
            newHexahedron.emplace_back(hexahedronPoints[4]);
            newHexahedron.emplace_back(hexahedronPoints[2]);
            newHexahedron.emplace_back(hexahedronPoints[3]);
            newHexahedron.emplace_back(hexahedronPoints[1]);
            newHexahedron.emplace_back(hexahedronPoints[7]);
            newHexahedron.emplace_back(hexahedronPoints[5]);

            hexahedraToCreate.emplace_back(newHexahedron);
        }
        hexahedronPoints.clear();
    }

    //add the new hedrahedron created in the lcc which contain the initial mesh
    for (std::vector<Point> hexahedron : hexahedraToCreate)
    {
        hexahedra_built.emplace_back(lcc.make_hexahedron(hexahedron[0],
               hexahedron[1],
               hexahedron[2],
               hexahedron[3],
               hexahedron[4],
               hexahedron[5],
               hexahedron[6],
               hexahedron[7]));
    }

// controllare che non si intersechino
//    for (std::vector<Point> hexahedron1 : hexahedraToCreate)
//    {
//        for (std::vector<Point> hexahedron2 : hexahedraToCreate)
//            Polyhedron P1,P2;
//        bool res = CGAL::Polygon_mesh_processing::do_intersect(P1,P2);
//       lcc.make_hexahedron(hexahedron[0],
//               hexahedron[1],
//               hexahedron[2],
//               hexahedron[3],
//               hexahedron[4],
//               hexahedron[5],
//               hexahedron[6],
//               hexahedron[7]);
//    }

    lcc.display_characteristics(std::cout);
    std::cout<<"creati i blocchi tra init mesh e boundary"<<std::endl;
    lcc.sew3_same_facets(); // link all blocks in lcc with same facets if they are not linked.
    lcc.display_characteristics(std::cout);

//    // for each hexahedron created check if there is intersection.
//    unsigned long i = 0;
//    Intersecting_polyhedron_finder intersectingPolyhedronFinder;
//    while( i < hexahedra_built.size())
//    {
//        Dart_handle hexahedra_to_check =  hexahedra_built.at(i);
//        //std::vector<Dart_handle> intersecting_facets;
//        //bool toModify = intersectingPolyhedronFinder.do_polyhedron_facets_intersect(lcc,hexahedra_to_check, intersecting_facets);
//        bool toModify = intersectingPolyhedronFinder.do_polyhedron_facets_intersect(lcc,hexahedra_to_check);
//        if(toModify == true){
//            Hexahedron_fitter hexahedronFitter;
//            hexahedronFitter.fix2(lcc, hexahedra_to_check, polyhedron);
//        }
//        i++;
//    }

}

bool InitialMesh_boundary_connector::is_the_isomorphic_point_computed(LCC_3 &lcc, Dart_handle &vertex_handle) {

    boost::optional<Point> intersectionPoint = lcc.info<0>(vertex_handle);
    if(intersectionPoint.is_initialized())
    {
        return true;
    }
    return false;
}
