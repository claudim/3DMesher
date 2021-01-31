#include "VTK_manager.h"

vtkSmartPointer<vtkUnstructuredGrid> readUnstructuredGrid(std::string const& fileName) {
    vtkSmartPointer <vtkUnstructuredGrid> unstructuredGrid;
    std::string extension = "";
    if (fileName.find_last_of(".") != std::string::npos) {
        extension = fileName.substr(fileName.find_last_of("."));
    }

    // Drop the case of the extension
    std::transform(extension.begin(), extension.end(), extension.begin(),
                   ::tolower);

    if (extension == ".vtu") {
        vtkNew <vtkXMLUnstructuredGridReader> reader;
        reader->SetFileName(fileName.c_str());
        reader->Update();
        unstructuredGrid = reader->GetOutput();
    } else if (extension == ".vtk") {
        vtkNew <vtkUnstructuredGridReader> reader;
        reader->SetFileName(fileName.c_str());
        reader->Update();
        unstructuredGrid = reader->GetOutput();
    } else {
        //impossible to read
        std::cout<<"Impossible to readthe file "<< fileName <<std::endl;
    }
    return unstructuredGrid;
}

void VTK_manager::get_statistics_from_vtk_file(std::string const &fileName, std::map<std::string, int> &statistics,
                                               bool doStatisticsWriteOnFile) {
    vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid = readUnstructuredGrid(fileName);
    vtkIdType numberOfCells = unstructuredGrid->GetNumberOfCells();
    statistics["CELLS_NUMBER"] = numberOfCells;
    std::cout<<"Number of cells"<< numberOfCells<<std::endl;
    int hexes_number = 0;
    int tetra_number = 0;
    int wedges_number = 0;
    int pyramids_number = 0;
    int voxels_number = 0;
    int other_polyhedron_number = 0;
    for(vtkIdType i = 0; i< numberOfCells; i++ )
    {
        int cell_type = unstructuredGrid->GetCellType(i);
        switch (cell_type) {
            case VTK_HEXAHEDRON:
                hexes_number++;
                break;
            case VTK_TETRA:
                tetra_number++;
                break;
            case VTK_WEDGE:
                wedges_number++;
                break;
            case VTK_PYRAMID:
                pyramids_number++;
                break;
            case VTK_VOXEL:
                voxels_number++;
                break;
            default:
                other_polyhedron_number++;
                break;
        }
    }
    //unstructuredGrid->GetCellTypes((vtkCellTypes *) list);
    statistics["CELLS_NUMBER"] = numberOfCells;
    statistics["HEXES_NUMBER"] = hexes_number;
    statistics["VOXELS_NUMBER"] = voxels_number;
    statistics["TETRA_NUMBER"] = tetra_number;
    statistics["WEDGES_NUMBER"] = wedges_number;
    statistics["PYRAMIDS_NUMBER"] = pyramids_number;
    statistics["OTHER_3D_CELLS_NUMBER"]= other_polyhedron_number;

    if (doStatisticsWriteOnFile)
    {
        this->writeStatisticsOnFile(statistics, fileName);
    }
}


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

