#include "../Include/catch.hpp"
#include "test_config.h"
#include "Block_maker.h"
#include "External_facet_finder.h"

static LCC_3 make_grid_3X3();
TEST_CASE("Must_find_external_facets","[External_facet_finder]")
{
    SECTION("must_find_54_external_facets"){
            Point basePoint1 = Point(0,0,0);  FT lg = 2;
    LCC_3 lcc = make_grid_3X3();

    External_facet_finder externalCellFinder = External_facet_finder();
    std::vector<Dart_const_handle> externalCell = externalCellFinder.find(lcc);
    REQUIRE(externalCell.size() == 54);
    }


    SECTION( "must_find_6_external_facets" ) {
        Point externalBasePoint = Point(-35, -35, -35);
        FT lg = 1;
        LCC_3 lcc;
        Block_maker blockMaker = Block_maker();
        Dart_handle block = blockMaker.make_block(lcc, externalBasePoint, lg);
        External_facet_finder externalCellFinder = External_facet_finder();
        std::vector<Dart_const_handle> externalFacets = externalCellFinder.find(lcc);
        REQUIRE(externalFacets.size() == 6);
    }

}

static LCC_3 make_grid_3X3()
{
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    FT NUMBER_OF_DARTS_PER_CUBE = 24;
    int  i=0, j=0;
    double x_min_p, y_min_p, z_min_p;
    FT grid_dimension = 2;
    //todo cercare di usare il one_dart_per_cell
    z_min_p = 0;
    for (int z = 0; z < 3; z++) {
        y_min_p =0;
        int add_z = z * j * i * NUMBER_OF_DARTS_PER_CUBE;

        for ( j = 0; j < 3; j++) {
            x_min_p = 0;
            for (i = 0; i < 3; i++) {
                Point basePoint = Point(x_min_p, y_min_p, z_min_p);
                Dart_handle dart_handle_of_cube = blockMaker.make_block(lcc, basePoint, grid_dimension);
            }
            LCC_3::Dart_range::iterator start_iterator = lcc.darts().begin();
            std::advance(start_iterator, NUMBER_OF_DARTS_PER_CUBE * j * i + add_z);
            LCC_3::Dart_range::iterator end_iterator = lcc.darts().end();


            //collego gli elementi adiacenti su tutta una fila
            for (LCC_3::Dart_range::iterator it = start_iterator,
                         itend = end_iterator;
                 std::distance(it, itend) > NUMBER_OF_DARTS_PER_CUBE;)  // std::distance(it, itend)>24
            {

                LCC_3::Dart_range::iterator first_dart_iterator = it;
                std::advance(it,
                             NUMBER_OF_DARTS_PER_CUBE); // it +=24 avanza l'iteratore di 24 poichè in ogni cubo ha 24 dardi. io devo unire primo e ssecondo cubo
                LCC_3::Dart_range::iterator second_dart_iterator = it;
                lcc.sew<3>(lcc.beta(second_dart_iterator, 2), lcc.beta(first_dart_iterator, 1, 1, 2));

            }


            if (j != 0) {
                //collego gli elementi adiacenti tra 2 righe
                LCC_3::Dart_range::iterator start_iterator_first_row = lcc.darts().begin();
                std::advance(start_iterator_first_row,
                             NUMBER_OF_DARTS_PER_CUBE * (j - 1) * i + add_z); // punta al 1°cubo di una riga sotto

                LCC_3::Dart_range::iterator start_iterator_second_row = lcc.darts().begin();
                std::advance(start_iterator_second_row,
                             NUMBER_OF_DARTS_PER_CUBE * (j) * i + add_z); //punta al 1° cubo di una riga sopra la riga di sotto

                for (LCC_3::Dart_range::iterator it2 = start_iterator_second_row,
                             itend = lcc.darts().end(); std::distance(it2, itend) >= NUMBER_OF_DARTS_PER_CUBE;) {
                    lcc.sew<3>(it2, lcc.beta(start_iterator_first_row, 2, 1, 1, 2));
                    std::advance(start_iterator_first_row, NUMBER_OF_DARTS_PER_CUBE);
                    std::advance(it2, NUMBER_OF_DARTS_PER_CUBE);

                }
            }
        }


        if (z != 0) {

            //collego gli elementi adiacenti tra 2 piani

            //collego gli elementi adiacenti tra 2 righe
            LCC_3::Dart_range::iterator start_iterator_first_plane = lcc.darts().begin();
            std::advance(start_iterator_first_plane,
                         NUMBER_OF_DARTS_PER_CUBE * (z - 1) * j * i ); // punta al 1°cubo di primo piano

            LCC_3::Dart_range::iterator start_iterator_second_plane = lcc.darts().begin();
            std::advance(start_iterator_second_plane,
                         NUMBER_OF_DARTS_PER_CUBE * z * j * i); //punta al 1° cubo di secondo piano

            for (LCC_3::Dart_range::iterator
                         itend = lcc.darts().end(); std::distance(start_iterator_second_plane, itend) >= NUMBER_OF_DARTS_PER_CUBE;) {
                lcc.sew<3>(lcc.beta(start_iterator_second_plane, 1,1, 1, 2), lcc.beta(start_iterator_first_plane, 1, 2));

                std::advance(start_iterator_first_plane, NUMBER_OF_DARTS_PER_CUBE);
                std::advance(start_iterator_second_plane, NUMBER_OF_DARTS_PER_CUBE);
            }
        }
    }
    lcc.display_characteristics(std::cout);
    return lcc;
}
