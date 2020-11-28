#include "InitialMesh_boundary_connector.h"

#include <CGAL/Polyhedron_3_to_lcc.h>

//template<typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits>
void InitialMesh_boundary_connector::connect(LCC_3 &lcc, const Polyhedron &polyhedron) {
    External_facet_finder externalFacetFinder;

    const std::vector<Dart_const_handle> &externalFacets = externalFacetFinder.find(lcc);

    PointNormal_boundary_intersectionPoint_finder pointNormalBoundaryIntersectionPointFinder;
    std::vector< std::vector<Point> > hexahedraToCreate;
    LCC_3 newHexahedraLcc;
    for( Dart_const_handle facet : externalFacets){

        std::vector< Point > hexahedronPoints;

        bool jumpToAnotherFacet = false;
        LCC_3::Dart_of_orbit_const_range<1>::const_iterator vertexIt = lcc.darts_of_orbit<1>(facet).begin(),
                vertexItEnd = lcc.darts_of_orbit<1>(facet).end();
        while(!jumpToAnotherFacet && vertexIt != vertexItEnd) {
//        for(LCC_3::Dart_of_orbit_const_range<1>::const_iterator vertexIt = lcc.darts_of_orbit<1>(facet).begin(),
//                    vertexItEnd = lcc.darts_of_orbit<1>(facet).end(); vertexIt != vertexItEnd; ++vertexIt) {
            //TODO: marcare il punto per cui ho già calcolato il punto di intersezione e memorizzare questo punto trovato nella 0-cell che sto marcando. questo mi permette di risparmiare del lavoro: se è marcato, cella0 dammi tu il punto di intersezione, se non è marcato, calcolo il punto di interseione.
            const Point p = lcc.point(vertexIt);
            boost::optional<Point> boostIntersectionPoint = pointNormalBoundaryIntersectionPointFinder.findIntersecionPoint(
                    lcc, vertexIt,
                    polyhedron);
            if (boostIntersectionPoint.is_initialized()) // if boostIntersectionPoint is null point
            {
                Point intersectionPoint = boostIntersectionPoint.get();

                float rounded_down_x = 0;
                float rounded_down_y = 0;
                float rounded_down_z = 0;
                if( !(intersectionPoint.x() > -0.001 && intersectionPoint.x() < 0.001))
                    rounded_down_x = intersectionPoint.x();

                if( !(intersectionPoint.y() > -0.001 && intersectionPoint.y() < 0.001))
                    rounded_down_y = intersectionPoint.y();

                if( !(intersectionPoint.z() > -0.001 && intersectionPoint.z() < 0.001))
                    rounded_down_z = intersectionPoint.z();

                Point rounded_point = Point(rounded_down_x, rounded_down_y, rounded_down_z);
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
       lcc.make_hexahedron(hexahedron[0],
               hexahedron[1],
               hexahedron[2],
               hexahedron[3],
               hexahedron[4],
               hexahedron[5],
               hexahedron[6],
               hexahedron[7]);
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
}