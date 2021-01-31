// Copyright (c) 2020-2021 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// Manage a vtk file. For example, it can count how many hexahedra or tetrahedra are in the file.
//******************************************************************************


#ifndef INC_3DMESHER_VTK_MANAGER_H
#define INC_3DMESHER_VTK_MANAGER_H

#include <iostream>
#include <map>
#include <fstream>
#include "vtk-9.0/vtkUnstructuredGrid.h"
#include "vtk-9.0/vtkXMLUnstructuredGridReader.h"
#include "vtk-9.0/vtkUnstructuredGridReader.h"
#include "vtk-9.0/vtkCellType.h"

class VTK_manager {


public:
    /**
     * \brief Read from a .vtu file or .vtk file where is stored an unstructured grid and get back
     * unstructured grid filled with the information in the file.
     *
     * @param fileName The name of the file to read.
     * @return The unstructured grid filled with the information in the file.
     */
    vtkSmartPointer<vtkUnstructuredGrid> readUnstructuredGrid(std::string const& fileName);

    /**
     * \brief Read from a .vtu file or .vtk file where is stored an unstructured grid and get some statistics on it
     * as the number of hexahedra or the number of tetrahedra or the number of wedges.
     *
     * @param fileName The name of the file to read.
     * @param statistics A map where the key is a name like NUMB_HEXES (number of hexahedra) while the value is the number associated to the key.
     * A key could be 3D_CELLS_NUMBER (number of 3D elements), HEXES_NUMBER (number of hexahedra), TETRA_NUMBER (number of tetrahedra), and so on.
     * @param doStatisticsWriteOnFile true if statistics must be written on the file, false otherwise.
     */
    void get_statistics_from_vtk_file(std::string const &fileName, std::map<std::string, int> &statistics,
                                      bool doStatisticsWriteOnFile);

    /**
     * @brief Write the statistics related to the vtk file where is stored the mesh.
     *
     * @param statistics A map where is stored the statistics to write on the file.
     * @param vtkFileName The vtk file name.
     * @return true if the text file has been generated, false otherwise.
     */
    bool writeStatisticsOnFile(const std::map<std::string, int> &statistics, std::string const &vtkFileName);
};


#endif //INC_3DMESHER_VTK_MANAGER_H
