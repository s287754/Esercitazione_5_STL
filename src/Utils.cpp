#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

namespace PolygonalLibrary
{
	bool ImportMesh(PolygonalMesh& mesh,const std::string& basePath)
{

    if(!ImportCell0Ds(mesh, basePath))
        return false;

    if(!ImportCell1Ds(mesh, basePath))
        return false;

    if(!ImportCell2Ds(mesh, basePath))
        return false;

    return true;
}

bool ImportCell0Ds(PolygonalMesh& mesh,const std::string& basePath)
{
	std::cout << "Tentativo di apertura file: " << "./Cell0Ds.csv" << std::endl;
	ifstream file ("/home/appuser/Data/Esercitazione5/Exercise2/Esercitazione_5_STL/Debug/Cell0Ds.csv");
	std::cout << "Apro file: " << basePath + "Cell0Ds.csv" << std::endl;
	if (file.fail())
		return false;
	
	list<string> listLines;
	string line;
	
    while (getline(file, line))
        listLines.push_back(line);

    file.close();
	
	listLines.pop_front();
	
	mesh.NumCell0Ds = listLines.size();
	
	if (mesh.NumCell0Ds == 0)
	{
		cerr << "No Cell0Ds" << endl;
		return false;
	}
	
	mesh.Cell0DsId.reserve(mesh.NumCell0Ds);
    mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds); 
	
	for (const string& line: listLines)
	{
		istringstream converter(line);
		
		unsigned int id;
		unsigned int marker;
		Vector2d coord;
		
		converter >> id >> marker >> mesh.Cell0DsCoordinates (0,id) >> mesh.Cell0DsCoordinates (1,id) ;
		
		mesh.Cell0DsId.push_back(id);
		
		if (marker != 0)
		{
			const auto it = mesh.MarkerCell0Ds.find(marker);
			if (it == mesh.MarkerCell0Ds.end())
				mesh.MarkerCell0Ds.insert({marker,{id}});
			
			else 
				it -> second.push_back(id);
		}
	}
	return true;
}

bool ImportCell1Ds(PolygonalMesh& mesh, const std::string& basePath)
{
	std::cout << "Tentativo di apertura file: " << "./Cell1Ds.csv" << std::endl;
	ifstream file("/home/appuser/Data/Esercitazione5/Exercise2/Esercitazione_5_STL/Debug/Cell1Ds.csv");
	std::cout << "Apro file: " << basePath + "Cell1Ds.csv" << std::endl;
	
	if (file.fail())
		return false;
		
	list <string> listLines;
	string line;
	
	while (getline (file,line))
		listLines.push_back(line);
	
	file.close();
	
	listLines.pop_front();
	
	mesh.NumCell1Ds = listLines.size();
	
	if (mesh.NumCell1Ds == 0)
	{
		cerr << "No Cell 1D" << endl;
		return false;
	}
	
	mesh.Cell1DsId.reserve(mesh.NumCell1Ds);
	mesh.Cell1DsExtrema = Eigen :: MatrixXi (2, mesh.NumCell1Ds);
	
	for (const string& line : listLines) {
		istringstream converter(line);
		
		unsigned int id;
		unsigned int marker;
		Vector2i Vertices;
		
		converter >> id >> marker >> mesh.Cell1DsExtrema (0,id) >> mesh.Cell1DsExtrema (1,id);
		mesh.Cell1DsId.push_back(id);
		
		if (marker != 0) {
			const auto it = mesh.MarkerCell1Ds.find(marker);
			if (it == mesh.MarkerCell1Ds.end()) 
			{
				mesh.MarkerCell1Ds.insert({marker,{id}});
			}
			else
			{
				it -> second.push_back(id);
			}
		}
	}
	return true;
}

bool ImportCell2Ds(PolygonalMesh& mesh, const std::string& basePath)
{
	std::cout << "Tentativo di apertura file: " << "./Cell2Ds.csv" << std::endl;
	ifstream file;
	file.open("/home/appuser/Data/Esercitazione5/Exercise2/Esercitazione_5_STL/Debug/Cell2Ds.csv");
	std::cout << "Apro file: " << basePath + "Cell2Ds.csv" << std::endl;
	
	if (file.fail())
		return false;
	
	list <string> listLines;
	string line;
	
	while (getline(file,line))
		listLines.push_back(line);
	
	file.close();
	
	listLines.pop_front();
	
	mesh.NumCell2Ds = listLines.size();
	
	if (mesh.NumCell2Ds == 0)
	{
		cerr << "No Cell 2D" << endl;
		return false; 
	}
	
	for (const string& line : listLines)
	{
		istringstream converter(line);
		
		unsigned int id;
		unsigned int marker;
		unsigned int NumVertices;
		unsigned int NumEdges;

		converter >> id >> marker >> NumVertices;
		vector<unsigned int> Vertices(NumVertices);
		for (unsigned int i = 0; i < NumVertices; i++)
			converter >> Vertices [i];
		
		converter >> NumEdges;
		vector<unsigned int> Edges(NumEdges);
		for (unsigned int i = 0; i < NumEdges; i++)
			converter >> Edges[i];
			
		mesh.Cell2DsId.push_back(id);
		mesh.Cell2DsMarker.push_back(marker);
		mesh.Cell2DsVertices.push_back(Vertices);
		mesh.Cell2DsEdges.push_back(Edges);
	}
	
	return true;
}

}
	