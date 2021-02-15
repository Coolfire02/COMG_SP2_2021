#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "Vertex.h"

/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	static Mesh* GenerateText(const std::string& meshName, unsigned numRow, unsigned numCol);
	static Mesh* GenerateOBJ(const std::string& meshName, const std::string& file_path);
	//static Mesh* GenerateQuad(const std::string& meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateCone(const std::string &meshName, Color color, int rad, int height);
	static Mesh* GenerateHalfCone(const std::string& meshName, Color color, int rad, int height);
	static Mesh* GenerateConicalFrustum(const std::string& meshName, Color color, float innerR, float outerR, int height);
	static Mesh* GenerateSphere(const std::string& meshName, Color color);
	static Mesh* GenerateHemiSphere(const std::string& meshName, Color color);
	static Mesh* GenerateHemiSphereFrustum(const std::string& meshName, Color color, float degreeCutOff);
	static Mesh* GenerateQuaterSphere(const std::string& meshName, Color color);
	static Mesh* GenerateCube(const std::string &meshName, Color color);
	static Mesh* GenerateQuad(const std::string& meshName, Color color);
	static Mesh* GenerateTetahedron(const std::string& meshName, Color color);
	static Mesh* GenerateTorus(const std::string& meshName, Color color, float innerR, float outterR);
	static Mesh* GenerateHalfTorus(const std::string& meshName, Color color, float innerR, float outterR);
	static Mesh* GenerateCylinder(const std::string& meshName, Color color, int height);
	static Mesh* GenerateOBJMTL(const std::string& meshName, const std::string& file_path, const std::string& mtl_path);
	static Mesh* GenerateHitBox(const std::string& meshName, Position3D* botLeftPos, Position3D* topRightPos);

private:
	static void calcMinMaxPos(Mesh*, std::vector<Vertex>);

};

#endif