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
    }
    return unstructuredGrid;
}

void VTK_manager::get_statistics_from_vtk_file(std::string const& fileName) {
    vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid = readUnstructuredGrid(fileName);
    vtkIdType numberOfCells = unstructuredGrid->GetNumberOfCells();
    std::cout<<"Number of cells"<< numberOfCells<<std::endl;
    for(vtkIdType i = 0; i<numberOfCells; i++ )
    {

    }
    //unstructuredGrid->GetCellTypes();
}
