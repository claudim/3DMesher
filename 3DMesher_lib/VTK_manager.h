// Copyright (c) 2020-2021 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// Manage a vtk file. For example, it can count how many hexahedra or _tetrahedra are in the file.
//******************************************************************************


#ifndef INC_3DMESHER_VTK_MANAGER_H
#define INC_3DMESHER_VTK_MANAGER_H

#include <iostream>
#include <map>
#include <fstream>
#include "vtk-9.0/vtkSmartPointer.h"
#include "vtk-9.0/vtkUnstructuredGridAlgorithm.h"
#include "vtk-9.0/vtkXMLUnstructuredGridReader.h"
#include "vtk-9.0/vtkUnstructuredGridReader.h"
#include "vtk-9.0/vtkUnstructuredGrid.h"
#include "vtk-9.0/vtkCellType.h"
#include "vtk-9.0/vtkCellTypes.h"
#include "vtk-9.0/vtkMeshQuality.h"
#include "vtk-9.0/vtkPolyData.h"
#include "vtk-9.0/vtkPointData.h"
#include "vtk-9.0/vtkCellData.h"
#include "vtk-9.0/vtkDoubleArray.h"
#include "vtk-9.0/vtkDataSet.h"
#include <algorithm>
#include "verdict.h"

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
     * as the number of hexahedra or the number of _tetrahedra or the number of _wedges.
     *
     * @param fileName The name of the file to read.
     * @param statistics A map where the key is a int (the vtk Cell Type, for example 12=VTK_HEXAHEDRON) while the value is the number associated to the key.
     * @param doStatisticsWriteOnFile true if statistics must be written on the file, false otherwise.
     */
    void get_statistics_from_vtk_file(std::string const &fileName, std::map<int, int> &statistics,
                                      bool doStatisticsWriteOnFile);

    /**
     * \brief Read from a .vtu file or .vtk file where is stored an unstructured grid and get some statistics on it
     * as the number of hexahedra or the number of _tetrahedra or the number of _wedges.
     *
     * @param fileName The name of the file to read.
     * @param statistics A map where the key is a int (the vtk Cell Type, for example 12=VTK_HEXAHEDRON) while the value is the number associated to the key.
     * @param doStatisticsWriteOnFile true if statistics must be written on the file, false otherwise.
     * @param outputFolderPath Path to a folder where write the statistics file text.
     */
    void get_statistics_from_vtk_file(std::string const &fileName, std::map<int, int> &statistics,
                                                   bool doStatisticsWriteOnFile, std::string const &outputFolderPath);

    /**
     * @brief Write the statistics related to the vtk file where is stored the mesh.
     *
     * @param statistics A map where is stored the statistics to write on the file.
     * @param vtkFileName The vtk file name.
     * @return true if the text file has been generated, false otherwise.
     */
    bool writeStatisticsOnFile(const std::map<std::string, int> &statistics, std::string const &vtkFileName);
//
//    /**
//     * @brief Generate Statistics from a unstructured grid passed as parameters.
//     *
//     * @param unstructuredGrid  The unstructured grid.
//     * @return true if statistics are generated, false otherwise.
//     */
//    bool generateStatistics(vtkSmartPointer<vtkUnstructuredGrid> &unstructuredGrid);

    double getQuality(std::string const &fileName);


};


#endif //INC_3DMESHER_VTK_MANAGER_H
