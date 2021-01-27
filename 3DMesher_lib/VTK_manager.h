// Copyright (c) 2020 Univaq (Italy)
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
#include <vtk-9.0/vtkUnstructuredGrid.h>
#include <vtk-9.0/vtkXMLUnstructuredGridReader.h>
#include <vtk-9.0/vtkUnstructuredGridReader.h>

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
     * as the number of hexahedra or the number of tetrahedra or the number of wedges
     *
     * @param fileName The name of the file to read.
     */
    void get_statistics_from_vtk_file(std::string const& fileName);
};


#endif //INC_3DMESHER_VTK_MANAGER_H
