// Copyright (c) 2020-2021 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// Find degenerate hexahedra in the mesh.
//******************************************************************************

#ifndef INC_3DMESHER_DEGENERATE_ELEMENT_FINDER_H
#define INC_3DMESHER_DEGENERATE_ELEMENT_FINDER_H

#include "MyLCC.h"

/**
 * @brief Find degenerate hexahedra in the mesh.
 *
 * @file Degenerate_element_finder.h
 * @class Degenerate_element_finder
 */
class Degenerate_element_finder {
private:

    int _precision = 6;

private:
    std::vector<Dart_handle> _pyramids;
    std::vector<Dart_handle> _tetrahedra;
    std::vector<Dart_handle> _wedges;
    std::vector<Dart_handle> _quadrilaterals;
    std::vector<Dart_handle> _block_with_folded_facets;
    std::vector<Dart_handle> _degenerate_elements;

private:
    std::vector<Dart_handle> _block_with_3_collinear_vertices;

public:
    /**
     * @brief Set the precision of digits numbers.
     *
     * @param precision The precision of decimal numbers.
     */
    void setPrecision(int precision) {
        _precision = precision;
    }

    /**
     * \brief Check if a mesh block is a pyramid and if it is a pyramid add it to _pyramids vector.
     *
     * @param replicated_vertices Map of replicated vertices with how many time they are replicated.
     * @param blockToCheck Block to chek.
     * @return true if it is a pyramid.
     */
    bool is_a_pyramid(std::map<Point, int>& replicated_vertices,Dart_handle& blockToCheck){
        bool is_a_pyramid = false;
        if(replicated_vertices.size() == 1)
        {
            if(replicated_vertices.begin()->second == 4)
            {
                _pyramids.emplace_back(blockToCheck);
                is_a_pyramid = true;
            }
        }
        return is_a_pyramid;
    }

    /**
     * \brief Check if a mesh block is a tetrahedron and if it is a tetrahedron add it to tetrehedra vector.
     *
     * @param replicated_vertices Map of replicated vertices with how many time they are replicated.
     * @param blockToCheck Block to chek.
     * @return true if it is a tetrahedron.
     */
    bool is_a_tetrahedron(std::map<Point, int>& replicated_vertices,Dart_handle& blockToCheck){
        bool is_a_tetrahedron = false;
        if(replicated_vertices.size() == 2)
        {
            if(replicated_vertices.begin()->second == 3 && replicated_vertices.rbegin()->second == 3  )
            {
                _tetrahedra.emplace_back(blockToCheck);
                is_a_tetrahedron = true;
            }
        }
        return is_a_tetrahedron;
    }

    /**
     * \brief Check if a mesh block is a wedge and if it is a wedge add it to _wedges vector.
     *
     * @param replicated_vertices Map of replicated vertices with how many time they are replicated.
     * @param blockToCheck Block to chek.
     * @return true if it is a wedge.
     */
    bool is_a_wedge(std::map<Point, int>& replicated_vertices,Dart_handle& blockToCheck){
        bool is_a_wedge = false;
        if(replicated_vertices.size() == 2)
        {
            if(replicated_vertices.begin()->second == 2 && replicated_vertices.rbegin()->second == 2 )
            {
                _wedges.emplace_back(blockToCheck);
                is_a_wedge = true;
            }
        }
        return is_a_wedge;
    }

    /**
     * \brief Check if a mesh block is a quadrilateral and if it is a quadrilateral add it to _quadrilaterals vector.
     *
     * @param replicated_vertices Map of replicated vertices with how many time they are replicated.
     * @param blockToCheck Block to chek.
     * @return true if it is a quadrilateral.
     */
    bool is_a_quadrilateral(std::map<Point, int>& replicated_vertices,Dart_handle& blockToCheck){
        bool is_a_quadrilateral = true;
        if(replicated_vertices.size() == 4)
        {

            for(std::map<Point, int>::iterator it = replicated_vertices.begin(), it_end = replicated_vertices.end(); it !=it_end; it++ )
            {
                if(it->second != 2)
                {
                    is_a_quadrilateral = false;
                    break;
                }
            }
            if(is_a_quadrilateral)
            {
                _quadrilaterals.emplace_back(blockToCheck);
            }
        }
        return is_a_quadrilateral;
    }

public:
     /**
      * \brief Check if a block/hexahedron has 8 different vertices.
      *
      * @param lcc The mesh.
      * @param blockToCheck  The mesh element/block to check.
      * @return true if a block has 8 different vertices, false otherwise.
      */
    bool has_8_different_vertices(LCC_3& lcc, Dart_handle& blockToCheck){
        bool has_8_different_vertices = true;
        std::vector<Point> vertices;
        std::map<Point, int> replicated_vertices;

         if(!lcc.is_empty()) {
             for (LCC_3::One_dart_per_incident_cell_range<0, 3, 3>::iterator vertex_it = lcc.one_dart_per_incident_cell<0, 3>(
                     blockToCheck).begin(), vertex_it_end = lcc.one_dart_per_incident_cell<0, 3>(blockToCheck).end();
                  vertex_it != vertex_it_end; ++vertex_it) {
                 FT x_coord = int((lcc.point(vertex_it).x() * pow(10,_precision)))/pow(10,_precision);
                 FT y_coord = int((lcc.point(vertex_it).y() * pow(10,_precision)))/pow(10,_precision);
                 FT z_coord = int((lcc.point(vertex_it).z() * pow(10,_precision)))/pow(10,_precision);
                 Point point  = Point (x_coord, y_coord, z_coord);
                 if (std::find(vertices.begin(), vertices.end(), point) == vertices.end()) {
                     vertices.emplace_back(lcc.point(vertex_it));
                 }
                 else{
                     if( replicated_vertices[point] == 0)
                     {replicated_vertices[point] = 2;}
                     else
                     {replicated_vertices[point] = 1 + replicated_vertices[point];}
                 }
             }
             if (vertices.size() != 8) {
                 has_8_different_vertices = false;
                 if(vertices.size() == 4) {
                     bool isAQuadrilateral = this->is_a_quadrilateral(replicated_vertices, blockToCheck);
                     if(!isAQuadrilateral)
                     {
                         this->is_a_tetrahedron(replicated_vertices, blockToCheck);
                     }
                 }
                 if(vertices.size() == 5) {
                     this->is_a_pyramid(replicated_vertices, blockToCheck);
                 }
                 if(vertices.size() == 6) {
                     this->is_a_wedge(replicated_vertices, blockToCheck);
                 }
             }
         }
        return has_8_different_vertices;
    }


    /**
     * \brief Check if all faces of a block are made up of coplanar vertices that is check if a hexahedron has at least a folded facet.
     *
     * @param lcc The mesh.
     * @param blockToCheck The mesh element/block/3-cell to check.
     * @return True if all faces of a block are made up of coplanar vertices, false otherwise.
     */
    bool has_hex_a_folded_facet(LCC_3 &lcc, Dart_handle &blockToCheck) {
        bool has_coplanar_vertices = true;
        if(!lcc.is_empty()) {
            for (LCC_3::One_dart_per_incident_cell_range<2, 3, 3>::iterator facet_it = lcc.one_dart_per_incident_cell<2, 3, 3>(
                    blockToCheck).begin(),
                         facet_end_it = lcc.one_dart_per_incident_cell<2, 3, 3>(blockToCheck).end();
                 facet_it != facet_end_it; ++facet_it) {
                std::vector<Point> facet_points;
                for (LCC_3::Dart_of_orbit_range<1>::iterator vertexIt = lcc.darts_of_orbit<1>(facet_it).begin(),
                             vertexItEnd = lcc.darts_of_orbit<1>(facet_it).end(); vertexIt != vertexItEnd; ++vertexIt) {
                    facet_points.emplace_back(lcc.point(vertexIt));
                }
                if (!CGAL::coplanar(facet_points[0], facet_points[1], facet_points[2], facet_points[3])) {
                    has_coplanar_vertices = false;
                    this->_block_with_folded_facets.emplace_back(blockToCheck);
                    break;
                }
            }
        }
        return has_coplanar_vertices;
    }

    /**
     * \brief Check if there are more than 2 collinear vertices among the block vertices.
     *
     * @param lcc The mesh.
     * @param blockToCheck The mesh element/block/3-cell to check.
     * @return True if there are 3 of the 8 block vertices that are collinear, false otherwise.
     */
    bool has_3_collinear_vertices(LCC_3 &lcc, Dart_handle &blockToCheck)
    {
        bool has_3_collinear_vertices = false;
        std::vector<Dart_handle> hexahedron_vertices;
        if(!lcc.is_empty()) {
            for(LCC_3::One_dart_per_incident_cell_range<0, 3, 3>::iterator vertex_it = lcc.one_dart_per_incident_cell<0, 3>(
                    blockToCheck).begin(), vertex_it_end = lcc.one_dart_per_incident_cell<0, 3>(blockToCheck).end(); vertex_it != vertex_it_end; ++vertex_it)
            {
                hexahedron_vertices.emplace_back(vertex_it);
            }
            int i = 0, j = i, k = j;
            Dart_handle vertex_it;
            Dart_handle vertex_it2;
            Dart_handle vertex_it3;
//            LCC_3::One_dart_per_incident_cell_range<0, 3, 3>::iterator vertex_it = lcc.one_dart_per_incident_cell<0, 3>(
//                    blockToCheck).begin(), vertex_it3_end = lcc.one_dart_per_incident_cell<0, 3>(blockToCheck).end();
//            LCC_3::One_dart_per_incident_cell_range<0, 3, 3>::iterator vertex_it2 = vertex_it,  vertex_it3 = vertex_it;
//            LCC_3::One_dart_per_incident_cell_range<0, 3, 3>::iterator vertex_it_end = vertex_it3_end, vertex_it2_end = vertex_it3_end;
            while(i < 6 && !has_3_collinear_vertices)
            {
                j = i; j++;
                vertex_it = hexahedron_vertices.at(i);
                vertex_it2 = hexahedron_vertices.at(j);
                while(j < 7 && !has_3_collinear_vertices)
                {
                    k = j; k++;
                    vertex_it3 = hexahedron_vertices.at(k);
                    while(k < 8 && !has_3_collinear_vertices)
                    {
                        if(CGAL::collinear(lcc.point(vertex_it),lcc.point(vertex_it2), lcc.point(vertex_it3) ))
                        {
                            has_3_collinear_vertices = true;
                            this->_block_with_3_collinear_vertices.emplace_back(blockToCheck);
                        }
                        k++;
                    }
                    j++;
                }
                i++;
            }
        }
//        if(!lcc.is_empty()) {
//            LCC_3::One_dart_per_incident_cell_range<0, 3, 3>::iterator vertex_it = lcc.one_dart_per_incident_cell<0, 3>(
//                    blockToCheck).begin(), vertex_it3_end = lcc.one_dart_per_incident_cell<0, 3>(blockToCheck).end();
//            LCC_3::One_dart_per_incident_cell_range<0, 3, 3>::iterator vertex_it2 = vertex_it,  vertex_it3 = vertex_it;
//            LCC_3::One_dart_per_incident_cell_range<0, 3, 3>::iterator vertex_it_end = vertex_it3_end, vertex_it2_end = vertex_it3_end;
//            while(vertex_it != vertex_it_end && !has_3_collinear_vertices)
//            {
//                vertex_it2 = vertex_it; vertex_it2++;
//                while(vertex_it2 != vertex_it2_end && !has_3_collinear_vertices)
//                {
//                    vertex_it3 = vertex_it2; vertex_it3++;
//                    while(vertex_it3 != vertex_it3_end && !has_3_collinear_vertices)
//                    {
//                        if(CGAL::collinear(lcc.point(vertex_it),lcc.point(vertex_it2), lcc.point(vertex_it3) ))
//                        {
//                            has_3_collinear_vertices = true;
//                        }
//                        vertex_it3++;
//                    }
//                    vertex_it2++;
//                }
//                vertex_it++;
//            }
//        }
        return has_3_collinear_vertices;
    }

    std::vector<Dart_handle>& getPyramids() {
        return _pyramids;
    }

    std::vector<Dart_handle>& getTetrahedra() {
        return _tetrahedra;
    }

    std::vector<Dart_handle>& getWedges() {
        return _wedges;
    }

    std::vector<Dart_handle>& getQuadrilaterals(){
        return _quadrilaterals;
    }

    std::vector<Dart_handle> &getBlockWithNotCoplanarFacetsVertices() {
        return _block_with_folded_facets;
    }

     std::vector<Dart_handle> &getBlockWith3CollinearVertices() {
        return _block_with_3_collinear_vertices;
    }

    /**
     * \brief Find the degenerate elements in the mesh.
     * In this method degenerate elements means: pyramid, tetrhedron, wedge, quadrilateral, elements with facets whose 4 vertices are not coplanar,
     * elements that have 3 collinear vertices. It finds degenerate elements among all mesh blocks.
     *
     * @param lcc The mesh.
     * @return Vector of degenerate elements present in the mesh.
     */
    std::vector<Dart_handle> find_degenerate_elements(LCC_3 &lcc) {
        std::vector<Dart_handle> degenerate_elements;
        if(!lcc.is_empty()) {
            // for every mesh block
            for (LCC_3::One_dart_per_cell_range<3, 3>::iterator cell_it = lcc.one_dart_per_cell<3>().begin(), cell_end_it = lcc.one_dart_per_cell<3>().end();
                 cell_it != cell_end_it; ++cell_it) {
                if(!this->has_8_different_vertices(lcc, cell_it) || !this->has_hex_a_folded_facet(lcc, cell_it) || this->has_3_collinear_vertices(lcc, cell_it)) {

                //if (!this->has_8_different_vertices(lcc, cell_it) || !this->has_hex_a_folded_facet(lcc, cell_it)) {
                //if (!this->has_hex_a_folded_facet(lcc, cell_it)) {
                    degenerate_elements.emplace_back(cell_it);
                }
            }
        }
        return degenerate_elements;
    }

    /**
    * \brief Find the degenerate elements in the mesh.
    * In this method degenerate elements means: pyramid, tetrhedron, wedge, quadrilateral, elements with facets whose 4 vertices are not coplanar,
    * elements that have 3 collinear vertices. For how the UNIVAQ algorithm is built, it finds degenerate elements only for the more external mesh block.
    *
    * @param lcc The mesh.
    * @return Vector of degenerate elements present in the mesh.
    */
    std::vector<Dart_handle> find_degenerate_elements_among_the_more_external_mesh_block(LCC_3 &lcc) {
        std::vector<Dart_handle> degenerate_elements;
        if(!lcc.is_empty()) {
            //TODO: replase "for every mesh block" with "for every more external blocks"
            // for every mesh block
            for (LCC_3::One_dart_per_cell_range<3, 3>::iterator cell_it = lcc.one_dart_per_cell<3>().begin(), cell_end_it = lcc.one_dart_per_cell<3>().end();
                 cell_it != cell_end_it; ++cell_it) {
                if (!this->has_8_different_vertices(lcc, cell_it) || !this->has_hex_a_folded_facet(lcc, cell_it) ||
                    this->has_3_collinear_vertices(lcc, cell_it)) {
                    degenerate_elements.emplace_back(cell_it);
                }
            }
        }
        return degenerate_elements;
    }
};

#endif //INC_3DMESHER_DEGENERATE_ELEMENT_FINDER_H
