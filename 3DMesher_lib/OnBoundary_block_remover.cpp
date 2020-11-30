#include "OnBoundary_block_remover.h"

//template<typename Linear_cell_complex_traits, typename allocator, typename allocator, typename Linear_cell_complex_traits>
void OnBoundary_block_remover::removeBlocks(LCC_3 &lcc, const Polyhedron &polyhedron) {
    if(!lcc.is_empty())
    {
        for (LCC_3::One_dart_per_cell_range<3, 3>::iterator lcc_cells_iterator = lcc.one_dart_per_cell<3, 3>().begin(),
                     lcc_cells_end_iterator = lcc.one_dart_per_cell<3, 3>().end();
             lcc_cells_iterator != lcc_cells_end_iterator; ++lcc_cells_iterator) {
//            if (is_block_to_be_removed(lcc, lcc_cells_iterator, polyhedron)) {
//                removeBlock(lcc, lcc_cells_iterator);
//            }
            if(is_block_on_boundary(lcc, lcc_cells_iterator, polyhedron)){
                removeBlock(lcc, lcc_cells_iterator);
            }
        }
    }
}


void OnBoundary_block_remover::removeBlocks(LCC_3 &lcc, const Polyhedron &polyhedron, const double &distance) {
    //remove all onBoundary blocks
    if(!lcc.is_empty())
    {
        for (LCC_3::One_dart_per_cell_range<3, 3>::iterator lcc_cells_iterator = lcc.one_dart_per_cell<3, 3>().begin(),
                     lcc_cells_end_iterator = lcc.one_dart_per_cell<3, 3>().end();
             lcc_cells_iterator != lcc_cells_end_iterator; ++lcc_cells_iterator) {
//            if (is_block_to_be_removed(lcc, lcc_cells_iterator, polyhedron, distance)) {
//                removeBlock(lcc, lcc_cells_iterator);
//            }
            if(is_block_on_boundary(lcc, lcc_cells_iterator, polyhedron)){
                removeBlock(lcc, lcc_cells_iterator);
            }
        }
        //remove all blocks too close to the boundary.
        if(!lcc.is_empty()){
            for (LCC_3::One_dart_per_cell_range<3, 3>::iterator lcc_cells_iterator = lcc.one_dart_per_cell<3, 3>().begin(),
                         lcc_cells_end_iterator = lcc.one_dart_per_cell<3, 3>().end();
                 lcc_cells_iterator != lcc_cells_end_iterator; ++lcc_cells_iterator) {
                if(is_block_too_close_to_the_boundary(lcc, lcc_cells_iterator, polyhedron, distance)){
                    removeBlock(lcc, lcc_cells_iterator);
                }
            }
        }
    }
}


bool OnBoundary_block_remover::is_block_on_boundary(const LCC_3 &lcc,
                                                      const Dart_handle& block,
                                                      const Polyhedron &polyhedron) {
    bool block_onBoundary = false;
    int number_of_internal_points = 0;
    if (!lcc.is_empty()) {
        Vertex_location_finder vertexLocationFinder = Vertex_location_finder(polyhedron);
        //per ogni vertice del cubo
        for (LCC_3::One_dart_per_incident_cell_const_range<0, 3>::const_iterator vertex_it = lcc.one_dart_per_incident_cell<0, 3>(
                block).begin(),
                     vertex_end_it = lcc.one_dart_per_incident_cell<0, 3>(block).end();
             vertex_it != vertex_end_it; ++vertex_it) {
            Point point = lcc.point(vertex_it);
            if (vertexLocationFinder.is_point_inside_polyhedron(point)) {
                number_of_internal_points++;
            }
        }
        if (number_of_internal_points > 0 && number_of_internal_points < 8) {
            block_onBoundary = true;
        }
    }
    return block_onBoundary;
}

//precondition: every on-boundary block have already been removed
bool OnBoundary_block_remover::is_block_too_close_to_the_boundary(const LCC_3 &lcc,
                                                                  const Dart_handle& block,
                                                                  const Polyhedron &polyhedron,
                                                                  const double &distance){

    //using 3cell_barycenter-boundary distance
    bool block_too_close = false;


    if(!lcc.is_empty()) {
//      //detect all external blocks (here external means block is on the boundary lcc, not external to the polyhedron)
//        External_facet_finder externalFacetFinder;
//        std::vector<Dart_const_handle> facets = externalFacetFinder.find(lcc);
//        std::vector<Dart_const_handle> externalHexes;
//        for(Dart_const_handle facet: facets)
//        {
//            if(lcc.one_dart_per_incident_cell<3,2,3>(facet).size() > 0) {
//                Dart_const_handle hex = lcc.one_dart_per_incident_cell<3, 2, 3>(facet).begin();
//                if (std::find(externalHexes.begin(), externalHexes.end(), hex) == externalHexes.end()) {
//                    // aggiungi cubo esterno
//                    externalHexes.emplace_back(hex);
//                }
//            }
//        }

        // compute barycenter for each external blocks
        Vertex_location_finder vertexLocationFinder = Vertex_location_finder(polyhedron);
        Point barycenter_point = lcc.barycenter<3>(block);
        //compute distance from barycenter-point detected to polyhedron
        double squared_distance_Barycenter_Polyhedron = vertexLocationFinder.getAabbTree().squared_distance(barycenter_point);
        double distance_Barycenter_Polyhedron = sqrt(squared_distance_Barycenter_Polyhedron);
        // if the computed distance is <= distance then block is to be removed
        if (distance_Barycenter_Polyhedron <= distance)
        {
            block_too_close = true;
        }
    }
    return block_too_close;
}









//precondition: every on-boundary block have already been removed
bool OnBoundary_block_remover::is_block_too_close_to_the_boundary2(const LCC_3 &lcc,
                                                                  const Dart_handle& block,
                                                                  const Polyhedron &polyhedron,
                                                                  const double &distance){

    //using point-boundary distance
    bool block_too_close = false;
    if(!lcc.is_empty()) {
        Vertex_location_finder vertexLocationFinder = Vertex_location_finder(polyhedron);
        // per ogni faccia del cubo controllo che almeno 3 punti siano ad una distanza
        LCC_3::One_dart_per_incident_cell_const_range<2, 3>::const_iterator
                facet_it = lcc.one_dart_per_incident_cell<2,3>(block).begin(),
                facet_itend = lcc.one_dart_per_incident_cell<2, 3>(block).end();
        while ( facet_it != facet_itend && !block_too_close) {
            FT number_of_points_too_close_to_the_boundary = 0;
            for(LCC_3::One_dart_per_incident_cell_const_range<0,2,3>::const_iterator vertex_it = lcc.one_dart_per_incident_cell<0,2,3>(facet_it).begin(),
                        vertex_end_it = lcc.one_dart_per_incident_cell<0,2,3>(facet_it).end(); vertex_it!= vertex_end_it; ++vertex_it )
            {
                Point point = lcc.point(vertex_it);
                bool is_point_too_close = vertexLocationFinder.is_point_too_close_to_the_boundary(point, distance);
                if(is_point_too_close)
                {
                    number_of_points_too_close_to_the_boundary++;
                }
            }
            if(number_of_points_too_close_to_the_boundary > 2) //is  3 or 4
                block_too_close = true;
            ++facet_it;
        }
    }
    return block_too_close;
}



bool OnBoundary_block_remover::is_block_to_be_removed(const LCC_3 &lcc,
                                                      const Dart_handle& block,
                                                      const Polyhedron &polyhedron,
                                                      const double &distance) {
    //using point-boundary distance
    bool toRemove = false;
    int number_of_internal_points = 0;
    if(!lcc.is_empty()) {
        Vertex_location_finder vertexLocationFinder = Vertex_location_finder(polyhedron);
        // per ogni faccia del cubo controllo che almeno 3 punti siano ad undistanza
        LCC_3::One_dart_per_incident_cell_const_range<2, 3>::const_iterator
                facet_it = lcc.one_dart_per_incident_cell<2,3>(block).begin(),
                facet_itend = lcc.one_dart_per_incident_cell<2, 3>(block).end();
        while ( facet_it != facet_itend && !toRemove) {
            FT points_number_of_too_close_to_the_boundary = 0;
            for(LCC_3::One_dart_per_incident_cell_const_range<0,2,3>::const_iterator vertex_it = lcc.one_dart_per_incident_cell<0,2,3>(facet_it).begin(),
                        vertex_end_it = lcc.one_dart_per_incident_cell<0,2,3>(facet_it).end(); vertex_it!= vertex_end_it; ++vertex_it )
            {
                Point point = lcc.point(vertex_it);
                if (vertexLocationFinder.is_point_inside_polyhedron(point)) {
                    number_of_internal_points++;
                    bool is_point_too_close = vertexLocationFinder.is_point_too_close_to_the_boundary(point, distance);
                    if(is_point_too_close)
                    {
                        points_number_of_too_close_to_the_boundary++;
                    }
                }
            }
            if(points_number_of_too_close_to_the_boundary > 2) //is  3 or 4
                    toRemove = true;
            ++facet_it;
        }
    }
    if ( number_of_internal_points < 8) {
        toRemove = true;
    }
    return toRemove;

////using only number of internal point
//    bool toRemove = false;
//    int number_of_internal_points = 0;
//    if(!lcc.is_empty()) {
//        Vertex_location_finder vertexLocationFinder = Vertex_location_finder(polyhedron);
//        // per tutti i vertici del cubo
//        LCC_3::One_dart_per_incident_cell_const_range<0, 3>::const_iterator
//                it = lcc.one_dart_per_incident_cell<0,3>(block).begin(),
//                itend = lcc.one_dart_per_incident_cell<0, 3>(block).end();
//        while ( it != itend && !toRemove) {
//            //if (is_point_inside_polyhedron(lcc.point(it), inside)) {
//            Point point = lcc.point(it);
//            if (vertexLocationFinder.is_point_inside_polyhedron(point)) {
//                number_of_internal_points++;
//                toRemove = vertexLocationFinder.is_point_too_close_to_the_boundary(point, distance);
//            }
//            ++it;
//        }
//    }
//    if (number_of_internal_points > 0 &&  number_of_internal_points < 8) {
//        toRemove = true;
//    }
//    return toRemove;

    //using barycenter
//    bool toRemove = false;
//    if(!lcc.is_empty()) {
//        Vertex_location_finder vertexLocationFinder = Vertex_location_finder(polyhedron);
//        // per tutte le facce del cubo
//        LCC_3::One_dart_per_incident_cell_const_range<2, 3>::const_iterator
//                it = lcc.one_dart_per_incident_cell<2,3>(block).begin(),
//                itend = lcc.one_dart_per_incident_cell<2, 3>(block).end();
//        while ( it != itend && !toRemove) {
//            Point barycenter = lcc.barycenter<2>(it);
//            double distanceBarycenterPolyhedron = vertexLocationFinder.getAabbTree().squared_distance(barycenter);
//            //Point point = lcc.point(it);
//            distanceBarycenterPolyhedron = sqrt(distanceBarycenterPolyhedron);
//            if ( distanceBarycenterPolyhedron < distance) {
//                toRemove = true;
//           }
//            ++it;
//        }
//    }
   // return toRemove;

}

//template<typename Linear_cell_complex_traits, typename allocator, typename allocator, typename Linear_cell_complex_traits>
bool OnBoundary_block_remover::is_block_to_be_removed(const LCC_3 &lcc,
                                                      const Dart_handle& block,
                                                      const Polyhedron &polyhedron) {

    bool toRemove = false;
    int number_of_internal_points = 0;
    if(!lcc.is_empty()) {
        Vertex_location_finder vertexLocationFinder = Vertex_location_finder(polyhedron);
        // per tutti i vertici del cubo
        for (LCC_3::One_dart_per_incident_cell_const_range<0, 3>::const_iterator
                     it = lcc.one_dart_per_incident_cell<0,3>(block).begin(),
                     itend = lcc.one_dart_per_incident_cell<0, 3>(block).end(); it != itend; ++it) {
            //if (is_point_inside_polyhedron(lcc.point(it), inside)) {
            if (vertexLocationFinder.is_point_inside_polyhedron(lcc.point(it))) {
                number_of_internal_points++;
            }
        }
    }
    if (number_of_internal_points > 0 &&  number_of_internal_points < 8) {
        toRemove = true;
    }
    return toRemove;
}

void OnBoundary_block_remover::removeBlock(LCC_3& lcc, Dart_handle& blockToRemove) {
    lcc.remove_cell<3>(blockToRemove);
}