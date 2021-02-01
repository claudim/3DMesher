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

