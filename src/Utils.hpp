#pragma once 

#include <iostream>
#include "PolygonalMesh.hpp"

using namespace std;

namespace PolygonalLibrary
{
	bool ImportMesh (PolygonalMesh& mesh, const std::string& basePath);
	
	bool ImportCell0Ds (PolygonalMesh& mesh,const std::string& basePath);
	
	bool ImportCell1Ds (PolygonalMesh& mesh,const std::string& basePath);
	
	bool ImportCell2Ds (PolygonalMesh& mesh,const std::string& basePath);
}
