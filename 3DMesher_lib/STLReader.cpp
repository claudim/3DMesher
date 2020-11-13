#include "STLReader.h"


//// it could throw std::ios_base::failure exception
//template < class PolyhedronTraits_3,
//        class PolyhedronItems_3,
//        template < class T, class I, class A>
//        class T_HDS,
//        class Alloc>
////Polyhedron STLReader<PolyhedronTraits_3, PolyhedronItems_3, T_HDS<T,I,A>, Alloc >::read(std::string fileName) {
//Polyhedron STLReader::read(std::string fileName) {
//
//    std::ifstream input(fileName, std::ios::in | std::ios::binary); // construction of input (a ifstream object) and stream opening filename file for input operations or in binary mode
//    if(!input) {
//        std::cerr << "Error! Cannot open file " << fileName << std::endl;
//    }
//    Polyhedron polyhedron;
//    if(fileName.size() == 0)
//    {
//        std::cerr << "The file you are trying to load is empty." << std::endl;;
//    }
//    input.exceptions ( std::ifstream::failbit | std::ifstream::badbit ); //if a bit in the mask becomes set in the error flags, then an exception of type std::ios_base::failure is thrown.
//    std::vector<std::array<double, 3> > points;
//    std::vector<std::array<int, 3> > triangles;
//    if (!CGAL::read_STL(input, points, triangles)) //if the reading process did not go well
//    {
//        std::cerr << "Error: invalid STL file" << std::endl;
//    }
//
//    //CGAL::Polyhedron_builder_from_STL<Polyhedron::HalfedgeDS>(input);
//
//    // quello che ho letto (quindi punti e trinagoli ) devo formare un polyhedron.
//    input >> polyhedron;
//    return polyhedron;
//}




//template < class Traits,
//        class Items,
//        template < class T, class I, class A>
//        class HDS, class Alloc>
//std::istream& operator>>(std::istream& in,
//                         Polyhedron_3<Traits,Items,HDS,Alloc>& P)




//template < class Traits,
//        class Items,
//        template < class T, class I, class A>
//        class HDS, class Alloc>
//std::istream& operator>>(std::istream& in,
//                         Polyhedron_3<Traits,Items,HDS,Alloc>& P)
//{
//    read_off(in,P);
//    return in;
//}


//template < class Traits,
//        class Items,
//        template < class T, class I, class A>
//        class HDS, class Alloc>
//bool
//read_off(std::istream& in,
//         Polyhedron_3<Traits,Items,HDS,Alloc>& P)
//{
//    return read_off(in, P, parameters::all_default());
//}

//template < class Traits,
//        class Items,
//        template < class T, class I, class A>
//        class HDS, class Alloc,
//        class NamedParameters>
//bool
//read_off(std::istream& in,
//         Polyhedron_3<Traits,Items,HDS,Alloc>& P,
//         NamedParameters np) {
//    // reads a polyhedron from `in' and appends it to P.
//    typedef typename CGAL::Polygon_mesh_processing::GetVertexPointMap<Polyhedron_3<Traits,Items,HDS,Alloc>, NamedParameters>::type Vpm;
//    using parameters::choose_parameter;
//    using parameters::get_parameter;
//
//    Vpm vpm = choose_parameter(get_parameter(np, internal_np::vertex_point),
//                               get_property_map(CGAL::vertex_point, P));
//    CGAL::scan_OFF( in, P);
//    if(!parameters::is_default_parameter(get_parameter(np, internal_np::vertex_point)))
//    {
//        typedef typename boost::graph_traits<Polyhedron_3<Traits,Items,HDS,Alloc> >::vertex_descriptor Vertex;
//        typename property_map_selector<Polyhedron_3<Traits,Items,HDS,Alloc>, boost::vertex_point_t>::type
//        def_vpm = get_property_map(CGAL::vertex_point, P);
//        for(Vertex v : vertices(P))
//        {
//            put(vpm, v, get(def_vpm, v));
//        }
//    }
//    return in.good();
//}