#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Utils.hpp"

namespace PolygonalLibrary {

bool ImportMesh (const string& filepath,
                 PolygonalMesh& mesh)
{
    if (!ImportCell0Ds(filepath + "/Cell0Ds.csv",mesh))
    {
        return false;
    }
    else
    {
        cout << "Importazione avvenuta con successo" << endl;
        cout << "Cell0Ds Markers : " << endl;
        for (auto i = mesh.Cell0DsMarkers.begin() ; i != mesh.Cell0DsMarkers.end() ; i ++)
        {
            cout << "Chiave:\t" << i -> first << "\t Valore:";
            for (const unsigned int id : i -> second) {
                cout << "\t" << id;
            }
            cout << endl;

        }
    }

    if (!ImportCell1Ds(filepath + "/Cell1Ds.csv",mesh))
    {
        cerr << "Errore nell'importazione dei dati" << endl;
        return false;
    }
    else
    {
        cout << "Importazione avvenuta con successo!" << endl;
        cout << "Cell1Ds Markers : " << endl;
        for (auto i = mesh.Cell1DsMarkers.begin() ; i != mesh.Cell1DsMarkers.end() ; i++) {
            cout << "Chiave:\t" << i -> first << "\t Valore:";
            for (const unsigned int id : i-> second) {
                cout << "\t" << id;
            }
            cout << endl;

        }
    }

    if (!ImportCell2Ds (filepath + "/Cell2Ds.csv",mesh)) {
        cerr << "Errore nell'importazione dei dati" <<endl;
        return false;
    }
    else {
        for (unsigned int c = 0; c < mesh.NumberCell2Ds; c++) {
            vector <unsigned int> Edges = mesh.Cell2DsEdges[c];

            for (unsigned int e = 0; e < 3; e++) {
                const unsigned int origin = mesh.Cell1DsVertices [Edges [e]][0];
                const unsigned int end = mesh.Cell1DsVertices [Edges [e]] [1];

                auto findOrigin = find (mesh.Cell2DsVertices[c].begin(), mesh.Cell2DsVertices[c].end(),end );
                if (findOrigin == mesh.Cell2DsVertices[c].end()) {
                    cerr << "Wrong mesh " << endl;
                    return 2;
                }
                auto findEnd = find(mesh.Cell2DsVertices[c].begin(), mesh.Cell2DsVertices[c].end(), end);
                if (findEnd == mesh.Cell2DsVertices[c].end()) {
                    cerr << "Wrong mesh" << endl;
                    return 3;
                }
            }
        }
    }
    return true;
}

bool ImportCell0Ds (const string &filename, PolygonalMesh& mesh) {

    ifstream file;
    file.open(filename);

    if (file.fail()) {
        return false;
    }

    list<string> listLines;
    string line;

    while (getline (file,line)) {
        listLines.push_back(line);
    }
    file.close();

    listLines.pop_front();

    mesh.NumberCell0Ds = listLines.size();

    if (mesh.NumberCell0Ds == 0) {
        cerr << "Non ci sono celle 0D" << endl;
        return false;
    }

    mesh.Cell0DsId.reserve(mesh.NumberCell0Ds);
    mesh.Cell0DsCoordinates.reserve(mesh.NumberCell0Ds);

    for (const string& line : listLines) {

        istringstream converter;

        unsigned int id;
        unsigned int Markers;
        Vector2d coordinates;

        converter >> id >> Markers >> coordinates (0) >> coordinates (1) ;

        mesh.Cell0DsId.push_back(id);
        mesh.Cell0DsCoordinates.push_back(coordinates);

        if (Markers != 0) {
            auto ret = mesh.Cell0DsMarkers.insert( {Markers,{id}} );
            if (!ret.second)
                (ret.first) -> second.push_back(id);
        }

    }
    file.close();
    return true;

}

bool ImportCell1Ds (const string &filename, PolygonalMesh& mesh) {

    ifstream file;
    file.open(filename);

    if (file.fail())
        return false;


    list <string> listLines;
    string line;

    while (getline (file,line)) {
        listLines.push_back(line);
    }

    listLines.pop_front();
    mesh.NumberCell1Ds = listLines.size();

    if (mesh.NumberCell1Ds == 0) {
        cerr <<"Non ci sono celle 1D" << endl;
        return false;
    }

    mesh.Cell1DsId.reserve(mesh.NumberCell1Ds);
    mesh.Cell1DsVertices.reserve(mesh.NumberCell1Ds);


    for (const string& line : listLines) {

        istringstream converter;

        unsigned int id;
        unsigned int Markers;
        Vector2i coordinates;

        converter >> id >> Markers >> coordinates (0) >> coordinates (1);

        mesh.Cell1DsId.push_back(id);
        mesh.Cell1DsVertices.push_back(coordinates);

        if (Markers != 0) {
            auto ret = mesh.Cell1DsMarkers.insert ({Markers, {id}});
            if (!ret.second)
                (ret.first) -> second.push_back(id);
        }
    }

    file.close();

    return true;

}

bool ImportCell2Ds (const string &filename, PolygonalMesh& mesh) {

    ifstream file;
    file.open(filename);

    if (file.fail())
        return false;

    list <string> listLines;
    string line;


    while (getline(file,line))
        listLines.push_back(line);


    listLines.pop_front();

    mesh.NumberCell2Ds = listLines.size();

    if (mesh.NumberCell2Ds == 0) {
        cerr << "Non ci sono celle 2D" << endl;
        return false;
    }

    mesh.Cell2DsId.reserve(mesh.NumberCell2Ds);
    mesh.Cell2DsVertices.reserve(mesh.NumberCell2Ds);
    mesh.Cell2DsEdges.reserve(mesh.NumberCell2Ds);

    for (const string& line : listLines) {

        istringstream converter (line);

        unsigned int id;
        vector <unsigned int> Vertices;
        vector <unsigned int> Edges;

        char ch;

        converter >> id >> ch;

        unsigned int numVertices;
        unsigned int numEdges;

        converter >> numVertices;

        for (unsigned int i = 0; i < numVertices ; i++)
            converter >> Vertices [i];


        converter >> numEdges;
        for (unsigned int i = 0; i < numEdges ; i++)
            converter >> Edges [i];


        mesh.Cell2DsId.push_back(id);
        mesh.Cell2DsVertices.push_back(Vertices);
        mesh.Cell2DsEdges.push_back(Edges);
    }

    file.close();
    return true;
    }
}

