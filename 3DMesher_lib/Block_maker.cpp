

#include "Block_maker.h"

Dart_handle Block_maker::make_cube(LCC_3& lcc, const Point& basepoint, FT& lg){
    return lcc.make_hexahedron(basepoint,
                               Traits::Construct_translated_point()
                                       (basepoint, Traits::Vector(lg, 0, 0)),
                               Traits::Construct_translated_point()
                                       (basepoint, Traits::Vector(lg, lg, 0)),
                               Traits::Construct_translated_point()
                                       (basepoint, Traits::Vector(0, lg, 0)),
                               Traits::Construct_translated_point()
                                       (basepoint, Traits::Vector(0, lg, lg)),
                               Traits::Construct_translated_point()
                                       (basepoint, Traits::Vector(0, 0, lg)),
                               Traits::Construct_translated_point()
                                       (basepoint, Traits::Vector(lg, 0, lg)),
                               Traits::Construct_translated_point()
                                       (basepoint, Traits::Vector(lg, lg, lg)));
}

//template<typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits, typename Point, typename Point>
Dart_handle Block_maker::make_block(LCC_3 &lcc, const std::vector<Point> &vertices) {

    return lcc.make_hexahedron(vertices[0],
                        vertices[1],
                        vertices[2],
                        vertices[3],
                        vertices[4],
                        vertices[5],
                        vertices[6],
                        vertices[7]);
}
