#include "InitialMesh_boundary_connector.h"

//template<typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits>
void InitialMesh_boundary_connector::connect(LCC_3 &lcc, const Polyhedron &polyhedron) {


    External_facet_finder externalFacetFinder;

    const std::vector<Dart_const_handle> &externalFacets = externalFacetFinder.find(lcc);

    std::vector<Dart_handle> newBlocks;

    PointNormal_boundary_intersectionPoint_finder pointNormalBoundaryIntersectionPointFinder;

    for( Dart_const_handle facet : externalFacets){

        std::vector<std::pair<Point, Point>> hexahedronPoints;
       // std::vector< Point > hexahedronPoints;

        for(LCC_3::Dart_of_orbit_const_range<1>::const_iterator vertexIt = lcc.darts_of_orbit<1>(facet).begin(),
                    vertexItEnd = lcc.darts_of_orbit<1>(facet).end(); vertexIt != vertexItEnd; ++vertexIt) {
//for(LCC_3::One_dart_per_incident_cell_range<0, 2, 3>::const_iterator vertexIt(lcc.one_dart_per_incident_cell<0, 2, 3>(facet).begin()),
//                vertexItEnd(lcc.one_dart_per_incident_cell<0, 2, 3>(facet).end()); vertexIt != vertexItEnd; ++vertexIt) {

            const Point &p = lcc.point(vertexIt);
            Point intersectionPoint = pointNormalBoundaryIntersectionPointFinder.findIntersecionPoint(lcc, vertexIt,
                                                                                                      polyhedron);

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

            hexahedronPoints.emplace_back(rounded_point,lcc.point(vertexIt));
            //hexahedronPoints.push_back(intersectionPoint);
          //  hexahedronPoints.push_back(rounded_point);
            //  hexahedronPoints.push_back(lcc.point(vertexIt));

            std::cout<<std::endl<<rounded_point<<", "<<lcc.point(vertexIt);
        }

        std::cout<<"hexPoint size "<<hexahedronPoints.size()<<std::endl;
        std::unique(hexahedronPoints.begin(), hexahedronPoints.end());
        std::cout<<"hexPoint size "<<hexahedronPoints.size()<<std::endl;
        hexahedronPoints.size();
//        std::pair<Point, Point> supportVariablePoint = hexahedronPoints[1];
//        Point supportVariablePoint = hexahedronPoints[1];
//        hexahedronPoints[1] = hexahedronPoints[6];
//        hexahedronPoints[6] = supportVariablePoint;
//        supportVariablePoint = hexahedronPoints[2];
//        hexahedronPoints[2] = hexahedronPoints[4];
//        hexahedronPoints[4] = supportVariablePoint;
//        supportVariablePoint = hexahedronPoints[3];
//        hexahedronPoints[3] = hexahedronPoints[4];
//        hexahedronPoints[4] = supportVariablePoint;
//        supportVariablePoint = hexahedronPoints[5];
//        hexahedronPoints[5] = hexahedronPoints[6];
//        hexahedronPoints[6] = supportVariablePoint;
//        supportVariablePoint = hexahedronPoints[6];
//        hexahedronPoints[6] = hexahedronPoints[7];
//        hexahedronPoints[7] = supportVariablePoint;



        Dart_handle newHexahedron = lcc.make_hexahedron(hexahedronPoints[0].second,
                                                        hexahedronPoints[1].second,
                                                        hexahedronPoints[2].second,
                                                        hexahedronPoints[3].second,
                                                        hexahedronPoints[3].first,
                                                        hexahedronPoints[0].first,
                                                        hexahedronPoints[1].first,
                                                        hexahedronPoints[2].first);
        newBlocks.push_back(newHexahedron);

//        lcc.make_hexahedron(hexahedronPoints[3].second,
//                            hexahedronPoints[2].second,
//                            hexahedronPoints[1].second,
//                            hexahedronPoints[0].second,
//                            hexahedronPoints[0].first,
//                            hexahedronPoints[1].first,
//                            hexahedronPoints[2].first,
//                            hexahedronPoints[3].first);





    }
    std::cout<<std::endl;
    lcc.display_characteristics(std::cout);


    for(Dart_handle justCreatedBlock : newBlocks){
        LCC_3::One_dart_per_cell_range<3, 3>::iterator lcc_cells_iterator = lcc.one_dart_per_cell<3, 3>().begin(),
                lcc_cells_end_iterator = lcc.one_dart_per_cell<3, 3>().end();
        while(lcc_cells_iterator != lcc_cells_end_iterator)
        {
            linkBlock(lcc, justCreatedBlock, lcc_cells_iterator);
            ++lcc_cells_iterator;
        }
//        for (LCC_3::One_dart_per_cell_range<3, 3>::iterator lcc_cells_iterator = lcc.one_dart_per_cell<3, 3>().begin(),
//                     lcc_cells_end_iterator = lcc.one_dart_per_cell<3, 3>().end();
//             lcc_cells_iterator != lcc_cells_end_iterator; ++lcc_cells_iterator) {
//            linkBlock(lcc, justCreatedBlock, lcc_cells_iterator);
//        }
    }




    //std::cout<<std::endl<<lcc.sew3_same_facets();

    lcc.display_characteristics(std::cout);

}

//template<typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits>
void InitialMesh_boundary_connector::linkBlock(LCC_3 &lcc, Dart_handle &block1, Dart_handle &block2) {

  //  lcc.sew3_same_facets();

    Dart_handle block1_dart_to_sew = lcc.null_dart_handle, block2_dart_to_sew = lcc.null_dart_handle;

    if(block1 == block2) return;
    //block1!=block2
    //colleghiamo attraverso facce

    bool linked = false;

    //per ogni faccia block1
    for(LCC_3::One_dart_per_incident_cell_range<2,3,3>::iterator block1_facet_it = lcc.one_dart_per_incident_cell<2,3,3>(block1).begin(),
                block1_facet_end_it = lcc.one_dart_per_incident_cell<2,3,3>(block1).end();
        block1_facet_it != block1_facet_end_it; ++block1_facet_it) {
        if (!linked) {
            //per ogni faccia block2
            for (LCC_3::One_dart_per_incident_cell_range<2, 3, 3>::iterator block2_facet_it = lcc.one_dart_per_incident_cell<2, 3, 3>(
                    block2).begin(),
                         block2_facet_end_it = lcc.one_dart_per_incident_cell<2, 3, 3>(block2).end();
                 block2_facet_it != block2_facet_end_it; ++block2_facet_it) {
                int j = 1;
                FT number_of_equal_points = 0;
//                for (LCC_3::Dart_of_cell_range<0, 3>::iterator block1_vertex_it = lcc.darts_of_cell<0, 3>(block1_facet_it).begin(),
//                             block1_vertex_end_it = lcc.darts_of_cell<0, 3>(block1_facet_it).end();
//                     block1_vertex_it != block1_vertex_end_it;
//                     ++block1_vertex_it) {

                for (LCC_3::One_dart_per_incident_cell_range<0,2,3>::iterator block1_vertex_it = lcc.one_dart_per_incident_cell<0,2,3>(block1_facet_it).begin(),
                             block1_vertex_end_it = lcc.one_dart_per_incident_cell<0,2,3>(block1_facet_it).end();
                     block1_vertex_it != block1_vertex_end_it;
                     ++block1_vertex_it) {
                    int i = 1;
                    for (LCC_3::One_dart_per_incident_cell_range<0,2,3>::iterator block2_vertex_it = lcc.one_dart_per_incident_cell<0,2,3>(block2_facet_it).begin(),
                                 block2_vertex_end_it = lcc.one_dart_per_incident_cell<0,2,3>(block2_facet_it).end();
                         block2_vertex_it != block2_vertex_end_it;
                         ++block2_vertex_it) {
                        Point pointF1 = lcc.point(block1_vertex_it) ;
                        Point pointF2 = lcc.point(block2_vertex_it);
                        if (pointF1 == pointF2) {
                            number_of_equal_points++;
                            break;
                        }
                    }
                }
                if (number_of_equal_points == 4) {
                    std::cout<<"qui1"<<std::endl;
                    if(lcc.point(block1_facet_it) == lcc.point(lcc.opposite(block2_facet_it)) &&  lcc.point(lcc.opposite(block1_facet_it)) == lcc.point(block2_facet_it)) {
                        std::cout<<"sto legando1"<<std::endl;
                        int dim = block2_facet_it->dimension;
                        if(lcc.is_sewable<3>(block1_facet_it, block2_facet_it)){
                            block1_dart_to_sew = block1_facet_it;
                            block2_dart_to_sew = block2_facet_it;
                            std::cout<<"is sewable"<<std::endl;
                            // lcc.sew<3>(block2_facet_it, block1_facet_it);
                            linked = true;
                            //return;
                        }
                    }
                    else
                    {
                        std::cout<<"qui2"<<std::endl;
//                        for (LCC_3::One_dart_per_incident_cell_range<0,2,3>::iterator block2_vertex_it2 = lcc.one_dart_per_incident_cell<0,2,3>(block2_facet_it).begin(),
//                                     block2_vertex_end_it2 = lcc.one_dart_per_incident_cell<0,2,3>(block2_facet_it).end();
//                             block2_vertex_it2 != block2_vertex_end_it2;
//                             ++block2_vertex_it2) {
                            Dart_handle block2_facet_it2 = block2_facet_it;
                            bool firstTime = true;
                            while(firstTime || block2_facet_it2 != block2_facet_it)
                            {
                            std::cout<<"qui3"<<std::endl;
                                firstTime = false;
                            if(lcc.point(block1_facet_it) == lcc.point(lcc.opposite(block2_facet_it2)) &&  lcc.point(lcc.opposite(block1_facet_it)) == lcc.point(block2_facet_it2)) {
                                std::cout<<"sto legando2"<<std::endl;
//                                lcc.sew<3>(block1_facet_it, block2_vertex_it2);
//                                linked = true;
                                if(lcc.is_sewable<3>(block1_facet_it, block2_facet_it2)){
                                    block1_dart_to_sew = block1_facet_it;
                                    block2_dart_to_sew = block2_facet_it2;
                                    std::cout<<"is sewable"<<std::endl;
                                    // lcc.sew<3>(block2_facet_it, block1_facet_it);
                                    linked = true;
                                }
                            }
                            block2_facet_it2 = lcc.beta(block2_facet_it2, 1);
                        }
                        std::cout<<"ho terminato il ciclo e so che ci sono 2 facce in comune "<<std::endl;
                    }
                }
            }


//                Dart_handle opposite_vertex_dart = lcc.opposite(block2_facet_it);
//                if (lcc.point(opposite_vertex_dart) == lcc.point(block1_facet_it)) {
//                    // in questo caso potrebbero avere una faccia in comune
//                    //necessario indagare ulteriormente
//
//                    lcc.sew<3>(block1_facet_it, block2_facet_it);
//                    linked = true;
//                    return;
//                }

        }
    }
    if (block1_dart_to_sew != lcc.null_dart_handle && block2_dart_to_sew != lcc.null_dart_handle)
    {
        std::cout<<"sono legando i 2 blocchi"<< std::endl;
        lcc.sew<3>(block1_dart_to_sew, block2_dart_to_sew);

    }
    std::cout<<"ho legato i 2 blocchi"<< std::endl;


}