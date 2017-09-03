#ifndef _OBJ_MODEL_LOADER_
#define _OBJ_MODEL_LOADER_

#include <QVector>
#include <QString>
#include "Vertex.h"

namespace OBJLoader
{
    typedef QVector<unsigned int> UIntVec;
    typedef QVector<QString> StringVec;

    namespace algorithm
    {
        float AngleBetweenV3(QVector3D a, QVector3D b);

        // Check to see if a Vector3 Point is within a 3 Vector3 Triangle
        bool inTriangle(QVector3D point, QVector3D tri1, QVector3D tri2, QVector3D tri3);

        int convertIndexes(QString indexesString, UIntVec &outIndexes);

        // Get element at given index position
        template <class T>
        inline const T & getElement(const std::vector<T> &elements, QString &index)
        {
            return elements[ index.toInt() - 1 ];
        }
    }

    struct Material
	{
		Material()
		{
            Clear();
		}

        void Clear()
        {
            name.clear();
            Ka = Kd = Ks = QVector3D(0.5, 0.5, 0.5);
            Ns = Ni = d = 0;
            illum = 0;
            map_bump = map_d = map_Ka = map_Kd = map_Ks = map_Ns = QString();
        }

        QString name;

        QVector3D Ka; // Ambient Color
        QVector3D Kd; // Diffuse Color
        QVector3D Ks; // Specular Color

        float Ns; // Specular Exponent
        float Ni; // Optical Density
        float d; // Dissolve

        int illum; // Illumination

        QString map_Ka; // Ambient Texture Map
        QString map_Kd; // Diffuse Texture Map
        QString map_Ks; // Specular Texture Map
        QString map_Ns; // Specular Hightlight Map
        QString map_d; // Alpha Texture Map
        QString map_bump; // Bump Map
	};

    struct Mesh
    {
        void Clear()
        {
            MeshName.clear();
            Vertices.clear();
            Indices.clear();
            MaterialName.clear();
            material.Clear();
            uniqueVertIndices.clear();
        }

        int AddVertex(Vertex v)
        {
            Vertices.push_back(v);
            return Vertices.size() - 1;
        }

        bool IsEmpty()
        {
            return Vertices.empty() || Indices.empty();
        }

        QString     MeshName;
        VertArray       Vertices;
        IndicesArray    Indices;

        Material        material;
        QString     MaterialName;

        int findVertexIndex(QString tripletKey);

    private:
        QMap<QString, int> uniqueVertIndices;
    };

	class Loader
	{
	public:
        ~Loader();

        bool LoadFile(QString filePath);

        std::vector<Mesh>       LoadedMeshes;
        std::vector<Material>   LoadedMaterials;

        QString Folder;

    private:
        bool ParseFile(QString dataBuffer);

        void StoreMesh(Mesh& mesh);
        void GenFaceVertices(Mesh &mesh, QString tail);

        void VertexTriangluation(IndicesArray& oIndices, const VertArray& iVerts);

		// Load Materials from .mtl file
        bool LoadMaterialsFile(QString filePath);
        bool ParseMaterials(QString dataBuffer);

        QVector3D ParseV3(QString text);
        QVector2D ParseV2(QString text, bool flipUV=false);

        Vec3Array Positions;
        Vec3Array Normals;
        Vec2Array UVs;

        Vertex MakeVertex(int vertexType, UIntVec indexes);
        Vertex MakeVertexP(int iPos);
        Vertex MakeVertexPT(int iPos, int iTex);
        Vertex MakeVertexPN(int iPos, int iNormal);
        Vertex MakeVertexPTN(int iPos, int iTex, int iNormal);
    };
}
 #endif
