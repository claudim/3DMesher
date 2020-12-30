#ifndef INC_3DMESHER_L_FACET_DETECTOR_H
#define INC_3DMESHER_L_FACET_DETECTOR_H

#include "MyLCC.h"
#include "External_facet_finder.h"
#include "Grid_maker.h"

class L_facet_detector {

public:

    std::vector<Dart_handle> detect_L_facets(LCC_3 &lcc);

    CGAL::Segment_3<K> compute_facet_normal_segment(LCC_3 &lcc, Dart_handle &facet);

    std::vector<Point> find_shared_point(LCC_3 &lcc, Dart_handle& facet_1, Dart_handle& facet_2);

    bool is_a_L_facets(LCC_3 &lcc, Dart_handle &facet, std::vector<Point> shared_points);
};




#endif //INC_3DMESHER_L_FACET_DETECTOR_H
