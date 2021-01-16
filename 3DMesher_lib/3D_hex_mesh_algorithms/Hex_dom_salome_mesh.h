// Copyright (c) 2021 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// Implementation of a Salome body fitting algorithm. To get more information on this algorithm,
// you can consult https://docs.salome-platform.org/latest/gui/SMESH/cartesian_algo.html .
// From previous link so from Salome documentation:
// "Body Fitting algorithm generates hexahedrons of a Cartesian grid
// in the internal part of geometry and polyhedrons and other types of elements
// at the intersection of Cartesian cells with the geometrical boundary.
// The meshing algorithm is as follows:
// 1) Lines of a Cartesian structured grid defined by Body Fitting Parameters hypothesis are intersected with the geometry boundary,
// thus nodes lying on the boundary are found. This step also allows finding out for each node of the Cartesian grid if it is inside or outside the geometry.
// 2) For each cell of the grid, check how many of its nodes are outside of the geometry boundary.
//    Depending on a result of this check:
//      -     skip a cell, if all its nodes are outside
//      -     skip a cell, if it is too small according to Size Threshold parameter. If the size of a truncated grid cell is Threshold times less than a initial cell size, then a mesh element is not created.
//      -     add a hexahedron in the mesh, if all nodes are inside
//      -     add a polyhedron or another cell type in the mesh, if some nodes are inside and some outside."
//
// Code documentation for the GEOM module is https://docs.salome-platform.org/latest/tui/GEOM/index.html
// Code documentation for the SMESH module is https://docs.salome-platform.org/latest/tui/SMESH/index.html
// Code documentation for the MEDCoupling is https://docs.salome-platform.org/latest/dev/MEDCoupling/developer/medcouplingcppexamples.html
//
//******************************************************************************


#ifndef INC_3DMESHER_HEX_DOM_SALOME_MESH_H
#define INC_3DMESHER_HEX_DOM_SALOME_MESH_H


/*
For example: you have an AFileName.idl
1. Add the AFileName.idl to you project: Right Click on The project->Add->Existing Item...
2. Click Right on The AFileName.idl from the project->Compile
3. The step 2 will generate AFileName_h.h, AFileName_i.c, AFileName_p.c,...
4. Now you can #include "AFileName_h.h" and use it, you also may need
        to add AFileName_i.c or other generated files to your project
depending on your needs.*/
//todo: per includere STLPlugin.idl, GEOM_Gen.idl
#include "GEOMAlgo_SolidSolid.hxx" //src/GEOMAlgo/GEOMAlgo_SolidSolid.hxx
#include <SMESH_Gen.hxx> //src/SMESH/SMESH_Gen.cxx
#include <SMESH_Mesh.hxx>
#include "StdMeshers_Cartesian_3D.hxx"
#include "StdMeshers_CartesianParameters3D.hxx"
#include "MEDCouplingUMesh" //src/MEDCoupling/MEDCouplingUMesh.hxx


class Hex_dom_salome_mesh {
public:
    /**
     * @brief Execute Salome body fitting algorithm.
     *
     * @file Hex_dom_salome_mesh.h
     * @class Hex_dom_salome_mesh
     *
     * Execute Salome body fitting algorithm.
     */
    void run(){
        //1. create solid importing from STL file
        GEOM::GEOM_Gen* geomGen = new GEOM:GEOM_Gen(); //geomGen sarebbe geompy // engine to create objects
        //get the basic operation necessary to create origin and axis
        GEOM::GEOM_GEN::GetIBasicOperations* basicOperations =  geomGen->GetIBasicOperation();
            //GEOM_VertexSource::GEOM_VertexSource* origin = new  GEOM_VertexSource::GEOM_VertexSource();
        GEOM::GEOM_Object* origin = basicOperations->MakePointXYZ(0,0,0);
        GEOM::GEOM_Object* x_axis = basicOperations->MakeVectorDXDYDZ(1,0,0);
        GEOM::GEOM_Object* y_axis = basicOperations->MakeVectorDXDYDZ(0,1,0);
        GEOM::GEOM_Object* z_axis = basicOperations->MakeVectorDXDYDZ(0,0,1);

        //create object from a stl file
        const std::string data_path = "/Users/claudia/CLionProjects/3DMesher/DataInput";
        //std::string name = "sfera";
        std::string name = "cube100x100axisAligned";
        std::string fileName = data_path + "/" + name + ".stl";

        GEOM::GEOM_GEN::IBasicOperations* stl_manager =  geomGen->GetPluginOperations('STLPlugin'); //dovrei inserire il nome della libreria
       // GEOM::ISTLOperation* stl_manager = new GEOM::ISTLOperation();
        GEOM::ListOfGO geometry_from_STL =  stl_manager->ImportSTL(fileName); //GEOM::ListOfGO is a sequence<GEOM_Object>

        //make the union of the facets
//        GEOM::GEOM_IBlocksOperations* block_operations =  geomGen->GetIBlocksOperations();
//        GEOM::GEOM_Object* union_faces = block_operations->UnionFaces(geometry_from_STL);
        //oppure
        GEOM::GEOM_IGroupOperations* group_operations =  geomGen->GetIGroupOperations();
        GEOM::GEOM_Object* union_faces = group_operations->UnionListOfGroups(geometry_from_STL);


        //generate a solid from the union_faces Create a solid (or solids) from the set of faces and/or shells.
//        GEOM::GEOM_IShapesOperations* shapes_operations =  geomGen->GetIShapesOperations();
//        GEOM::GEOM_Object* solid = shapes_operations->MakeSolidFromConnectedFaces([geometry_from_STL],false);
        //oppure
        GEOM::GEOM_IShapesOperations* shapes_operations =  geomGen->GetIShapesOperations();
        GEOM::GEOM_Object* solid = shapes_operations->MakeSolidFromConnectedFaces([union_faces],false);


//        Cube_solid_1 = geompy.MakeSolidFromConnectedFaces([cube100x100axisAligned_stl_1],False)
//        Oppure
//        Bunny_UnionFaces_1 = geompy.UnionFaces(bunny_stl_1)
//        Solid_1 = geompy.MakeSolidFromConnectedFaces([Bunny_UnionFaces_1],False)

       // TopoDS_shape* solid;

        geomGen->addInStudy( origin , 'origin');
        geomGen->addInStudy( x_axis, 'x_axis');
        geomGen->addInStudy( y_axis, 'y_axis');
        geomGen->addInStudy( z_axis, 'z_axis');
        geomGen->addInStudy( , 'stl_object');
        geomGen->addInStudy( , 'union_facets_object');
        geomGen->addInStudy( , 'solid');

        //2. run body fitted algorithms
        SMESH_Gen* smeshGen = new SMESH_Gen();

        //create a mesh in the study
        SMESH_Mesh* mesh = smeshGen->CreateMesh(true);
        //set the geometry to be meshed in the mesh created
        mesh->ShapeToMesh(solid);

        //set the algorithm # create a hexahedral body fitted algorithm and assign it to gen
        StdMeshers_Cartesian_3D* cartesian_3D = new StdMeshers_Cartesian_3D(ALGO_3D, smeshGen); //ALGO_3D is the hypothesis_type
        //add parameters to the cartesian 3D algorithm
        StdMeshers_CartesianParameters3D* cartesian_3D_parameters = new StdMeshers_CartesianParameters3D(ALGO_3D, smeshGen);

        cartesian_3D_parameters->SetSizeThreshold(100); // add the threshold value
        cartesian_3D_parameters->SetToAddEdges(false); //disable: If this feature is disabled, sharp edges of the shape are lost ("smoothed") in the mesh if they don't coincide with the grid lines
        cartesian_3D_parameters->SetGridSpacing(['0.25'], [0,1],0); //Set grid spacing along the x-axis
        cartesian_3D_parameters->SetGridSpacing(['0.25'], [0,1],1); //Set grid spacing along the y-axis
        cartesian_3D_parameters->SetGridSpacing(['0.25'], [0,1],2); //Set grid spacing along the z-axis

        //compute the mesh
        bool is_done = smeshGen->Compute(*mesh, solid);

        //get some statistics
        mesh->NbHexas(); //how many hexas

        //3. export the mesh to vtk file: SMESH -> MED -> VTK
        const std::string out_data_path = "/Users/claudia/CLionProjects/3DMesher/MeshOutput/SalomeMeshOutput/";
        std::string outputFileNameMED = out_data_path + "/" + name + ".med";
        mesh->ExportMED(outputFileNameMED);

        //MEDCouplingUMesh* medCouplingUMesh = new MEDCouplingUMesh();
        //MEDCouplingUMesh* medCouplingUMesh = new MEDCouplingMesh();
        int mesh_dimension = 3;
        MEDCoupling::MEDCouplingUMesh* medCouplingUMesh = MEDCoupling::MEDCouplingUMesh::New("3DMesh", mesh_dimension);

        /* get MEDCouplingUMesh from scratch http://trac.lecad.fs.uni-lj.si/vaje/chrome/site/doc8.3.0/dev/MEDCoupling/medcouplingcppexamples.html#medcouplingcppexamplesUmeshStdBuild1
         * //retrieve basic data in full interlace mode for coordinates, and nodal connectivity cell per cell.
        double coords[];
        int number_of_nodes = mesh->Nb0DElements();
        std::map<Vertex_handle, vtkIdType> Vids;
        for(int n = 0; n<number_of_nodes; n++ ) //for n in m.GetNodesId():
        {
            coords += mesh->GetNodeXYZ( n );  //coords += m.GetNodeXYZ( n )
        }
        //let's set the coordinates using array coords defined above
        MEDCoupling::DataArrayDouble* coordsArray = MEDCoupling::DataArrayDouble::New(); // coordsArray = DataArrayDouble.New()
        int space_dimension = 3;
        coordsArray->alloc(number_of_nodes,space_dimension);//here coordsArr are declared to have 3 components, mesh will deduce that its spaceDim==3.
        int shift_number = number_of_nodes * space_dimension;
        std::copy(coords, coords + shift_number, coordsArray->getPointer());
        medCouplingUMesh->setCoords(coordsArray);//coordsArr contains number_of_nodes tuples

        MEDCoupling::DataArrayInt *nodalConn=MEDCoupling::DataArrayInt::New();
        nodalConn->alloc(mesh->NbElements(),1);
        std::copy(nodalConnPerCell,nodalConnPerCell+mesh->NbElements(),nodalConn->getPointer());
        MEDCoupling::DataArrayInt *nodalConnI=MEDCoupling::DataArrayInt::New();
        nodalConnI->alloc(6,1);
        std::copy(nodalConnPerCellIndex,nodalConnPerCellIndex+6,nodalConnI->getPointer());
        mesh->setConnectivity(nodalConn,nodalConnI,true);
        nodalConn->decrRef();// nodalConn DataArrayInt instance is owned by mesh after call to setConnectivity method. No more need here -> decrRef()
        nodalConnI->decrRef();// nodalConnI DataArrayInt instance is owned by mesh after call to setConnectivity method. No more need here -> decrRef()

        medCouplingUMesh->allocateCells(mesh->NbElements())
        for(auto element : mesh->GetElementsByType( SMESH.VOLUME) )
        {
            medCouplingUMesh->insertNextCell(NORM_SEG2, mesh->GetElemNodes(element))
        }
        cm.insertNextCell(NORM_SEG2, m.GetElemNodes( seg ))
        medCouplingUMesh->finishInsertingCells() //Compacts data arrays to release unused memory. This method is to be called after finishing cell insertion
        medCouplingUMesh->checkCoherency()
*/

        //coordsArray->decrRef();//When this mesh is no more needed simply call decrRef to decrement its reference counter.

        MEDCouplingUMesh* medCouplingUMesh=MEDLoader::ReadUMeshFromFile(outputFileNameMED,"3D_Mesh",0);

        const std::string out_data_path = "/Users/claudia/CLionProjects/3DMesher/MeshOutput/SalomeMeshOutput/";
        std::string outputFileNameVTK = out_data_path + "/" + name + ".vtk";
        std::ofstream vtk_file(outputFileNameVTK);


        medCouplingUMesh->writeVTK(	outputFileNameVTK, false); //isBinyary = false http://trac.lecad.fs.uni-lj.si/vaje/chrome/site/doc8.3.0/dev/MEDCoupling/classMEDCoupling_1_1MEDCouplingMesh.html#aee8b3910a00ec2f9edfc05b984cf5b59
//        medCouplingUMesh->writeVTKLL(vtk_file,
//                                                  const std::string & 	cellData,
//                                                  const std::string & 	pointData,
//                                                  DataArrayByte * 	byteData)


        medCouplingUMesh->decrRef(); //When this mesh is no more needed simply call decrRef() to decrement its reference counter.
    }
};


#endif //INC_3DMESHER_HEX_DOM_SALOME_MESH_H
