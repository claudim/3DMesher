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
//            if(is_the_isomorphic_point_computed(lcc,vertexIt))
//            {//get the computed isomorphic point
//                boostIntersectionPoint = lcc.info<0>(vertexIt);
//                rounded_point = boostIntersectionPoint.get();
//            }
//            else{
            if(!is_the_isomorphic_point_computed(lcc,vertexIt))
            {   //compute the isomorphic point
                boostIntersectionPoint = pointNormalBoundaryIntersectionPointFinder.findIntersecionPoint(lcc, vertexIt,polyhedron);
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
//                    std::cout<< "punto di intersezione "<<rounded_point<<std::endl;
//                    std::cout<<"punto"<< lcc.point(vertexIt)<<std::endl;
                }
            }
            //const Point p = lcc.point(vertexIt);
            boostIntersectionPoint = lcc.info<0>(vertexIt);
            if (boostIntersectionPoint.is_initialized()) // if boostIntersectionPoint is null point
            {

//                hexahedronPoints.emplace_back(lcc.point(vertexIt));
//                hexahedronPoints.emplace_back(rounded_point);
                vertexIt++;
            } else {
                jumpToAnotherFacet = true;
            }
        }
        if(!jumpToAnotherFacet) {
            //check for intersections
            double distance = Grid_maker().getGridDimension(polyhedron)/10;
            this->replace(lcc, facet, polyhedron, distance);

//            std::vector<Point> newHexahedron;
//            newHexahedron.emplace_back(hexahedronPoints[0]);
//            newHexahedron.emplace_back(hexahedronPoints[6]);
//            newHexahedron.emplace_back(hexahedronPoints[4]);
//            newHexahedron.emplace_back(hexahedronPoints[2]);
//            newHexahedron.emplace_back(hexahedronPoints[3]);
//            newHexahedron.emplace_back(hexahedronPoints[1]);
//            newHexahedron.emplace_back(hexahedronPoints[7]);
//            newHexahedron.emplace_back(hexahedronPoints[5]);
//
//            hexahedraToCreate.emplace_back(newHexahedron);
        }
//        hexahedronPoints.clear();
    }

    for( Dart_handle facet : externalFacets) {
        std::vector<Point> hexahedronPointsToCreate;
        std::cout<<"Faccia nuova"<<std::endl;
        for(LCC_3::Dart_of_orbit_range<1>::iterator vertexIt = lcc.darts_of_orbit<1>(facet).begin(),
                    vertexItEnd = lcc.darts_of_orbit<1>(facet).end(); vertexIt != vertexItEnd; ++vertexIt)
        {
//todo: problema se non ho un punto della faccia ad esempio nel caso della normale nulla
            hexahedronPointsToCreate.emplace_back(lcc.point(vertexIt));
            hexahedronPointsToCreate.emplace_back(lcc.info<0>(vertexIt).get());
           // std::cout<<"punto "<<lcc.point(vertexIt) <<", punto isomorfo "<< lcc.info<0>(vertexIt).get()<<std::endl;
        }
        hexahedra_built.emplace_back(lcc.make_hexahedron(hexahedronPointsToCreate[0],
                                                         hexahedronPointsToCreate[6],
                                                         hexahedronPointsToCreate[4],
                                                         hexahedronPointsToCreate[2],
                                                         hexahedronPointsToCreate[3],
                                                         hexahedronPointsToCreate[1],
                                                         hexahedronPointsToCreate[7],
                                                         hexahedronPointsToCreate[5]));



//        //add the new hedrahedron created in the lcc which contain the initial mesh using point and isomorphic point
//        for (std::vector<Point> hexahedron : hexahedraToCreate) {
//            hexahedra_built.emplace_back(lcc.make_hexahedron(hexahedron[0],
//                                                             hexahedron[1],
//                                                             hexahedron[2],
//                                                             hexahedron[3],
//                                                             hexahedron[4],
//                                                             hexahedron[5],
//                                                             hexahedron[6],
//                                                             hexahedron[7]));
//        }
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
    Point p1 = lcc.point(vertex_handle);
    if(p1 == Point(3,1,2.5) || p1 == Point(3,1.5,2.5) || p1 == Point(2.5,1.5,2.5) || p1 == Point(1,1.5,2.5) || p1 == Point(3,0.5,2.5))
    {
        std::cout<<"vediamo "<<std::endl;
        std::cout<< intersectionPoint  <<std::endl;
    }
    if(intersectionPoint.is_initialized())
    {
        return true;
    }
    return false;
}

void InitialMesh_boundary_connector::replace(std::vector<Point> &hexahedronVertexPoints, const Polyhedron& polyhedron, const double distance) {

    std::vector<CGAL::Segment_3<K> > segments;
    segments.emplace_back(CGAL::Segment_3<K>(hexahedronVertexPoints[1], hexahedronVertexPoints[0]));
    segments.emplace_back(CGAL::Segment_3<K>(hexahedronVertexPoints[3], hexahedronVertexPoints[2]));
    segments.emplace_back(CGAL::Segment_3<K>(hexahedronVertexPoints[5], hexahedronVertexPoints[4]));
    segments.emplace_back(CGAL::Segment_3<K>(hexahedronVertexPoints[7], hexahedronVertexPoints[6]));

    for(std::vector<CGAL::Segment_3<K> >::iterator it = segments.begin(), it2, it_end = segments.end();
        it != it_end; ++it){
        it2 = it; it2++;
        while(it2 != it_end){
            double squaredDistance = CGAL::squared_distance(*it, *it2);

            if(squaredDistance < (std::pow(distance,2)))
                //if(squaredDistance < (std::pow(Grid_maker().getGridDimension(polyhedron)/10,2)))
            {
                //move the end segment point:
                //1. change direction
                Vector v1 = (*it).to_vector();
                Vector v2 =(*it2).to_vector();
                Vector v = CGAL::NULL_VECTOR;
                Point p;
                if((v1.direction().dx()== 0 && v1.direction().dy() == 0) || (v1.direction().dx()==0 && v1.direction().dz() ==0) ||
                   (v1.direction().dz()== 0 && v1.direction().dy() == 0))
                {
                    v = LCC::Traits::Construct_sum_of_vectors()(v1, v2);
                    p = (*it).end();
                }
                if((v2.direction().dx()== 0 && v2.direction().dy() == 0) || (v2.direction().dx()==0 && v2.direction().dz() ==0) ||
                   (v2.direction().dz()== 0 && v2.direction().dy() == 0)){

                    v = LCC::Traits::Construct_sum_of_vectors()(v2, v1);
                    p = (*it2).end();
                }
                //2. compute the new intersection point
                if(v != CGAL::NULL_VECTOR) {
                    PointNormal_boundary_intersectionPoint_finder intersectionPointFinder;
                    boost::optional<Point> boostIntersectionPoint = intersectionPointFinder.findIntersecionPoint(p,polyhedron,v);
                    //3. update the vertex point
                    if(boostIntersectionPoint.is_initialized())
                    {
                        Point p1 = boostIntersectionPoint.get();
                        for(int i=0; i < hexahedronVertexPoints.size(); i++ )
                        {
                            if(hexahedronVertexPoints[i] == p)
                            {
                                hexahedronVertexPoints[i+1] = p1;
                            }
                        }
                    }
                }
            }
            ++it2;
        }
    }

}

void InitialMesh_boundary_connector::replace(LCC_3& lcc, Dart_handle facet, const Polyhedron& polyhedron, const double distance) {
    std::vector<CGAL::Segment_3<K> > segments;
    for(LCC_3::Dart_of_orbit_range<1>::iterator vertexIt = lcc.darts_of_orbit<1>(facet).begin(),
                vertexItEnd = lcc.darts_of_orbit<1>(facet).end(); vertexIt != vertexItEnd; ++vertexIt)
    {
        Point isomorphic_point = lcc.info<0>(vertexIt).get();
        Point initialMesh_point = lcc.point(vertexIt);
       // std::cout<<isomorphic_point << " e "<<initialMesh_point<<std::endl;
        segments.emplace_back(CGAL::Segment_3<K>(isomorphic_point,initialMesh_point));
    }
    std::cout<<"Faccia dei segmenti "<< std::endl;
    for(std::vector<CGAL::Segment_3<K> >::iterator it = segments.begin(), it2, it_end = segments.end();
        it != it_end; ++it){
        it2 = it; it2++;
        while(it2 != it_end){
//           std::cout<<"segmento 1 :"<< (*it).source() <<" e "<< (*it).end()<<std::endl;
//            std::cout<<"segmento 2 :"<< (*it2).source() <<" e "<< (*it2).end()<<std::endl;
            double squaredDistance = CGAL::squared_distance(*it, *it2);
            if(squaredDistance < (std::pow(distance,2)))
            {
                //move the end segment point:
                //1. change direction
                Vector v1 = (*it).to_vector();
                Vector v2 =(*it2).to_vector();
                Vector v = CGAL::NULL_VECTOR;
                Point p;
                if((v1.direction().dx()== 0 && v1.direction().dy() == 0) || (v1.direction().dx()==0 && v1.direction().dz() ==0) ||
                   (v1.direction().dz()== 0 && v1.direction().dy() == 0))
                {
                    v = LCC::Traits::Construct_sum_of_vectors()(v1, v2);
                    p = (*it).end();
                }
                if((v2.direction().dx()== 0 && v2.direction().dy() == 0) || (v2.direction().dx()==0 && v2.direction().dz() ==0) ||
                   (v2.direction().dz()== 0 && v2.direction().dy() == 0)){

                    v = LCC::Traits::Construct_sum_of_vectors()(v2, v1);
                    p = (*it2).end();
                }
                //2. compute the new intersection point
                if(v != CGAL::NULL_VECTOR) {
                    PointNormal_boundary_intersectionPoint_finder intersectionPointFinder;
                    boost::optional<Point> boostIntersectionPoint = intersectionPointFinder.findIntersecionPoint(p,polyhedron,v);
                    //3. update the vertex point
                    if(boostIntersectionPoint.is_initialized())
                    {
                        Point p1 = boostIntersectionPoint.get();
                        for(LCC_3::Dart_of_orbit_range<1>::iterator vertexIt = lcc.darts_of_orbit<1>(facet).begin(),
                                    vertexItEnd = lcc.darts_of_orbit<1>(facet).end(); vertexIt != vertexItEnd; ++vertexIt)
                        {
                            if(lcc.point(vertexIt) == p)
                            {
                                lcc.info<0>(vertexIt) = p1;
                            }
                        }
                    }
                }
            }
            it2++;
        }
    }
}