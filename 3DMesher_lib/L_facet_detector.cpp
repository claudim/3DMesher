#include "L_facet_detector.h"

std::vector<Dart_handle> L_facet_detector::detect_L_facets(LCC_3 &lcc) {
    std::vector<Dart_handle> L_facets = std::vector<Dart_handle>();

    External_facet_finder externalFacetFinder;
    std::vector<Dart_handle> externalFacets = externalFacetFinder.findFacets(lcc);
    std::cout<<"facce esterne "<<externalFacets.size()<<std::endl;


    //cycle over the external facet
    for(std::vector<Dart_handle >::iterator it = externalFacets.begin(), it2, it_end = externalFacets.end();
        it != it_end; ++it)
    {
       // std::cout<<" faccia "<<std::endl;
        Dart_handle facet_1 = *it;
        CGAL::Segment_3<K> facet_1_segment = compute_facet_normal_segment(lcc, facet_1);

        it2 = it; ++it2;
        while(it2 != it_end)
        {
            Dart_handle facet_2 = *it2;
            CGAL::Segment_3<K> facet_2_segment = compute_facet_normal_segment(lcc, facet_2);
            std::cout<<facet_2_segment<< " e "<<facet_1_segment<<std::endl;
            if(CGAL::do_intersect(facet_1_segment, facet_2_segment))
            {
                std::cout<<"Si intersecano"<<std::endl;
                // find the L facet
                    //find the shared point between facet_1 and facet_2
                    std::vector<Point> facet_1_and_facet_2_shared_points = this->find_shared_point(lcc, facet_1, facet_2);
                    //find the L facet
                    if(this->is_a_L_facets(lcc, facet_1,facet_1_and_facet_2_shared_points))
                    {
                        if(std::find(L_facets.begin(), L_facets.end(), facet_1) == L_facets.end())
                            L_facets.emplace_back(facet_1);
                    }
                    if(this->is_a_L_facets(lcc, facet_2,facet_1_and_facet_2_shared_points))
                    {
                        if(std::find(L_facets.begin(), L_facets.end(), facet_1) == L_facets.end())
                            L_facets.emplace_back(facet_2);
                    }
//                if(std::find(L_facets.begin(), L_facets.end(), facet_1) == L_facets.end())
//                    L_facets.emplace_back(facet_1);
//                if(std::find(L_facets.begin(), L_facets.end(), facet_2) == L_facets.end())
//                    L_facets.emplace_back(facet_2);
            }
            ++it2;
        }
    }
    std::cout<<"le facce che si intersecano"<<L_facets.size()<<std::endl;
    return L_facets;
}

CGAL::Segment_3<K> L_facet_detector::compute_facet_normal_segment(LCC_3 &lcc, Dart_handle &facet) {
    Vector facet_normal = CGAL::compute_normal_of_cell_2(lcc, facet);
    Point source = lcc.barycenter<2>(facet);
    Point target = LCC_3::Traits::Construct_translated_point_3()(source, -facet_normal);
    CGAL::Segment_3<K> facet_segment = CGAL::Segment_3<K>(source, target);

    double length = sqrt(facet_segment.squared_length());
    double new_length = 0.5;
    Point new_target = source + new_length * (target - source) / length;
    return facet_segment = CGAL::Segment_3<K>(source, new_target);
}

std::vector<Point> L_facet_detector::find_shared_point(LCC_3 & lcc, Dart_handle& facet_1, Dart_handle& facet_2){
    std::vector<Point> shared_points = std::vector<Point>();

    for(LCC_3::Dart_of_orbit_range<1>::iterator vertexIt1 = lcc.darts_of_orbit<1>(facet_1).begin(),
                vertexItEnd1 = lcc.darts_of_orbit<1>(facet_1).end();vertexIt1 != vertexItEnd1 ;++vertexIt1 ){
        for(LCC_3::Dart_of_orbit_range<1>::iterator vertexIt2 = lcc.darts_of_orbit<1>(facet_2).begin(),
                    vertexItEnd2 = lcc.darts_of_orbit<1>(facet_2).end(); vertexIt2 != vertexItEnd2 ;++vertexIt2 ){
            Point p1 = lcc.point(vertexIt1);
            if(p1 == lcc.point(vertexIt2))
            {
                shared_points.emplace_back(p1);
                break;
            }
        }
    }
    return shared_points;
}

bool L_facet_detector::is_a_L_facets(LCC_3 &lcc, Dart_handle &facet, std::vector<Point> shared_points) {
    for(LCC_3::Dart_of_orbit_range<1>::iterator vertexIt1 = lcc.darts_of_orbit<1>(facet).begin(),
                vertexItEnd1 = lcc.darts_of_orbit<1>(facet).end();vertexIt1 != vertexItEnd1 ;++vertexIt1 ){
        if(lcc.point(vertexIt1) == shared_points.at(0))
        {
            if(lcc.point(lcc.next(vertexIt1)) == shared_points.at(1))
            {

            }
        }
        if(lcc.point(vertexIt1) == shared_points.at(1))
        {
            if(lcc.point(lcc.next(vertexIt1)) == shared_points.at(0))
            {

            }

        }

    }
    return false;
}
