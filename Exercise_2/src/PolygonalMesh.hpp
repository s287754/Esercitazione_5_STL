#pragma once

#include <iostream>
#include <Eigen/Eigen>

using namespace std;
using namespace Eigen;


namespace PolygonalLibrary {

struct PolygonalMesh
{
    unsigned int NumberCell0Ds = 0;
    std :: vector <unsigned int> Cell0DsId = {};
    std :: vector <Vector2d> Cell0DsCoordinates = {};
    std ::  map <unsigned int, list <unsigned int>> Cell0DsMarkers = {};

    unsigned int NumberCell1Ds = 0;
    std :: vector <unsigned int> Cell1DsId = {};
    std :: vector <Vector2i> Cell1DsVertices = {};
    std :: map <unsigned int, list< unsigned int>> Cell1DsMarkers = {};

    unsigned int NumberCell2Ds = 0;
    std :: vector <unsigned int> Cell2DsId = {};
    std :: vector <vector <unsigned int>> Cell2DsVertices = {};
    std :: vector <vector <unsigned int>> Cell2DsEdges = {};

};
}
