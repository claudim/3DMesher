//
// Created by Claudia Di Marco on 01/11/2020.
//

#include "Writer.h"

void Writer::output_to_medit(std::ostream& os, const LCC_3& lcc){
    typedef typename LCC_3::Vertex_attribute_const_handle Vertex_handle;

    //-------------------------------------------------------
    // File output
    //-------------------------------------------------------

    //-------------------------------------------------------
    // Header
    //-------------------------------------------------------
    os << std::setprecision(17);

    os << "MeshVersionFormatted 1\n"
       << "Dimension 3\n";

    //-------------------------------------------------------
    // Vertices
    //-------------------------------------------------------
    os << "Vertices\n" << lcc.number_of_vertex_attributes() << '\n';

    boost::unordered_map<Vertex_handle, int> V;
    int inum = 1;
    for( Vertex_handle vit = lcc.vertex_attributes().begin();
         vit != lcc.vertex_attributes().end();
         ++vit)
    {
        V[vit] = inum++;
        Point p = lcc.point_of_vertex_attribute(vit);
        os << CGAL::to_double(p.x()) << ' '
           << CGAL::to_double(p.y()) << ' '
           << CGAL::to_double(p.z()) << ' '
           << get() << '\n';
    }

    //-------------------------------------------------------
    // Facets
    //-------------------------------------------------------
    typename LCC_3::size_type number_of_quadrilaterals = number_of_facets_in_lcc(lcc);

    os << "Quadrilaterals\n"
       << number_of_quadrilaterals << '\n';

    //ciclo su tutti le 2-celle di dim 3 // su tutti gli esaedri
    for (LCC_3::One_dart_per_cell_const_range<2,3>::const_iterator lcc_facets_iterator = lcc.one_dart_per_cell<2,3>().begin(),
                 lcc_facets_end_iterator = lcc.one_dart_per_cell<2,3>().end();
         lcc_facets_iterator != lcc_facets_end_iterator; ++lcc_facets_iterator) {

        // per tutti i vertici della faccia
        for (LCC_3::One_dart_per_incident_cell_const_range<0,2>::const_iterator
                     it = lcc.one_dart_per_incident_cell<0, 2>(lcc_facets_iterator).begin(),
                     itend = lcc.one_dart_per_incident_cell<0, 2>(lcc_facets_iterator).end(); it != itend; ++it) {
            os << V[lcc.vertex_attribute(it)] << ' ';

        }
        //os << get(facet_pmap, *fit) << '\n';
        os << get() << '\n';
        //os << '\n';
    }


    //-------------------------------------------------------
    // Hexahedra
    //-------------------------------------------------------
    os << "Hexahedra\n"
       << number_of_cells_in_lcc(lcc) << '\n';

    //ciclo su tutti le 3-celle di dim 3 // su tutti gli esaedri
    for (LCC_3::One_dart_per_cell_const_range<3,3>::const_iterator lcc_cells_iterator = lcc.one_dart_per_cell<3,3>().begin(),
                 lcc_cells_end_iterator = lcc.one_dart_per_cell<3,3>().end();
         lcc_cells_iterator != lcc_cells_end_iterator; ++lcc_cells_iterator) {

        // per tutti i vertici del cubo
        for (LCC_3::One_dart_per_incident_cell_const_range<0,3>::const_iterator
                     it = lcc.one_dart_per_incident_cell<0, 3>(lcc_cells_iterator).begin(),
                     itend = lcc.one_dart_per_incident_cell<0, 3>(lcc_cells_iterator).end(); it != itend; ++it) {

            os << V[lcc.vertex_attribute(it)] << ' ';
        }
        //os << get(cell_pmap, lcc_cells_iterator) << '\n';
        os << get() << '\n';
        //os << '\n';
    }

    //-------------------------------------------------------
    // End
    //-------------------------------------------------------
    os << "End\n";
}


int Writer::get()
{
    return 0;
}

LCC_3::size_type Writer::number_of_facets_in_lcc(const LCC_3 &lcc)
{
    unsigned int dimension = LCC_3::Base::dimension;
    std::vector<unsigned int> cells(dimension+2);
    for ( unsigned int i=0; i<=dimension+1; ++i)
    { cells[i]=i; }

    std::vector<unsigned int> res = lcc.count_cells(cells);
    return res[2];
}

LCC_3::size_type Writer::number_of_cells_in_lcc(const LCC_3 &lcc)
{
    unsigned int dimension = LCC_3::Base::dimension;
    std::vector<unsigned int> cells(dimension+2);
    for ( unsigned int i=0; i<=dimension+1; ++i)
    { cells[i]=i; }

    std::vector<unsigned int> res = lcc.count_cells(cells);
    return res[3];
}