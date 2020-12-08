#include <InitialMesh_boundary_connector.h>
#include "../Include/catch.hpp"
#include "test_config.h"
#include "OFF_Reader.h"
#include "Grid_maker.h"
#include "Initial_mesh_maker.h"
#include "External_and_onBoundary_remover.h"
#include "Writer.h"
#include "External_facet_finder.h"

TEST_CASE("Must_find_L_facets","[L_facets_detect_tests]")
{
    std::string name = "trapezoidTest";
    std::string fileName = data_path + "/trapezoidTest.off";
    OFF_Reader reader;
    Polyhedron polyhedron = reader.read(fileName);

    Grid_maker gridMaker;
    LCC_3 hex_mesh = gridMaker.make(polyhedron);

    Initial_mesh_maker<External_and_onBoundary_remover> initMeshMaker;
    initMeshMaker.removeBlocks(hex_mesh, polyhedron, gridMaker.getGridDimension()/2);


    const std::string out_data_path = "/Users/claudia/CLionProjects/3DMesher/MeshOutput";
    std::string outputFileName = out_data_path + "/" + name + "_L_facet_detector_initMesh.mesh";
    std::ofstream medit_file(outputFileName);
    Writer writer;
    writer.output_to_medit(medit_file,hex_mesh);
    medit_file.close();

//    External_facet_finder facet_finder;
//    std::vector<Dart_handle> external_facets = facet_finder.findFacets(hex_mesh);
//
//    int l_facets = 0;
//    for(Dart_handle facet: external_facets)
//    {
//        Vector facet_normal = CGAL::compute_normal_of_cell_2(hex_mesh, facet);
//        for(LCC::One_dart_per_incident_cell_range<2,2,3>::iterator f_it =hex_mesh.one_dart_per_incident_cell<2,2,3>(facet).begin(),
//                f_end_it = hex_mesh.one_dart_per_incident_cell<2,2,3>(facet).end(); f_it!= f_end_it; ++f_it){
//            Vector near_facet_normal = CGAL::compute_normal_of_cell_2(hex_mesh, f_it);
//
//
//        }
//    }

    InitialMesh_boundary_connector boundaryConnector = InitialMesh_boundary_connector();
    boundaryConnector.connect(hex_mesh, polyhedron);

    std::string outputFileName1 = out_data_path + "/" + name + "_L_facet_detector_Mesh.mesh";
    std::ofstream medit_file1(outputFileName1);
    //Writer writer;
    writer.output_to_medit(medit_file1,hex_mesh);
    medit_file.close();






}