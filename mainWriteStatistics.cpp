// Copyright (c) 2020-2021 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// Main file to write some statistics from a vtk file.
//******************************************************************************

#include <iostream>
#include "VTK_manager.h"

int main(int argc, char* argv[]) {

    if (argc == 2 || argc == 3)
    {
        std::string inputPathToVTKFileName = argv[1];

        std::cout << "Loading: " << inputPathToVTKFileName << std::endl;
        VTK_manager vtk_manager;
        std::map<int, int> statistics;
        if(argc == 3)
        {
            std::string outputFolderPathStatistic = argv[2];
            vtk_manager.get_statistics_from_vtk_file(inputPathToVTKFileName, statistics, true,outputFolderPathStatistic );

        } else {
            vtk_manager.get_statistics_from_vtk_file(inputPathToVTKFileName, statistics, true);
        }
        std::cout<< "Write statistics on a txt file" <<std::endl;
    }
    return EXIT_SUCCESS;
}
