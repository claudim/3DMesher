#include <iostream>
#include "Block_maker.h"

int main(int argc, char* argv[]) {

    try {
        //lettura lancia errore

        // testo il calcolo della normale ad un punto
        LCC_3 lcc;
        Block_maker b;
        Point p1 = Point(2,2,2);
        FT lg = 2;
        Dart_handle p_dart;
        Dart_handle block1 = b.make_cube(lcc, p1, lg);
        for(LCC_3::One_dart_per_incident_cell_range<0,3>::iterator it = lcc.one_dart_per_incident_cell<0,3>(block1).begin();
        it.cont(); ++it)
        {
            if(lcc.point(it) == Point(4,2,4))
            {
                p_dart = it;
            }
        }
        FT number_of_incident_facets = 0;
        for(LCC_3::One_dart_per_incident_cell_range<2,0>::iterator it = lcc.one_dart_per_incident_cell<2,0>(p_dart).begin();
            it.cont(); ++it)
        {
            number_of_incident_facets++;
        }
        std::cout<<number_of_incident_facets<<std::endl;

        Dart_handle block2 = b.make_cube(lcc, Point(4,2,2), lg);
        number_of_incident_facets = 0;
        for(LCC_3::One_dart_per_incident_cell_range<2,0>::iterator it = lcc.one_dart_per_incident_cell<2,0>(p_dart).begin();
            it.cont(); ++it)
        {
            number_of_incident_facets++;
        }
        std::cout<<number_of_incident_facets<<std::endl;
        lcc.sew3_same_facets();
        number_of_incident_facets = 0;
        for(LCC_3::One_dart_per_incident_cell_range<2,0>::iterator it = lcc.one_dart_per_incident_cell<2,0>(p_dart).begin();
            it.cont(); ++it)
        {
            number_of_incident_facets++;
        }
        std::cout<<number_of_incident_facets<<std::endl;

    }
    catch (std::ios_base::failure e) {
        std::cerr << "Exception opening/reading/closing file\n";
    }
    return EXIT_SUCCESS;
}
