

#include "Block_maker.h"

Dart_handle Block_maker::make_block(LCC_3& lcc, const Point& basepoint, FT& lg){
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