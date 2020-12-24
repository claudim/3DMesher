#include "Grid_maker.h"
#include "Block_maker.h"

Grid_maker::Grid_maker(){
    grid_box = CGAL::Bbox_3();
}

LCC_3 Grid_maker::make(const Polyhedron& polyhedron){
    wrap_the_object(polyhedron);
    return turn_box_into_grid();
}

void Grid_maker::wrap_the_object(const Polyhedron &polyhedron) {
    const CGAL::Bbox_3 &polyhedron_bbox3 = CGAL::Polygon_mesh_processing::bbox(polyhedron);

    double delta_x = polyhedron_bbox3.xmax() - polyhedron_bbox3.xmin();
    double delta_y = polyhedron_bbox3.ymax() - polyhedron_bbox3.ymin();
    double delta_z = polyhedron_bbox3.zmax() - polyhedron_bbox3.zmin();

    std::cout<<"x_max " << polyhedron_bbox3.xmax() <<std::endl;
    std::cout<<"x_min " << polyhedron_bbox3.xmin() <<std::endl;
    std::cout<<"delta_x " << delta_x  <<std::endl;

    std::cout<<"y_max " << polyhedron_bbox3.ymax() <<std::endl;
    std::cout<<"y_min " << polyhedron_bbox3.ymin() <<std::endl;
    std::cout<<"delta_y " << delta_y  <<std::endl;

    std::cout<<"z_max " << polyhedron_bbox3.zmax() <<std::endl;
    std::cout<<"z_min " << polyhedron_bbox3.zmin() <<std::endl;
    std::cout<<"delta_z " << delta_z  <<std::endl;

    grid_dimension = std::min(std::min(delta_y, delta_z), delta_x) / resolution;

    std::cout<<"grid_dimension " << grid_dimension  <<std::endl;

    grid_box = CGAL::Bbox_3(polyhedron_bbox3.xmin() - grid_dimension,
                            polyhedron_bbox3.ymin() - grid_dimension,
                            polyhedron_bbox3.zmin() - grid_dimension,
                            polyhedron_bbox3.xmax() + grid_dimension,
                            polyhedron_bbox3.ymax() + grid_dimension,
                            polyhedron_bbox3.zmax() + grid_dimension);

    double delta_x_grid = grid_box.xmax() - grid_box.xmin();
    double delta_y_grid = grid_box.ymax() - grid_box.ymin();
    double delta_z_grid = grid_box.zmax() - grid_box.zmin();

    x_dimension = delta_x_grid;
    y_dimension = delta_y_grid;
    z_dimension = delta_z_grid;

    std::cout<<"x_max dopo grid dimension " << grid_box.xmax() <<std::endl;
    std::cout<<"x_min dopo grid dimension" << grid_box.xmin() <<std::endl;
    std::cout<<"delta_x dopo grid dimension" << delta_x_grid  <<std::endl;

    std::cout<<"y_max dopo grid dimension " << grid_box.ymax() <<std::endl;
    std::cout<<"y_min dopo grid dimension" << grid_box.ymin() <<std::endl;
    std::cout<<"delta_y dopo grid dimension" << delta_y_grid  <<std::endl;

    std::cout<<"z_max dopo grid dimension " << grid_box.zmax() <<std::endl;
    std::cout<<"z_min dopo grid dimension" << grid_box.zmin() <<std::endl;
    std::cout<<"delta_z dopo grid dimension" << delta_z_grid  <<std::endl;
}

Point Grid_maker::get_grid_centroid(){

    return Point(grid_box.xmin() + x_dimension / 2,
                 grid_box.ymin() + y_dimension / 2,
                 grid_box.zmin() + z_dimension / 2);
}

LCC_3 Grid_maker::turn_box_into_grid(){
    const double number_of_x_nodes = round(x_dimension / grid_dimension);
    const double number_of_y_nodes = round(y_dimension / grid_dimension);
    const double number_of_z_nodes = round(z_dimension / grid_dimension);

    std::cout<<"numero nodi x" << number_of_x_nodes  <<std::endl;
    std::cout<<"numero nodi y" << number_of_y_nodes  <<std::endl;
    std::cout<<"numero nodi z" << number_of_z_nodes  <<std::endl;

    const double number_of_nodes = number_of_x_nodes * number_of_y_nodes * number_of_z_nodes;
    LCC_3 lcc;

    Block_maker blockMaker = Block_maker();
    int  i=0, j=0;
    //todo cercare di usare il one_dart_per_cell
    for (int z = 0; z < number_of_z_nodes; z++) {

        int add_z = z * j * i * NUMBER_OF_DARTS_PER_CUBE;

        for ( j = 0; j < number_of_y_nodes; j++) {
            for (i = 0; i < number_of_x_nodes; i++) {
                double x_min_p =
                        (grid_box.xmin() + (grid_dimension) / 2.0 + grid_dimension * i ) - (grid_dimension) / 2.0;
                double y_min_p =
                        (grid_box.ymin() + (grid_dimension) / 2.0 + grid_dimension * j ) - (grid_dimension) / 2.0;
                double z_min_p =
                        (grid_box.zmin() + (grid_dimension) / 2.0 + grid_dimension * z ) - (grid_dimension) / 2.0;

                Point basePoint = Point(x_min_p, y_min_p, z_min_p);
                Dart_handle dart_handle_of_cube = blockMaker.make_cube(lcc, basePoint, grid_dimension);
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

    std::cout << "griglia realizzata" << std::endl;
    lcc.display_characteristics(std::cout);
    return lcc;
}

void Grid_maker::setGridDimension(double gridDimension) {
    grid_dimension = gridDimension;
}


