#ifndef INC_3DMESHER_STLREADER_H
#define INC_3DMESHER_STLREADER_H

//#include <iostream>
#include <fstream>
#include <CGAL/Polyhedral_mesh_domain_with_features_3.h>
#include <CGAL/IO/Polyhedron_builder_from_STL.h>
#include <CGAL/boost/graph/named_params_helper.h>
#include <CGAL/boost/graph/Named_function_parameters.h>

//#include <CGAL/IO/STL_writer.h>
//#include <CGAL/Polygon_mesh_processing/polygon_soup_to_polygon_mesh.h>

//typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
//typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;

template < class PolyhedronTraits_3 = CGAL::Exact_predicates_inexact_constructions_kernel,
        class PolyhedronItems_3 = CGAL::Polyhedron_items_3,
        template < class T, class I, class A>
        class T_HDS = CGAL::HalfedgeDS_default,
        class Alloc = CGAL_ALLOCATOR(int)>
class STLReader {

    typedef CGAL::Polyhedron_3< PolyhedronTraits_3, PolyhedronItems_3, T_HDS, Alloc>        Self;
    typedef PolyhedronTraits_3                                                              Traits;
    typedef PolyhedronItems_3                                                               Items;
    typedef CGAL::I_Polyhedron_derived_items_3<Items>                                       Derived_items;
    typedef T_HDS< Traits, Derived_items, Alloc>                                            HDS;
   // typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
    typedef typename CGAL::Mesh_polyhedron_3<Traits>::type                                  Polyhedron;


public:
    //// it could throw std::ios_base::failure exception
    template<class Polyhedron = Polyhedron>
    Polyhedron read(const std::string fileName){
        {
            std::ifstream input(fileName, std::ios::in | std::ios::binary); // construction of input (a ifstream object) and stream opening filename file for input operations or in binary mode
            if(!input) {
                std::cerr << "Error! Cannot open file " << fileName << std::endl;
            }
            Polyhedron polyhedron;
            if(fileName.size() == 0)
            {
                std::cerr << "The file you are trying to load is empty." << std::endl;;
            }
            input.exceptions( std::ifstream::failbit | std::ifstream::badbit ); //if a bit in the mask becomes set in the error flags, then an exception of type std::ios_base::failure is thrown.
            std::vector<std::array<double, 3> > vertices;
            std::vector<std::array<int, 3> > triangles;
            if (!CGAL::read_STL(input, vertices, triangles)) //if the reading process did not go well
            {
                std::cerr << "Error: invalid STL file" << std::endl;
            }

           // CGAL::Polyhedron_builder_from_STL polyhedronBuilderFromStl;
           // CGAL::Polyhedron_builder_from_STL<HDS>(input);

            //Self s;
            //s.delegate(polyhedronBuilderFromStl);
           // polyhedron.delegate(polyhedronBuilderFromStl);



           // read_stl(input, polyhedron, CGAL::parameters::all_default());


            //CGAL::Polyhedron_builder_from_STL<typename Self::HalfedgeDS> polyhedronBuilderFromStl;
            //polyhedron.delegate(polyhedronBuilderFromStl);

            // quello che ho letto (quindi punti e trinagoli ) devo formare un polyhedron.
            //input >> polyhedron;
            return polyhedron;
        }
    }


    template<class Polyhedron = Polyhedron, class NamedParameters>
    bool read_stl(std::istream& in, Polyhedron & P, NamedParameters np) {

        // reads a polyhedron from `in' and appends it to P.
        typedef typename CGAL::Polygon_mesh_processing::GetVertexPointMap<Self, NamedParameters>::type Vpm;
        using CGAL::parameters::choose_parameter;
        using CGAL::parameters::get_parameter;

        Vpm vpm = choose_parameter(get_parameter(np, CGAL::internal_np::vertex_point),
                                   get_property_map(CGAL::vertex_point, P));
        //CGAL::scan_OFF( in, P);

        std::vector<std::array<double, 3> > vertices;
        std::vector<std::array<int, 3> > triangles;
        if (!CGAL::read_STL(in, vertices, triangles)) //if the reading process did not go well
        {
            std::cerr << "Error: invalid STL file" << std::endl;
        }

        if(!CGAL::parameters::is_default_parameter(get_parameter(np, CGAL::internal_np::vertex_point)))
        {
            typedef typename boost::graph_traits<Self>::vertex_descriptor Vertex;
            typename CGAL::property_map_selector<Self, boost::vertex_point_t>::type
            def_vpm = get_property_map(CGAL::vertex_point, P);
            for(Vertex v : vertices)
            {
                put(vpm, v, get(def_vpm, v));
            }
        }
        return in.good();
    }


//    template < class Traits,
//            class Items,
//            template < class T, class I, class A>
//            class HDS, class Alloc>
//    std::istream& operator>>(std::istream& in, Polyhedron & p);

    //typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
    //typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;
//template<template < class K = CGAL::Exact_predicates_inexact_constructions_kernel> class Polyhedron = CGAL::Mesh_polyhedron_3<K>::type >
////friend std::istream& operator>>(std::istream &in, Polyhedron &polyhedron);
//    template<class Traits, class Items,template < class T, class I, class A> class HDS, class AllocClassTemplate>
//    friend std::istream& operator>>(std::istream &in, CGAL::Polyhedron_3<Traits,Items,HDS,AllocClassTemplate> &p);



    template<class Polyhedron>
    friend std::istream& operator>>(std::istream &in, Polyhedron &p);

};

//template<class Traits, class Items,template < class T, class I, class A> class HDS, class AllocClassTemplate>
//std::istream& operator>>(std::istream &in, CGAL::Polyhedron_3<Traits,Items,HDS,AllocClassTemplate> &p){
//        p = CGAL::Polyhedron_builder_from_STL(in);
//        return in;
//}

template<class Polyhedron>
std::istream& operator>>(std::istream &in, Polyhedron &polyhedron){
    //polyhedron = CGAL::Polyhedron_builder_from_STL(in);
    //CGAL::Polyhedron_builder_from_STL(in);
    return in;
}




#endif //INC_3DMESHER_STLREADER_H
