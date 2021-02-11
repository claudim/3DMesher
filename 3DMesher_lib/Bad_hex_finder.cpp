#include "Bad_hex_finder.h"

bool Bad_hex_finder::is_hex_bad(const Dart_handle& aHex, LCC_3& lcc) {

    std::vector<std::array<double, 3> > hex_vertices;
    std::array<double, 3> point{};
    for (LCC_3::One_dart_per_incident_cell_range<0, 3>::iterator vertex_it = lcc.one_dart_per_incident_cell<0, 3>(
            aHex).begin(),
                 vertex_it_end = lcc.one_dart_per_incident_cell<0, 3>(aHex).end();
         vertex_it != vertex_it_end; ++vertex_it) {
        point[0] = lcc.point(vertex_it).x();
        point[1] = lcc.point(vertex_it).y();
        point[2] = lcc.point(vertex_it).z();
        hex_vertices.emplace_back(point);
    }
    HexMetricVals vals{};
    std::array<double, 3> *pArray = hex_vertices.data();
    v_hex_quality(hex_vertices.size(), reinterpret_cast<const double (*)[3]>(pArray), V_HEX_SCALED_JACOBIAN, &vals);
    if(vals.scaled_jacobian <= scaled_jacobian_threshold){
        return true;
    }else{
        return false;
    }
}

//template<typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits, typename allocator, typename allocator, typename Linear_cell_complex_traits, typename Linear_cell_complex_traits, typename allocator>
void Bad_hex_finder::find_bad_hexes(LCC_3 &lcc, std::vector<Dart_handle> &bad_hexes) {

    for(LCC_3::One_dart_per_cell_range<3>::iterator hex_it = lcc.one_dart_per_cell<3>().begin(),
                hex_it_end = lcc.one_dart_per_cell<3>().end(); hex_it != hex_it_end; ++hex_it) {
        if(is_hex_bad(hex_it, lcc)){
            bad_hexes.emplace_back(hex_it);
        }
    }
}

void Bad_hex_finder::setScaledJacobianThreshold(float scaledJacobianThreshold) {
    scaled_jacobian_threshold = scaledJacobianThreshold;
}
