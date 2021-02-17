
#include <vtk-9.0/vtkCellArrayIterator.h>
#include "VTK_manager.h"

vtkSmartPointer<vtkUnstructuredGrid> VTK_manager::readUnstructuredGrid(std::string const& fileName) {
    vtkSmartPointer <vtkUnstructuredGrid> unstructuredGrid;
    std::string extension = "";
    if (fileName.find_last_of(".") != std::string::npos) {
        extension = fileName.substr(fileName.find_last_of("."));
    }

    // Drop the case of the extension
    std::transform(extension.begin(), extension.end(), extension.begin(),
                   ::tolower);

    if (extension == ".vtu") {
        std::cout<<"vtu"<<endl;
        vtkNew <vtkXMLUnstructuredGridReader> reader;
        reader->SetFileName(fileName.c_str());
        reader->Update();
        unstructuredGrid = reader->GetOutput();
    } else if (extension == ".vtk") {
        vtkNew <vtkUnstructuredGridReader> reader;
        reader->SetFileName(fileName.c_str());
        if(reader->IsFileValid("unstructured_grid"))
        {
            reader->Update();
            unstructuredGrid = reader->GetOutput();
        } else
        {
            std::cout<<"The vtk file is not valid "<<std::endl;
        }

    } else {
        //impossible to read
        std::cout<<"Impossible to read the file "<< fileName <<std::endl;
    }
    return unstructuredGrid;
}

void VTK_manager::get_statistics_from_vtk_file(std::string const &fileName, std::map<int, int> &statistics,
                                               bool doStatisticsWriteOnFile) {
    vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid = readUnstructuredGrid(fileName);

    vtkIdType numberOfCells = unstructuredGrid->GetNumberOfCells();
    std::cout << "------------------------" << std::endl;
    std::cout << "The inside dataset contains a " << std::endl
              << unstructuredGrid->GetClassName()
              <<  " that has " << numberOfCells << " cells" << std::endl;

    for (vtkIdType i = 0; i < numberOfCells; i++)
    {
        statistics[unstructuredGrid->GetCellType(i)]++;
    }

    if (doStatisticsWriteOnFile)
    {
        try {
            std::string fileName_without_extension = "";
            if (fileName.find_last_of("/") != std::string::npos) {
                fileName_without_extension = fileName.substr((fileName.find_last_of("/")+1));
                fileName_without_extension.replace(fileName_without_extension.size()-4, 4,"" );
            }
            std::ofstream statisticsFile;
            std::string statistics_file_name =  fileName_without_extension + "_statistics.txt";
            statisticsFile.open(statistics_file_name, std::ios::out);
            statisticsFile << "This is the statistics file of the mesh stored in " << fileName << ".\n";
            statisticsFile << "\n";

            for (auto c : statistics)
            {
                statisticsFile << "\tCell type "
                          << vtkCellTypes::GetClassNameFromTypeId(c.first)
                          << " occurs " << c.second << " times." << std::endl;
            }
            statisticsFile.close();

        }catch(std::ios::failure exception){
            std::cout<<"Error while writing statistics file" <<std::endl;
        }
    }

}

void VTK_manager::get_statistics_from_vtk_file(std::string const &fileName, std::map<int, int> &statistics,
                                               bool doStatisticsWriteOnFile, std::string const &outputFolderPath) {
    vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid = readUnstructuredGrid(fileName);

    vtkIdType numberOfCells = unstructuredGrid->GetNumberOfCells();
    std::cout << "------------------------" << std::endl;
    std::cout << "The inside dataset contains a " << std::endl
              << unstructuredGrid->GetClassName()
              <<  " that has " << numberOfCells << " cells" << std::endl;

    for (vtkIdType i = 0; i < numberOfCells; i++)
    {
        statistics[unstructuredGrid->GetCellType(i)]++;
    }

    if (doStatisticsWriteOnFile)
    {
        try {
            std::string fileName_without_extension = "";
            if (fileName.find_last_of("/") != std::string::npos) {
                fileName_without_extension = fileName.substr((fileName.find_last_of("/")+1));
                fileName_without_extension.replace(fileName_without_extension.size()-4, 4,"" );
            }
            std::ofstream statisticsFile;
            std::string statistics_file_name = outputFolderPath +  fileName_without_extension + "_statistics.txt";
            statisticsFile.open(statistics_file_name, std::ios::out);
            statisticsFile << "This is the statistics file of the mesh stored in " << fileName << ".\n";
            statisticsFile << "\n";

            for (auto c : statistics)
            {
                statisticsFile << "\tCell type "
                               << vtkCellTypes::GetClassNameFromTypeId(c.first)
                               << " occurs " << c.second << " times." << std::endl;
            }
            statisticsFile.close();

        }catch(std::ios::failure exception){
            std::cout<<"Error while writing statistics file" <<std::endl;
        }
    }

}

//bool VTK_manager::generateStatistics(vtkSmartPointer<vtkUnstructuredGrid> &unstructuredGrid) {
//    // Generate a report
//    vtkIdType numberOfCells = unstructuredGrid->GetNumberOfCells();
//    std::cout << "------------------------" << std::endl;
//    std::cout << "The inside dataset contains a " << std::endl
//              << unstructuredGrid->GetClassName()
//              <<  " that has " << numberOfCells << " cells" << std::endl;
//    typedef std::map<int,int> CellContainer;
//    CellContainer cellMap;
//    for (vtkIdType i = 0; i < numberOfCells; i++)
//    {
//        cellMap[unstructuredGrid->GetCellType(i)]++;
//    }
//
//    for (auto c : cellMap)
//    {
//        std::cout << "\tCell type "
//                  << vtkCellTypes::GetClassNameFromTypeId(c.first)
//                  << " occurs " << c.second << " times." << std::endl;
//    }
//    return true;
//}



bool VTK_manager::writeStatisticsOnFile(const std::map<std::string, int> &statistics, std::string const &vtkFileName) {
    try {
        std::ofstream statisticsFile;
        statisticsFile.open("Statistics.txt", std::ios::out);
        statisticsFile << "This is the statistics file of the mesh stored in " << vtkFileName << ".\n";
        statisticsFile << "\n";
        for (std::map<std::string, int>::const_iterator it = statistics.begin(); it != statistics.end(); ++it)
        {
            statisticsFile << it->first << ": " << it->second << " \n";
        }
        statisticsFile.close();
        return true;
    }catch(std::ios::failure exception){
        return false;
    }
}


double VTK_manager::getQuality(std::string const &fileName){
    vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid = readUnstructuredGrid(fileName);
    vtkSmartPointer<vtkMeshQuality> quality_filter = vtkSmartPointer<vtkMeshQuality>::New();
    quality_filter->SetInputData(unstructuredGrid);
    quality_filter->SetHexQualityMeasureToScaledJacobian();
    quality_filter->SetHexQualityMeasureToVolume();
    quality_filter->Update();

    for (vtkIdType i = 0; i < unstructuredGrid->GetNumberOfCells(); i++)
    {
        if (unstructuredGrid->GetCellType(i) == 12)
        {
            //It is an Hex Cell
            vtkCell *hex_cell = unstructuredGrid->GetCell(i);
            vtkSmartPointer<vtkCellArray> quads = vtkSmartPointer<vtkCellArray>::New();

            vtkSmartPointer<vtkMeshQuality> quality_face_filter = vtkSmartPointer<vtkMeshQuality>::New();
            vtkSmartPointer<vtkUnstructuredGrid> unstructured_grid_quad = vtkSmartPointer<vtkUnstructuredGrid>::New();
          //  vtkSmartPointer<vtkCellArray*>
            //vtkCellArray* const vtk_faces = vtkCellArray::New();
            // for each face
            for (vtkIdType j = 0; j < hex_cell->GetNumberOfFaces(); j++) {

                vtkCell *face = unstructuredGrid->GetCell(i)->GetFace(j);
                quads->InsertNextCell(face);
                double d = vtkMeshQuality::QuadWarpage(face);
                std::cout << "warpage  : " << d << std::endl;


//                // print face points
//                for (vtkIdType k = 0; k < face->GetNumberOfPoints(); k++) {
//                    double p[3];face->GetPoints()->GetPoint(k,p);
//                    std::cout<<p[0] << " " <<p[1]<< " " <<p[2] <<std::endl;
//                }


                if(face->GetCellType() == VTK_QUAD){
                    //quads->InsertNextCell(face);
                    std::cout << "size  : " << quads->GetSize() << std::endl;

                }

                //vtkIdType *pInt = unstructuredGrid->GetCell(i)->GetFaces();

                //quality_face_filter->SetInputData(unstructuredGrid->GetCell(i)->GetFaces());
            }

            unstructured_grid_quad->SetPoints(hex_cell->GetPoints());
            unstructured_grid_quad->SetCells(VTK_QUAD,quads);

            std::cout<<"punti:"<<unstructured_grid_quad->GetNumberOfPoints()<<std::endl;
            std::cout<<"facce:"<<unstructured_grid_quad->GetNumberOfCells()<<std::endl;

            quality_face_filter->SetInputData(unstructured_grid_quad);
            quality_face_filter->SetQuadQualityMeasureToWarpage();
            quality_face_filter->SetQuadQualityMeasureToArea();
            quality_face_filter->Update();

            vtkSmartPointer<vtkDoubleArray> qualityArrayQuad =
                    dynamic_cast<vtkDoubleArray*>(quality_filter->GetOutput()->GetCellData()->GetAbstractArray("Quality"));
                    //dynamic_cast<vtkDoubleArray*>(quality_face_filter->GetOutput()->GetFieldData()->GetArray("Mesh Quadrilateral Quality"));
            std::cout << "There are " << qualityArrayQuad->GetNumberOfTuples() << " values." << std::endl;
            for(vtkIdType i = 0; i < qualityArrayQuad->GetNumberOfTuples(); i++)
            {
                std::cout << "tuple "  << qualityArrayQuad->GetNumberOfTuples() << std::endl;
                    double val = qualityArrayQuad->GetValue(i);

                    std::cout << "value " << i << " : " << val << std::endl;
            }
        }
    }

//    vtkCellArray *pCellArray = unstructuredGrid->GetCells();
//    for (vtkCellArrayIterator it)
//    for(int i = 0; i < pCellArray->GetNumberOfCells(); i++){
//        pCellArray->GetCell(i,)
//    }
//    vtkIdTypeArray *pArray = unstructuredGrid->GetFaces();
    

   // vtkSmartPointer<vtkDoubleArray> quality_array =  vtkDoubleArray::FastDownCast(quality_filter->GetOutput()->GetCellData()) ;
    //vtkSmartPointer<vtkDataArray> quality_array =  vtkDataArray::FastDownCast(quality_filter->GetOutput()->GetCellGhostArray()) ;
    //quality_array->GetNumberOfTuples();
    vtkSmartPointer<vtkDoubleArray> qualityArray =
            //dynamic_cast<vtkDoubleArray*>(quality_filter->GetOutput()->GetCellData()->GetAbstractArray("Quality"));
            dynamic_cast<vtkDoubleArray*>(quality_filter->GetOutput()->GetFieldData()->GetArray("Mesh Hexahedron Quality"));
    std::cout << "There are " << qualityArray->GetNumberOfTuples() << " values." << std::endl;


    for(vtkIdType i = 0; i < qualityArray->GetNumberOfTuples(); i++)
    {
//        for(vtkIdType j = 0; j < qualityArray->GetNumberOfComponents(); j++){
//            double val = qualityArray->GetComponent(i,j);
//
//            std::cout << "value " << i << " : " << val << std::endl;
//
//        }
            double val = qualityArray->GetValue(i);
        std::cout << "value " << i << " : " << val << std::endl;
    }

    return qualityArray->GetValue(0);



}

