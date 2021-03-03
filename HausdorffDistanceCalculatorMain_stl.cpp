
#include <cstdlib>
#include <VTK_manager.h>
#include "vtkHausdorffDistancePointSetFilter.h"
#include <string>
#include <vtk-9.0/vtkSTLReader.h>

int main(int argc, char* argv[]){

    if (argc == 3)
    {
        std::string inputPathToVTKFileName = argv[1];
        std::string inputPathToVTKFileName2 = argv[2];

        std::cout << "Loading: " << inputPathToVTKFileName << std::endl;

        vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New();
        reader->SetFileName(inputPathToVTKFileName.c_str());
        reader->Update();

        vtkSmartPointer<vtkSTLReader> reader2 = vtkSmartPointer<vtkSTLReader>::New();
        reader2->SetFileName(inputPathToVTKFileName2.c_str());
        reader2->Update();
       // VTK_manager vtk_manager;
        //vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid = vtk_manager.readUnstructuredGrid(inputPathToVTKFileName);

        std::cout << "0" << std::endl;


        vtkSmartPointer<vtkHausdorffDistancePointSetFilter> distance =
                vtkSmartPointer<vtkHausdorffDistancePointSetFilter>::New();
        //vtkHausdorffDistancePointSetFilter* distance;
        std::cout << "0.1" << std::endl;

        distance->SetInputData(0,reader->GetOutput());
        std::cout << "0.2" << std::endl;

        distance->SetInputData(1,reader2->GetOutput());

        std::cout << "0.3" << std::endl;

        distance->Update();
        std::cout << "1" << std::endl;

        double hausdorffDistance = distance->GetHausdorffDistance();
        std::cout << "Distanza " << hausdorffDistance << std::endl;
    }
    return EXIT_SUCCESS;
}
