#include "InitialMesh_boundary_connector.h"
#include "Hexahedron_fitter.h"
#include <CGAL/Segment_3.h>


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
            else {
                boostIntersectionPoint = lcc.info<0>(vertexIt);
            }
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
        //std::cout<<"Faccia nuova"<<std::endl;
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
//    if(p1 == Point(3,1,2.5) || p1 == Point(3,1.5,2.5) || p1 == Point(2.5,1.5,2.5) || p1 == Point(1,1.5,2.5) || p1 == Point(3,0.5,2.5))
//    {
//        std::cout<<"vediamo "<<std::endl;
//        std::cout<< intersectionPoint  <<std::endl;
//    }
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
            std::cout<<"segmento1  "<<(*it).source() << " e " << (*it).end() <<std::endl;
            std::cout<<"segmento2  "<<(*it2).source() << " e " << (*it2).end() <<std::endl;
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
            it2++;
        }
    }

}

void InitialMesh_boundary_connector::replace2(LCC_3& lcc, Dart_handle facet, const Polyhedron& polyhedron, const double distance) {
    std::vector<CGAL::Segment_3<K> > segments;
    for(LCC_3::Dart_of_orbit_range<1>::iterator vertexIt = lcc.darts_of_orbit<1>(facet).begin(),
                vertexItEnd = lcc.darts_of_orbit<1>(facet).end(); vertexIt != vertexItEnd; ++vertexIt)
    {
        Point isomorphic_point = lcc.info<0>(vertexIt).get();
        Point initialMesh_point = lcc.point(vertexIt);
        segments.emplace_back(CGAL::Segment_3<K>(isomorphic_point,initialMesh_point));
    }
    //std::cout<<"Faccia dei segmenti "<< std::endl;
    for(std::vector<CGAL::Segment_3<K> >::iterator it = segments.begin(), it2, it_end = segments.end();
        it != it_end; ++it){
        it2 = it; it2++;
        while(it2 != it_end){
          // std::cout<<"segmento 1 :"<< (*it).end() <<std::endl;
//           std::cout<<"segmento 1 :"<< (*it).source() <<" e "<< (*it).end()<<std::endl;
           // std::cout<<"segmento 2 :"<< (*it2).end() <<std::endl;
//            std::cout<<"segmento 2 :"<< (*it2).source() <<" e "<< (*it2).end()<<std::endl;
//            if((*it).source() == (*it2).source())
//            {
//                std::cout<<"sono uguali"<<std::endl;
//            }
            double squaredDistance = CGAL::squared_distance(*it, *it2);
            if(squaredDistance < (std::pow(distance,2)) &&  !CGAL::parallel(*it, *it2)) //little distance and they are not parallels
            {
              //  std::cout<<"entro "<< squaredDistance <<std::endl;
//              std::cout<<"segmento 1 :"<< (*it).source() <<" e "<< (*it).end()<<std::endl;
//              std::cout<<"segmento 2 :"<< (*it2).source() <<" e "<< (*it2).end()<<std::endl;

                //check if the 2 segments are parallels
//                if(CGAL::parallel(*it, *it2))
//                {
//                    std::cout<<"sono paralleli"<<std::endl;
//                }

                //move the end segment point:
                //1. change direction
                Vector v1 = (*it).to_vector();
                auto v1_x_direction = v1.direction().dx();
                auto v1_y_direction = v1.direction().dy();
                auto v1_z_direction = v1.direction().dz();
                if (v1_x_direction > -0.001 && v1_x_direction < 0.001)
                    v1_x_direction = 0;

                if (v1_y_direction > -0.001 && v1_y_direction < 0.001)
                    v1_y_direction = 0;

                if (v1_z_direction  > -0.001 && v1_z_direction  < 0.001)
                    v1_z_direction = 0;

                Vector v2 =(*it2).to_vector();
                auto v2_x_direction = v2.direction().dx();
                auto v2_y_direction = v2.direction().dy();
                auto v2_z_direction = v2.direction().dz();
                if (v2_x_direction > -0.001 && v2_x_direction < 0.001)
                    v2_x_direction = 0;

                if (v2_y_direction > -0.001 && v2_y_direction < 0.001)
                    v2_y_direction = 0;

                if (v2_z_direction  > -0.001 && v2_z_direction  < 0.001)
                    v2_z_direction = 0;

//                std::cout<<"v1 prima "<<v1.direction()<<std::endl;
//                std::cout<<"v2 prima "<<v2.direction()<<std::endl;
//                std::cout<<"v2 dopo  "<<v2_x_direction<< ", " <<v2_y_direction<<", "<< v2_z_direction<<std::endl;
                Vector v = CGAL::NULL_VECTOR;
                Point p;
                PointNormal_boundary_intersectionPoint_finder intersectionPointFinder;
                boost::optional<Point> boostIntersectionPoint = boost::none;
                Point py = (*it).end();
                Point pye = (*it).source();
                if(((v1_x_direction == v1_y_direction) || (v1_x_direction == v1_z_direction) || (v1_z_direction == v1_y_direction)) &&
                        ((v2_x_direction == v2_y_direction) || (v2_x_direction == v2_z_direction  ) || (v2_z_direction== v2_y_direction)))
                { //the_U_case
                    double new_length = sqrt(2) * (0.5) * Grid_maker().getGridDimension(polyhedron);
                    //double new_length = sqrt(2) * (0.5) ;
                    if((v1_x_direction == v1_y_direction) || (v1_x_direction == v1_z_direction) || (v1_z_direction == v1_y_direction))
                    {
                        //set p as a new point
                        double length = sqrt((*it).squared_length());
                        p =  (*it).end() + new_length * ((*it).source() - (*it).end())/length;

                        //set v as the normal of external facet of the intial mesh
                        //if is the U case then the normal vector of the facet is the right direction
                        v = CGAL::compute_normal_of_cell_2(lcc, facet);

                        boostIntersectionPoint = intersectionPointFinder.findIntersecionPoint(p,polyhedron,v);
                        //set p point as a point of initial_mesh external facet vertex
                        p = (*it).end();


                    }
                    if((v2_x_direction == v2_y_direction) || (v2_x_direction == v2_z_direction  ) || (v2_z_direction== v2_y_direction)){

                        //set p as a new point
                        double length = sqrt((*it2).squared_length());
                        p =  (*it2).end() + new_length * ((*it2).source() - (*it2).end()) /length;

                        //set v as the normal of external facet of the intial mesh
                        //if is the U case then the normal vector of the facet is the right direction
                        v = CGAL::compute_normal_of_cell_2(lcc, facet);

                        boostIntersectionPoint = intersectionPointFinder.findIntersecionPoint(p,polyhedron,v);
                        //set p point as a point of initial_mesh external facet vertex
                        p = (*it2).end();
                    }

                }
                else{ // the_L_case
                    if((v1_x_direction == v1_y_direction) || (v1_x_direction == v1_z_direction) || (v1_z_direction == v1_y_direction))
                    {
                        //std::cout<<"entro in v1 "<<std::endl;
                        v = LCC::Traits::Construct_sum_of_vectors()(v1, v2);
                        p = (*it).end();
                        boostIntersectionPoint = intersectionPointFinder.findIntersecionPoint(p,polyhedron,v);
                    }
                    if((v2_x_direction == v2_y_direction) || (v2_x_direction == v2_z_direction  ) || (v2_z_direction== v2_y_direction)){
                        // std::cout<<"entro in v2 "<<std::endl;
                        v = LCC::Traits::Construct_sum_of_vectors()(v2, v1);
                        p = (*it2).end();
                        boostIntersectionPoint = intersectionPointFinder.findIntersecionPoint(p,polyhedron,v);
                    }
                }

                //2. compute the new intersection point
                if(v != CGAL::NULL_VECTOR) {
                   // std::cout<<"compute the new intersection point "<<std::endl;

//                    PointNormal_boundary_intersectionPoint_finder intersectionPointFinder;
//                    boost::optional<Point> boostIntersectionPoint = intersectionPointFinder.findIntersecionPoint(p,polyhedron,v);

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

void InitialMesh_boundary_connector::connect2(LCC_3 &lcc, const Polyhedron &polyhedron) {
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
            else {
                boostIntersectionPoint = lcc.info<0>(vertexIt);
            }
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
            this->replace2(lcc, facet, polyhedron, distance);
        }
    }

    for( Dart_handle facet : externalFacets) {
        std::vector<Point> hexahedronPointsToCreate;
        //std::cout<<"Faccia nuova"<<std::endl;
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
    }

    lcc.display_characteristics(std::cout);
    std::cout<<"creati i blocchi tra init mesh e boundary"<<std::endl;
    lcc.sew3_same_facets(); // link all blocks in lcc with same facets if they are not linked.
    lcc.display_characteristics(std::cout);

}

void InitialMesh_boundary_connector::replace(LCC_3& lcc, Dart_handle facet, const Polyhedron& polyhedron, const double distance) {
    std::vector<CGAL::Segment_3<K> > segments;
    std::vector<Vector > vectors;

    for(LCC_3::Dart_of_orbit_range<1>::iterator vertexIt = lcc.darts_of_orbit<1>(facet).begin(),
                vertexItEnd = lcc.darts_of_orbit<1>(facet).end(); vertexIt != vertexItEnd; ++vertexIt)
    {
        Point isomorphic_point = lcc.info<0>(vertexIt).get();
        Point initialMesh_point = lcc.point(vertexIt);
        segments.emplace_back(CGAL::Segment_3<K>(isomorphic_point,initialMesh_point));
    }
    //std::cout<<"Faccia dei segmenti "<< std::endl;
    for(std::vector<CGAL::Segment_3<K> >::iterator it = segments.begin(), it2, it_end = segments.end();
        it != it_end; ++it){
        it2 = it; it2++;
        while(it2 != it_end){
            // std::cout<<"segmento 1 :"<< (*it).end() <<std::endl;
//           std::cout<<"segmento 1 :"<< (*it).source() <<" e "<< (*it).end()<<std::endl;
            // std::cout<<"segmento 2 :"<< (*it2).end() <<std::endl;
//            std::cout<<"segmento 2 :"<< (*it2).source() <<" e "<< (*it2).end()<<std::endl;
//            if((*it).source() == (*it2).source())
//            {
//                std::cout<<"sono uguali"<<std::endl;
//            }
            double squaredDistance = CGAL::squared_distance(*it, *it2);
            if(squaredDistance < (std::pow(distance,2)) &&  !CGAL::parallel(*it, *it2)) //little distance and they are not parallels
            {
                //  std::cout<<"entro "<< squaredDistance <<std::endl;
//              std::cout<<"segmento 1 :"<< (*it).source() <<" e "<< (*it).end()<<std::endl;
//              std::cout<<"segmento 2 :"<< (*it2).source() <<" e "<< (*it2).end()<<std::endl;

                //check if the 2 segments are parallels
//                if(CGAL::parallel(*it, *it2))
//                {
//                    std::cout<<"sono paralleli"<<std::endl;
//                }

                //move the end segment point:
                //1. change direction
                Vector v1 = (*it).to_vector();
                auto v1_x_direction = v1.direction().dx();
                auto v1_y_direction = v1.direction().dy();
                auto v1_z_direction = v1.direction().dz();
                if (v1_x_direction > -0.001 && v1_x_direction < 0.001)
                    v1_x_direction = 0;

                if (v1_y_direction > -0.001 && v1_y_direction < 0.001)
                    v1_y_direction = 0;

                if (v1_z_direction  > -0.001 && v1_z_direction  < 0.001)
                    v1_z_direction = 0;

                Vector v2 =(*it2).to_vector();
                auto v2_x_direction = v2.direction().dx();
                auto v2_y_direction = v2.direction().dy();
                auto v2_z_direction = v2.direction().dz();
                if (v2_x_direction > -0.001 && v2_x_direction < 0.001)
                    v2_x_direction = 0;

                if (v2_y_direction > -0.001 && v2_y_direction < 0.001)
                    v2_y_direction = 0;

                if (v2_z_direction  > -0.001 && v2_z_direction  < 0.001)
                    v2_z_direction = 0;

//                std::cout<<"v1 prima "<<v1.direction()<<std::endl;
//                std::cout<<"v2 prima "<<v2.direction()<<std::endl;
//                std::cout<<"v2 dopo  "<<v2_x_direction<< ", " <<v2_y_direction<<", "<< v2_z_direction<<std::endl;
                Vector v = CGAL::NULL_VECTOR;
                Point p;
                PointNormal_boundary_intersectionPoint_finder intersectionPointFinder;
                boost::optional<Point> boostIntersectionPoint = boost::none;
                Point py = (*it).end();
                Point pye = (*it).source();
                if(((v1_x_direction == v1_y_direction) || (v1_x_direction == v1_z_direction) || (v1_z_direction == v1_y_direction)) &&
                   ((v2_x_direction == v2_y_direction) || (v2_x_direction == v2_z_direction  ) || (v2_z_direction== v2_y_direction)))
                { //the_U_case
                    double new_length = sqrt(2) * (0.5) * Grid_maker().getGridDimension(polyhedron);
                    //double new_length = sqrt(2) * (0.5) ;
                    if((v1_x_direction == v1_y_direction) || (v1_x_direction == v1_z_direction) || (v1_z_direction == v1_y_direction))
                    {
                        //set p as a new point
                        double length = sqrt((*it).squared_length());
                        p =  (*it).end() + new_length * ((*it).source() - (*it).end())/length;

                        //set v as the normal of external facet of the intial mesh
                        //if is the U case then the normal vector of the facet is the right direction
                        v = CGAL::compute_normal_of_cell_2(lcc, facet);

                        boostIntersectionPoint = intersectionPointFinder.findIntersecionPoint(p,polyhedron,v);
                        //set p point as a point of initial_mesh external facet vertex
                        p = (*it).end();


                    }
                    if((v2_x_direction == v2_y_direction) || (v2_x_direction == v2_z_direction  ) || (v2_z_direction== v2_y_direction)){

                        //set p as a new point
                        double length = sqrt((*it2).squared_length());
                        p =  (*it2).end() + new_length * ((*it2).source() - (*it2).end()) /length;

                        //set v as the normal of external facet of the intial mesh
                        //if is the U case then the normal vector of the facet is the right direction
                        v = CGAL::compute_normal_of_cell_2(lcc, facet);

                        boostIntersectionPoint = intersectionPointFinder.findIntersecionPoint(p,polyhedron,v);
                        //set p point as a point of initial_mesh external facet vertex
                        p = (*it2).end();
                    }

                }
                else{ // the_L_case
                    if((v1_x_direction == v1_y_direction) || (v1_x_direction == v1_z_direction) || (v1_z_direction == v1_y_direction))
                    {
                        //std::cout<<"entro in v1 "<<std::endl;
                        v = LCC::Traits::Construct_sum_of_vectors()(v1, v2);
                        p = (*it).end();
                        boostIntersectionPoint = intersectionPointFinder.findIntersecionPoint(p,polyhedron,v);
                    }
                    if((v2_x_direction == v2_y_direction) || (v2_x_direction == v2_z_direction  ) || (v2_z_direction== v2_y_direction)){
                        // std::cout<<"entro in v2 "<<std::endl;
                        v = LCC::Traits::Construct_sum_of_vectors()(v2, v1);
                        p = (*it2).end();
                        boostIntersectionPoint = intersectionPointFinder.findIntersecionPoint(p,polyhedron,v);
                    }
                }

                //2. compute the new intersection point
                if(v != CGAL::NULL_VECTOR) {
                    // std::cout<<"compute the new intersection point "<<std::endl;

//                    PointNormal_boundary_intersectionPoint_finder intersectionPointFinder;
//                    boost::optional<Point> boostIntersectionPoint = intersectionPointFinder.findIntersecionPoint(p,polyhedron,v);

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


void InitialMesh_boundary_connector::connect3(LCC_3 &lcc, const Polyhedron &polyhedron) {
    std::vector<Dart_handle> hexahedra_built;
    std::vector<Dart_handle> maybe_U_external_facet;
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
                }
            }
            else {
                boostIntersectionPoint = lcc.info<0>(vertexIt);
            }
            if (boostIntersectionPoint.is_initialized()) // if boostIntersectionPoint is null point
            {
                vertexIt++;
            } else {
                jumpToAnotherFacet = true;
            }
        }
        if(!jumpToAnotherFacet) {
            //check for intersections
            double distance = Grid_maker().getGridDimension(polyhedron)/10;
            if (!this->replace_L_facets(lcc, facet, polyhedron, distance)){
                maybe_U_external_facet.emplace_back(facet);
            }
        }
    }
    for( Dart_handle facet : maybe_U_external_facet)
    {
        double distance = Grid_maker().getGridDimension(polyhedron)/10;
        this->replace_U_facets(lcc, facet, polyhedron, distance);

    }
    for( Dart_handle facet : externalFacets) {
        std::vector<Point> hexahedronPointsToCreate;
        //std::cout<<"Faccia nuova"<<std::endl;
        for(LCC_3::Dart_of_orbit_range<1>::iterator vertexIt = lcc.darts_of_orbit<1>(facet).begin(),
                    vertexItEnd = lcc.darts_of_orbit<1>(facet).end(); vertexIt != vertexItEnd; ++vertexIt)
        {
//todo: problema se non ho un punto della faccia ad esempio nel caso della normale nulla
            hexahedronPointsToCreate.emplace_back(lcc.point(vertexIt));
            hexahedronPointsToCreate.emplace_back(lcc.info<0>(vertexIt).get());
        }
        hexahedra_built.emplace_back(lcc.make_hexahedron(hexahedronPointsToCreate[0],
                                                         hexahedronPointsToCreate[6],
                                                         hexahedronPointsToCreate[4],
                                                         hexahedronPointsToCreate[2],
                                                         hexahedronPointsToCreate[3],
                                                         hexahedronPointsToCreate[1],
                                                         hexahedronPointsToCreate[7],
                                                         hexahedronPointsToCreate[5]));
    }

    lcc.display_characteristics(std::cout);
    std::cout<<"creati i blocchi tra init mesh e boundary"<<std::endl;
    lcc.sew3_same_facets(); // link all blocks in lcc with same facets if they are not linked.
    lcc.display_characteristics(std::cout);

}

bool InitialMesh_boundary_connector::replace_L_facets(LCC_3& lcc, Dart_handle facet, const Polyhedron& polyhedron, const double distance){
    bool is_replace_done = false;
    std::vector<CGAL::Segment_3<K> > segments;
    int number_of_45_degrees_segments=0;
    for(LCC_3::Dart_of_orbit_range<1>::iterator vertexIt = lcc.darts_of_orbit<1>(facet).begin(),
                vertexItEnd = lcc.darts_of_orbit<1>(facet).end(); vertexIt != vertexItEnd; ++vertexIt)
    {
        Point isomorphic_point = lcc.info<0>(vertexIt).get();
        Point initialMesh_point = lcc.point(vertexIt);
        CGAL::Segment_3<K> segment = CGAL::Segment_3<K>(isomorphic_point, initialMesh_point);
        CGAL::Direction_3<K> direction = segment.direction();
        if(direction.dx() == direction.dy() || direction.dx() == direction.dz() || direction.dz() == direction.dy())
            number_of_45_degrees_segments++;
        segments.emplace_back(segment);
    }
    if(number_of_45_degrees_segments == 2) //facet could be belong to the L case
    {
        for(std::vector<CGAL::Segment_3<K> >::iterator it = segments.begin(), it2, it_end = segments.end();
            it != it_end; ++it){
            it2 = it; it2++;
            while(it2 != it_end){
                double squaredDistance = CGAL::squared_distance(*it, *it2);
                if(squaredDistance < (std::pow(distance,2)) &&  !CGAL::parallel(*it, *it2)) //little distance and they are not parallels
                {
                    //move the end segment point:
                    //1. change direction
                    Vector v1 = (*it).to_vector();
                    auto v1_x_direction = v1.direction().dx();
                    auto v1_y_direction = v1.direction().dy();
                    auto v1_z_direction = v1.direction().dz();
                    if (v1_x_direction > -0.001 && v1_x_direction < 0.001)
                        v1_x_direction = 0;

                    if (v1_y_direction > -0.001 && v1_y_direction < 0.001)
                        v1_y_direction = 0;

                    if (v1_z_direction  > -0.001 && v1_z_direction  < 0.001)
                        v1_z_direction = 0;

                    Vector v2 =(*it2).to_vector();
                    auto v2_x_direction = v2.direction().dx();
                    auto v2_y_direction = v2.direction().dy();
                    auto v2_z_direction = v2.direction().dz();
                    if (v2_x_direction > -0.001 && v2_x_direction < 0.001)
                        v2_x_direction = 0;

                    if (v2_y_direction > -0.001 && v2_y_direction < 0.001)
                        v2_y_direction = 0;

                    if (v2_z_direction  > -0.001 && v2_z_direction  < 0.001)
                        v2_z_direction = 0;

                    Vector v = CGAL::NULL_VECTOR;
                    Point p;
                    PointNormal_boundary_intersectionPoint_finder intersectionPointFinder;
                    boost::optional<Point> boostIntersectionPoint = boost::none;

                    if((v1_x_direction == v1_y_direction) || (v1_x_direction == v1_z_direction) || (v1_z_direction == v1_y_direction))
                    {
                        //std::cout<<"entro in v1 "<<std::endl;
                        v = LCC::Traits::Construct_sum_of_vectors()(v1, v2);
                        p = (*it).end();
                    }
                    if((v2_x_direction == v2_y_direction) || (v2_x_direction == v2_z_direction  ) || (v2_z_direction== v2_y_direction)){
                        // std::cout<<"entro in v2 "<<std::endl;
                        v = LCC::Traits::Construct_sum_of_vectors()(v2, v1);
                        p = (*it2).end();

                    }

                    //2. compute the new intersection point
                    if(v != CGAL::NULL_VECTOR) {
                        boostIntersectionPoint = intersectionPointFinder.findIntersecionPoint(p,polyhedron,v);

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
        is_replace_done = true;
    }
    return is_replace_done;

}

void InitialMesh_boundary_connector::replace_U_facets(LCC_3& lcc, Dart_handle facet, const Polyhedron& polyhedron, const double distance){
    std::vector<CGAL::Segment_3<K> > segments;
    for(LCC_3::Dart_of_orbit_range<1>::iterator vertexIt = lcc.darts_of_orbit<1>(facet).begin(),
                vertexItEnd = lcc.darts_of_orbit<1>(facet).end(); vertexIt != vertexItEnd; ++vertexIt)
    {
        Point isomorphic_point = lcc.info<0>(vertexIt).get();
        Point initialMesh_point = lcc.point(vertexIt);
        CGAL::Segment_3<K> segment = CGAL::Segment_3<K>(isomorphic_point, initialMesh_point);
        segments.emplace_back(segment);
    }
    for(std::vector<CGAL::Segment_3<K> >::iterator it = segments.begin(), it2, it_end = segments.end();
        it != it_end; ++it){
        it2 = it; it2++;
        while(it2 != it_end){
            double squaredDistance = CGAL::squared_distance(*it, *it2);
            if(squaredDistance < (std::pow(distance,2)) &&  !CGAL::parallel(*it, *it2)) //little distance and they are not parallels
            {
                auto v1_x_direction = (*it).direction().dx();
                auto v1_y_direction = (*it).direction().dy();
                auto v1_z_direction = (*it).direction().dz();
                if (v1_x_direction > -0.001 && v1_x_direction < 0.001)
                    v1_x_direction = 0;

                if (v1_y_direction > -0.001 && v1_y_direction < 0.001)
                    v1_y_direction = 0;

                if (v1_z_direction  > -0.001 && v1_z_direction  < 0.001)
                    v1_z_direction = 0;

                auto v2_x_direction = (*it2).direction().dx();
                auto v2_y_direction = (*it2).direction().dy();
                auto v2_z_direction = (*it2).direction().dz();
                if (v2_x_direction > -0.001 && v2_x_direction < 0.001)
                    v2_x_direction = 0;

                if (v2_y_direction > -0.001 && v2_y_direction < 0.001)
                    v2_y_direction = 0;

                if (v2_z_direction  > -0.001 && v2_z_direction  < 0.001)
                    v2_z_direction = 0;
                Vector v = CGAL::NULL_VECTOR;
                Point p, p_1, p_2;
                PointNormal_boundary_intersectionPoint_finder intersectionPointFinder;
                boost::optional<Point> boostIntersectionPoint_1 = boost::none;
                boost::optional<Point> boostIntersectionPoint_2 = boost::none;
                if(((v1_x_direction == v1_y_direction) || (v1_x_direction == v1_z_direction) || (v1_z_direction == v1_y_direction)) &&
                   ((v2_x_direction == v2_y_direction) || (v2_x_direction == v2_z_direction  ) || (v2_z_direction== v2_y_direction)))
                { //the_U_case
                    double new_length = sqrt(2) * (0.5) * Grid_maker().getGridDimension(polyhedron);

                    //set v as the normal of external facet of the intial mesh
                    //if is the U case then the normal vector of the facet is the right direction
                    v = CGAL::compute_normal_of_cell_2(lcc, facet);
                    // v e polyhedron normal are parallel
                   // TODO trovare la normale al poliedro
                    //if() {

                        //set p as a new point
                        double length = sqrt((*it).squared_length());
                        p_1 = (*it).end() + new_length * ((*it).source() - (*it).end()) / length;

                        boostIntersectionPoint_1 = intersectionPointFinder.findIntersecionPoint(p_1, polyhedron, v);
                        //set p point as a point of initial_mesh external facet vertex
                        p_1 = (*it).end();


                        //set p as a new point
                        length = sqrt((*it2).squared_length());
                        p_2 = (*it2).end() + new_length * ((*it2).source() - (*it2).end()) / length;

                        boostIntersectionPoint_2 = intersectionPointFinder.findIntersecionPoint(p_2, polyhedron, v);
                        //set p point as a point of initial_mesh external facet vertex
                        p_2 = (*it2).end();
                   // }


                }
                //2. compute the new intersection point
                if(v != CGAL::NULL_VECTOR) {
                    // std::cout<<"compute the new intersection point "<<std::endl;

//                    PointNormal_boundary_intersectionPoint_finder intersectionPointFinder;
//                    boost::optional<Point> boostIntersectionPoint = intersectionPointFinder.findIntersecionPoint(p,polyhedron,v);

                    //3. update the vertex point
                    if(boostIntersectionPoint_1.is_initialized() && boostIntersectionPoint_2.is_initialized())
                    {
                        Point p1 = boostIntersectionPoint_1.get();
                        Point p2 = boostIntersectionPoint_2.get();
                        for(LCC_3::Dart_of_orbit_range<1>::iterator vertexIt = lcc.darts_of_orbit<1>(facet).begin(),
                                    vertexItEnd = lcc.darts_of_orbit<1>(facet).end(); vertexIt != vertexItEnd; ++vertexIt)
                        {
                            if(lcc.point(vertexIt) == p_1)
                            {
                                lcc.info<0>(vertexIt) = p1;
                            }
                            if(lcc.point(vertexIt) == p_2)
                            {
                                lcc.info<0>(vertexIt) = p2;
                            }
                        }
                    }
                }
            }
            it2++;
        }
    }
}


