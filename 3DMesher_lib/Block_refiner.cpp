#include "Block_refiner.h"

void Block_refiner::refineBlock(LCC_3 &lcc, Dart_handle &blockToRefine, const std::vector<Point> &featuresPoints,
                                double distance) {
    // calcolo le distanze di ogni punto dell'esaedro e lo salvo assieme ad un riferimento del blocco in una mappa <distance, dart>
    //ordino secondo le distanze
    //il primo con distanza inferiore a tot viene spostato al punto

    //for each features vertex point
    for(Point p: featuresPoints) {
        //for each point of hexahedron check the point of minimum distance and move it in the fixed feature vertex
        Dart_handle vertexToMove = lcc.null_dart_handle;
        double minSquaredDistanceFromPoint = std::pow(distance,2);
        if(!lcc.is_empty()) {
            for (LCC_3::One_dart_per_incident_cell_range<0, 3, 3>::iterator vertex_it = lcc.one_dart_per_incident_cell<0, 3, 3>(
                    blockToRefine).begin(),
                         vertex_end_it = lcc.one_dart_per_incident_cell<0, 3, 3>(blockToRefine).end();
                 vertex_it != vertex_end_it; ++vertex_it) {
                Point blockVertexPoint = lcc.point(vertex_it);
                FT squaredDistance = CGAL::squared_distance(p, blockVertexPoint);

                //osservazione: se due distanze fossero uguali cosa fare?? magari dovrei scegliere sulla base della distanza dagli altri punti che sono connessi a lui??
                if (squaredDistance < minSquaredDistanceFromPoint && squaredDistance > 0) {
                    minSquaredDistanceFromPoint = squaredDistance;
                    vertexToMove = vertex_it;
                }
            }
            if (vertexToMove != lcc.null_dart_handle) //if there is a vertex to move
            {
                lcc.point(vertexToMove) = p; //move the vertex point to p
            }
        }
    }
}

//template<typename Linear_cell_complex_traits, typename allocator, typename allocator, typename Linear_cell_complex_traits, typename Point, typename Point, typename FT>
void Block_refiner::refineBlocks(LCC_3 &lcc, const std::vector<Point> &points, FT distance) {
    if(!lcc.is_empty() && distance > 0)
    {
        // find external facets
        External_facet_finder externalFacetFinder;
        std::vector<Dart_handle> externalFacets = externalFacetFinder.findFacets(lcc);

        // find external blocks
        std::vector<Dart_handle> externalBlocks;
        for(Dart_handle facet: externalFacets)
        {
            Dart_handle blockToRefine = lcc.one_dart_per_incident_cell<3, 2, 3>(facet).begin();
            externalBlocks.emplace_back(blockToRefine);
        }
        //refine every external blocks
        for(Dart_handle block: externalBlocks)
        {
            this->refineBlock(lcc, block, points, distance);
        }

//refine every  blocks
//        for (LCC_3::One_dart_per_cell_range<3, 3>::iterator lcc_cells_iterator = lcc.one_dart_per_cell<3, 3>().begin(),
//                     lcc_cells_end_iterator = lcc.one_dart_per_cell<3, 3>().end();
//             lcc_cells_iterator != lcc_cells_end_iterator; ++lcc_cells_iterator) {
//
//            this->refineBlock(lcc, lcc_cells_iterator, points, distance);
//        }
    }
}
