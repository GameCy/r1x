#include "OBJLoader.h"
#include <QFile>
#include "Utils.h"
#include <math.h>

namespace OBJLoader {

namespace algorithm
{
    float AngleBetweenV3(QVector3D a, QVector3D b)
    {
        float angle = QVector3D::dotProduct(a, b);
        angle /= (a.length() * b.length());
        return angle = acosf(angle);
    }

    // Check to see if a Vector3 Point is within a 3 Vector3 Triangle
    bool inTriangle(QVector3D point, QVector3D tri1, QVector3D tri2, QVector3D tri3)
    {
        // Starting vars
        QVector3D u = tri2 - tri1;
        QVector3D v = tri3 - tri1;
        QVector3D w = point - tri1;
        QVector3D n = QVector3D::crossProduct(u, v);

        float y = (QVector3D::dotProduct(QVector3D::crossProduct(u, w), n) / QVector3D::dotProduct(n, n));
        float b = (QVector3D::dotProduct(QVector3D::crossProduct(u, w), n) / QVector3D::dotProduct(n, n));
        float a = 1 - y - b;

        // Projected point
        //QVector3D p = (a * tri1) + (b * tri2) + (y * tri3);

        if (a >= 0 && a <= 1
            && b >= 0 && b <= 1
            && y >= 0 && y <= 1)
        {
            return true;
        }
        else
            return false;
    }

    // returns -1 or number of indexes, returns the actual indexes in @outIndexes
    int convertIndexes(QString indexesString, UIntVec &outIndexes)
    {
        QStringList parts = indexesString.split("/");

        int vtype = parts.size();
        if ( (vtype == 3) && (parts[1] != "") )    vtype = 4;
        if (vtype<1 || vtype>4)
            return -1;

        outIndexes.clear();
        foreach(auto p, parts)
            outIndexes.push_back( p.toInt() -1 );
        return vtype;
    }

}// algorithm

//---------------------------------------------

int Mesh::findVertexIndex(QString tripletKey)
{
    QMap<QString, int>::iterator itr = uniqueVertIndices.find(tripletKey);
    if (itr!=uniqueVertIndices.end())
        return itr.value();

    int newIndex = uniqueVertIndices.size();
    uniqueVertIndices[tripletKey] = newIndex;
    return -1;
}

//---------------------------------------------

Loader::~Loader()
{
    LoadedMeshes.clear();
}

bool Loader::LoadFile(QString filePath)
{
    Folder = Utils::getFolder(filePath);

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly))
    {
        QString fileContents = file.readAll();
        ParseFile(fileContents);
        return true;
    }
    return false;
}

bool Loader::ParseFile(QString dataBuffer)
{
    Mesh newMesh;

    bool flipUV = true;
    QTextStream file;
    file.setString(&dataBuffer);
    QString curline;
    while (!file.atEnd())
    {
        QString line = file.readLine();
        QString token = line.section(' ', 0, 0, QString::SectionSkipEmpty);

        QString tail = line.mid(token.size()+1);

        if (token == "o" || token == "g" || line[0] == 'g')
        {
            StoreMesh(newMesh);
            newMesh.MeshName = tail;
         }
        else if (token == "v")    Positions.push_back( ParseV3(tail));
        else if (token == "vt")   UVs.push_back( ParseV2(tail, flipUV) );
        else if (token == "vn")   Normals.push_back( ParseV3(tail) );
        else if (token == "f")
        {
            GenFaceVertices(newMesh, tail);
        }
        else if (token == "mtllib") // Load Materials
        {
            LoadMaterialsFile( tail );
        }
        else if (token == "usemtl")  // assign Material
        {
            newMesh.MaterialName = tail;
        }

    }

    // Deal with last mesh
    StoreMesh(newMesh);

    // Set Materials for each Mesh
    for (size_t i = 0; i < LoadedMeshes.size(); i++)
        for (size_t j = 0; j < LoadedMaterials.size(); j++)
            if (LoadedMaterials[j].name == LoadedMeshes[i].MaterialName)
            {
                LoadedMeshes[i].material = LoadedMaterials[j];
                break;
            }

    return !LoadedMeshes.empty();
}

void Loader::StoreMesh(Mesh &mesh)
{
    if (!mesh.IsEmpty())
    {
        LoadedMeshes.push_back( Mesh(mesh));
    }

    mesh.Clear();

}

void Loader::GenFaceVertices(Mesh& mesh, QString tail)
{
    QStringList indexTokens = tail.split(" ");

    size_t numVerts = indexTokens.size();
    for(size_t i = 0; i<numVerts ; i++)
    {
        int vertexIndex = mesh.findVertexIndex(indexTokens[i]);
        if (vertexIndex==-1)
        {
            UIntVec indexTriplet;
            int vertexType = algorithm::convertIndexes( indexTokens[i], indexTriplet);
            Vertex newVertex = MakeVertex(vertexType, indexTriplet);
            vertexIndex = mesh.AddVertex( newVertex );
        }

        mesh.Indices.push_back(vertexIndex);
    }
}

bool Loader::LoadMaterialsFile(QString filePath)
{
    QString mtlPath = Folder + "/" + Utils::getFile(filePath);

    QFile file(mtlPath);
    if (file.open(QIODevice::ReadOnly))
    {
        QString fileContents = file.readAll();
        return ParseMaterials(fileContents);
    }
    return false;
}

bool Loader::ParseMaterials(QString dataBuffer)
{
    QTextStream file;
    file.setString( &dataBuffer );

    Material tempMaterial;
    int materialCount=0;
    // Go through each line looking for material variables
    QString line;
    while (!file.atEnd())
    {
        line = file.readLine();
        QString token = line.section(' ', 0, 0, QString::SectionSkipEmpty);
        QString tail = line.mid(token.size()+1);

        // new material and material name
        if (token == "newmtl")
        {
            materialCount++;
            if (materialCount>1)
            {
                LoadedMaterials.push_back(tempMaterial);
                tempMaterial = Material();
            }

            if (line.size() > 7)    tempMaterial.name = tail;
            else                    tempMaterial.name = "none";
        }
        else if (token == "Ka")     tempMaterial.Ka = ParseV3(tail);
        else if (token == "Kd")     tempMaterial.Kd  = ParseV3(tail);
        else if (token == "Ks")     tempMaterial.Ks = ParseV3(tail);
        else if (token == "Ns")     tempMaterial.Ns = tail.toFloat();
        else if (token == "Ni")     tempMaterial.Ni = tail.toFloat();
        else if (token == "d")      tempMaterial.d = tail.toFloat();
        else if (token == "illum")  tempMaterial.illum = tail.toFloat();
        else if (token == "map_Ka") tempMaterial.map_Ka = tail;
        else if (token == "map_Kd") tempMaterial.map_Kd = tail;
        else if (token == "map_d")  tempMaterial.map_d = tail;
        else if (token == "map_Ns") tempMaterial.map_Ns = tail;
        else if (token == "map_Ks") tempMaterial.map_Ks = tail;
        else if (token == "map_Bump" || token == "map_bump")
            tempMaterial.map_bump = tail;
    }
    // Push last Material
    LoadedMaterials.push_back(tempMaterial);

    return !LoadedMaterials.empty();
}

QVector3D Loader::ParseV3(QString text)
{
    QStringList parts = text.split(" ");

    QVector3D v3 = QVector3D( parts[0].toFloat(), parts[1].toFloat(), parts[2].toFloat() );

    return v3;
}

QVector2D Loader::ParseV2(QString text, bool flipUV)
{
    QStringList parts = text.split(" ");

    QVector2D v2;
    v2.setX( parts[0].toFloat());
    if (flipUV)
        v2.setY( 1.f - parts[1].toFloat());
    else
        v2.setY( parts[1].toFloat());

    return v2;
}

Vertex Loader::MakeVertex(int vertexType, UIntVec indexes)
{
    Vertex newVertex;
    switch (vertexType)
    {
        case 1: newVertex = MakeVertexP( indexes[0] );              break;
        case 2: newVertex = MakeVertexPT( indexes[0], indexes[1] ); break;
        case 3: newVertex = MakeVertexPN( indexes[0], indexes[2] ); break;
        case 4: newVertex = MakeVertexPTN( indexes[0], indexes[1], indexes[2] ); break;
        default:
        {
            return Vertex();
        }
    }
    return newVertex;
}

Vertex Loader::MakeVertexP(int iPos)
{
    return Vertex( Positions[iPos], QVector2D(0,0), QVector3D(0,0,0) );
}

Vertex Loader::MakeVertexPT(int iPos, int iTex)
{
    Vertex v( Positions[iPos], UVs[iTex], QVector3D(0,0,0) );
    return v;
}

Vertex Loader::MakeVertexPN(int iPos, int iNormal)
{
    return Vertex( Positions[iPos], QVector2D(0,0), Normals[iNormal] );
}

Vertex Loader::MakeVertexPTN(int iPos, int iTex, int iNormal)
{
    Vertex v( Positions[iPos], UVs[iTex], Normals[iNormal] );
    return v;
}

} // OBJLoader
